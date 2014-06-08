#!/usr/bin/env node

(function () {
	var stdio = require('stdio');
    var client = require("./client");

	var opt = stdio.getopt({
		'team': {key: 'n', args: 1, description: "IA's teamname", mandatory: true},
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

    var coresPos = [0, 2, 1, 8];

	var doAlgo = function (cli, mapX, mapY) {


		// ====> Chercher de la nourriture uniquement
		var survive = function (nbFood, see) {
			if (cli.inv.nourriture > nbFood) {
				cli.debug("Finis la survie");
				return (begin(10));
			}

			try {
				for (var i = 0; i < 4; ++i)
					if (see[i].nourriture) // préférer devant plutôt que devant + gauche
						return (cli.goDirection(coresPos[i], function (dir) {
									cli.prend("nourriture", function (res) {
										if (res)
											cli.debug("J'ai pris une nourriture");
										cli.voir(function (see) {
											survive(nbFood, see);
										});
									});
								}));
			} catch (e) {
				cli.debug("Err survive");
				process.exit(1);
			}
			cli.debug("Pas de nourriture sur cette case");
			return (cli.avance(function (res) {
						cli.voir(function (see) {
							survive(nbFood, see);
						});
					}));
		}

		// =====> Gestion du nombre de joueurs et incantation

		var launchIncant = function () {
			cli.debug("Il y a le bon nombre de joueurs, je lance l'incantation");
			cli.broadcast(cli.lvl.toString() + "-ok", function (res) {
				cli.incantation(function (res) {
					if (!res) {
						cli.debug("Je n'ai pas pu lancer mon incantation");
						cli.broadcast(cli.lvl.toString() + "-ko", function (res) { });
						return (begin(10));
					}
				});
			});
		}


		var callTeam = function (square) {
			cli.debug("Je vérifie le nombre de joueurs");

			if (square.joueur == incant[cli.lvl].joueur) {
				return (launchIncant());
			} else if (square.joueur < incant[cli.lvl].joueur) {
				cli.debug("Nous ne sommes pas assez, j'appele des gens");
				return (cli.broadcast(cli.lvl.toString() + "-help", function (res) {
							cli.voir(function (see) {
								callTeam(see[0]);
							});
						}));
			} else {
				cli.debug("Nous sommes trop sur la map, je m'en vais");
				return (begin(10));
			}
		}

		// =====> Gestion des pierres
		var possibleIncant = function (square) {
			for (s in square)
				if (s != "joueur" && square[s] + cli.inv[s] < incant[cli.lvl][s])
					return (false);
			return (true);
		}

		var takeStonesAndMove = function (see) {
			var square = see[0];

			for (s in square)
				if (s != "joueur" && square[s] && (incant[cli.lvl][s] || incant[cli.lvl + 1 == 7 ? cli.lvl : cli.lvl + 1][s]))
					return (cli.prend(s, function (res) {
								cli.voir(function (see) {
									takeStonesAndMove(see);
								});
							}));

			// bouger à un endroit pertinent en fonction de nos besoins
			cli.avance(function (res) {
				cli.voir(function (see) {
					searchStones(see);
				});
			});
		}

		var searchStones = function (see) {
			var square = see[0];

			if (!possibleIncant(square))
				return (takeStonesAndMove(see));

			for (s in square) {
				if (s != "joueur") {
					if (square[s] > incant[cli.lvl][s]) {
						cli.debug("Je prend un " + s);
						return (cli.prend(s, function (res) {
									cli.voir(function (see) {
										searchStones(see);
									});
								}));
					}

					if (square[s] < incant[cli.lvl][s]) {
						cli.debug("Je pose un " + s);
						return (cli.pose(s, function (res) {
									cli.voir(function (see) {
										searchStones(see);
									});
								}));
					}
				}
			}
			cli.debug("Il devrait y avoir le bon nombre de pierres sur la case");
			return (callTeam(square));
		}

		// ====> Tout début de la "boucle de vie"
		var begin = function (nbFood) {
			cli.inventaire(function (inv) {
				cli.voir(function (see) {
					if (inv.nourriture < nbFood) {
						cli.debug("Je n'ai pas assez de nourriture je vais en chercher");
						survive(nbFood + 10, see);
					} else {
						cli.debug("J'ai assez de nourriture, je vais chercher des pierres");
						searchStones(see);
					}
				});
			});
		}

		cli.fork(function (res) {
			cli.setLevelCallback(begin, function () {
				begin(10);
			});
		});
	}

    new client(console, opt, doAlgo);

})();
