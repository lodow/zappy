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

		cli.on('10', function (numSquare) {
			var pos;

			if (numSquare == 1)
				pos = 2;
			else if (numSquare == 2)
				pos = 1;
			else if (numSquare == 3)
				pos = 8;
			else
				pos = 0;
			console.log('Je prend la nourriture de la case:', pos);
			cli.goDirection(pos, function (res) {
				cli.prend("nourriture", function (res) {
					if (res) {
						console.log("J'ai réussi a prendre la nourriture");
						cli.emit('1');
					} else {
						console.log("Je n'ai pas réussi a prendre la nourriture (quelqu'un la prise avant moi)");
						cli.emit('9');
					}
				});
			});
		});

		cli.on('9', function () {
			console.log("J'avance");
			cli.goDirection(Math.floor(Math.random() * 10) % 9 + 1, function (res) {
				cli.voir(function (see) {
					cli.emit('8', see);
				});
			});
		});

		cli.on('8', function (see) {
			for (var i = 	0; i < 4;  ++i)
				if (see[i].nourriture) {
					console.log('Il y a de la nourriture devant moi');
					return (cli.emit('10', i));
				}
			console.log("Il n'y a pas de la nourriture devant moi");
			cli.emit('9');
		});

		cli.on('12', function (item) {
			console.log("je prend un ", item);
			cli.prend(item, function (res) {
				cli.voir(function (see) {
					cli.emit('2', see[0]);
				});
			});
		});

		cli.on('13', function (item) {
			console.log("Je pose un", item);
			cli.pose(item, function (res) {
				cli.voir(function (see) {
					cli.emit('2', see[0]);
				});
			});
		});

		cli.on('14', function () {
			console.log("J'avance");
			cli.avance(function (res) {
				cli.voir(function (see) {
					cli.emit('2', see[0]);
				});
			});
		});

		cli.on('4', function () {
			console.log("Je debloque les anciens broadcast et j'incante");
			cli.broadcast(cli.lvl.toString + "-ok", function (res) {
				cli.incantation(function (res) {
					console.log("result de l'incant:", res);
				});
			});			
		});


		var onBroadcast = function (direction, msg) {
			msg = msg.split('-');
			if (parseInt(msg[0]) != cli.lvl) {
				console.log('Ce broadcast ne me concerne pas');
				return (cli.emit('1'));
			}

			if (msg[1] == 'help') {
				cli.goDirection(direction, function (res) {
					console.log("res =>", res);
					if (!res) {
						console.log("Je suis bien arrivé pour l'incant");
					} else {
						console.log("J'attend de nouvelles coordonées pour me déplacer");
					}
				});
			} else if (msg[1] == "ok") {

			}
		}

		cli.on('6', onBroadcast);

		cli.on('3', function (square) {
			console.log('Je vérifie le nombre de joueurs');
			if (square.joueur == incant[cli.lvl].joueur) {
				console.log('Il y a le bon nombre de joueurs sur la case')
				return (cli.emit("4"));
			} else if (square.joueur < incant[cli.lvl].joueur) {
				console.log("Il manque des joueurs sur la case");
				
				cli.connect_nbr(function (res) {
					if (!res) {
						if (cli.nbClis() + cli.nbFork() >= incant[cli.lvl].joueur) {
							console.log("je broadcast");
							cli.broadcast(cli.lvl.toString() + "-help", function (res) {
								cli.emit('3', square);
							});
						} else {
							console.log("Je fork et je broadcast");
							cli.fork(function (res) {
								cli.broadcast(cli.lvl.toString() + "-help", function (res) {
									cli.emit('3', square);
								});
							});
						}
					} else {
						console.log('Je connecte un nouveau client, et je broadcast');
						new client(console, opt, doAlgo);
						cli.broadcast(cli.lvl.toString() + "-help", function (res) {
							cli.emit('3', square);
						});
					}
				});
			} else {
				// si on a trop de joueurs sur la case ?
			}
		});

		cli.on('2', function (square) {
			for (c in square) {
				if (c != "joueur") {
					if (square[c] > incant[cli.lvl][c]) {
						console.log("Il a a trop de :", c, "sur la case");
						return (cli.emit('12', c));
					}

					if (square[c] < incant[cli.lvl][c]) {
						console.log("Il manque de :", c, "sur la case");
						if (square[c] + cli.inv[c] >= incant[cli.lvl][c]) {
							console.log("Je pose:", c);
							return (cli.emit('13', c));
						} else {
							console.log("Je n'en ai pas", cli.inv);
							return (cli.emit('14'));
						}
					}
				}
			}
			cli.emit("3", square);
		});

		cli.on('1', function () {
			cli.inventaire(function (inv) {
				cli.voir(function (see) {
					if (inv.nourriture > 50) {
						cli.emit('2', see[0]);
					} else {
						cli.emit('8', see);
					}
				});
			});
		});

		cli.fork(function (res) {
			cli.emit('1');
		});
    }

    new client(console, opt, doAlgo);

})();
