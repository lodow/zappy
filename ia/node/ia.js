#!/usr/bin/env node

(function () {
	var stdio = require('stdio');
    var client = require("./client");

	var opt = stdio.getopt({
		'team': {key: 'n', args: 1, description: 'Teamname for te ia', mandatory: true},
	    'port': {key: 'p', args: 1, description: 'Connexion port', mandatory: false},
	    'host': {key: 'h', args: 1, description: 'Connexion host', mandatory: false},
	});

	opt.port = parseInt(opt.port) || 4242;
	opt.host = opt.host || "127.0.0.1";
	console.err = function (msg) { console.error("\033[0;31m!!! " + msg + "\033[0;0m"); }
	console.warn = function (msg) { console.log("\033[0;33m*** " + msg + "\033[0;0m"); }
	console.recv = function (msg) { console.log("\033[0;32m<<< " + msg + "\033[0;0m"); }
	console.send = function (msg) { console.log("\033[0;34m>>> " + msg + "\033[0;0m"); }

    var incant = [
    	{joueur : 1, linemate : 1, deraumere : 0, sibur : 0, mendiane : 0, phiras : 0, thystame : 0},
    	{joueur : 2, linemate : 1, deraumere : 1, sibur : 1, mendiane : 0, phiras : 0, thystame : 0},
    	{joueur : 2, linemate : 2, deraumere : 0, sibur : 1, mendiane : 0, phiras : 2, thystame : 0},
    	{joueur : 4, linemate : 1, deraumere : 1, sibur : 2, mendiane : 0, phiras : 1, thystame : 0},
    	{joueur : 4, linemate : 1, deraumere : 2, sibur : 1, mendiane : 3, phiras : 0, thystame : 0},
    	{joueur : 6, linemate : 1, deraumere : 2, sibur : 3, mendiane : 0, phiras : 1, thystame : 0},
    	{joueur : 6, linemate : 2, deraumere : 2, sibur : 2, mendiane : 2, phiras : 2, thystame : 1},
    ];

	var doAlgo = function (cli, mapX, mapY) {

		cli.on('msg', function (direction, data) {
			console.log("Received msg (broadcast):", direction, data);
		});

		cli.on('Move', function (callback) { // S'oriente aléatoirement a droite/gauche et avance d'une case
			var avance = function (res) {
				cli.avance(callback);
			}

			if (Math.floor(Math.random() * 10) % 2)
				cli.droite(avance);
			else
				cli.gauche(avance);
		});

		cli.on('needFood', function () {
			cli.voir(function (see) {
				if (see[0].nourriture) {
					cli.prend("nourriture", function (res) {
						if (!res)
							cli.emit("Move", function () { cli.emit("needFood"); });
					});
				} else {
					cli.emit("Move", function () { cli.emit("needFood"); });
				}
			});
		});

		cli.on('checkIncant', function () {
			cli.voir(function (see) {
				var square = see[0];

				for (c in square) {
					if (c != "joueur" && square[c] > incant[cli.lvl][c]) { // Trop de ressources sur la case, on les prend pour plus tard
						console.log("taking:", c);
					  	return (cli.prend(c, function () { cli.emit('checkIncant'); }));
					}

					if (c != "joueur" && square[c] < incant[cli.lvl][c]) { // Il manque une ressource sur la case, on essaye de poser, sinon on bouge
						console.log("missing:", c);
						return (cli.emit('Move', function () { cli.emit("checkIncant"); }));
					}
				}

				if (square.joueur < incant[cli.lvl].joueur) { // Si il manque des joueurs, on envoie un broadcast pour les amener a nous
					return (cli.broadcast("TOTO", function () { }));
				}

				// Tout est bon pour une incantation
				return (cli.incantation(function () { cli.emit('checkFood'); }));
			});
		});

		cli.on('checkFood', function () {
			cli.inventaire(function (inv) {
				if (inv.nourriture > 3) {
					cli.emit('checkIncant');
				} else {
					cli.emit('needFood');
				}
			});
		});

		cli.emit('checkFood');
    }

    new client(console, opt, doAlgo);

})();
