#!/usr/bin/env node

(function () {
	var stdio = require('stdio');
    var client = require("./client");

    try {
		var opt = stdio.getopt({
			'team': {key: 'n', args: 1, description: "IA's teamname", mandatory: true},
		    'port': {key: 'p', args: 1, description: 'Connexion port', mandatory: false},
		    'host': {key: 'h', args: 1, description: 'Connexion host', mandatory: false},
		    'debug' : {key: 'd', args: 1, description: 'debug mode (network | verbose)', mandatory: false}
		});
	} catch(e) {
		console.log("Error getopt !");
		process.exit(1);
	}

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


		// ====> Search food only
		var survive = function (nbFood, see) {
			if (cli.inv.nourriture > nbFood) {
				cli.debug("Finis la survie");
				return (begin(10));
			}

			for (var i = 0; i < 4; ++i)
				if (see[i].nourriture)
					return (cli.goDirection(coresPos[see[2].nourriture ? 2 : i], function (dir) {
								cli.prend("nourriture", function (res) {
									cli.debug(res ? "J'ai pris une nourriture" : "Quelqu'un m'a pris ma nourriture");
									if (!res) {
										cli.goDirection(coresPos[Math.floor(Math.random() * 10) % 3 + 1], function (dir) {
													cli.voir(function (see) {
												survive(nbFood, see);
											});
										});
									} else {
										cli.voir(function (see) {
											survive(nbFood, see);
										});
									}
								});
							}));

			cli.debug("Pas de nourriture sur cette case");
			return (cli.avance(function (res) {
						cli.voir(function (see) {
							survive(nbFood, see);
						});
					}));
		}

		// =====> Incantation and number of player management

		var launchIncant = function () {
			cli.debug("Il y a le bon nombre de joueurs, je lance l'incantation");
			cli.broadcast(cli.lvl.toString() + "-ok", function (res) {
				cli.incantation(function (res) {
					if (!res) {
						cli.broadcast(cli.lvl.toString() + "-ko", function (res) {
							cli.avance(function (res) {
								begin((cli.lvl + 1) * 10);
							});
						});
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
							cli.incant = true;

							cli.voir(function (see) {
								callTeam(see[0]);
							});
						}));
			} else {
				cli.debug("Nous sommes trop sur la map, je m'en vais");
				return (cli.avance(function (res) {
							begin((cli.lvl + 1) * 10);
						}));
			}
		}

		// =====> Stones management
		var possibleIncant = function (square) {
			for (s in square)
				if (s != "joueur" && s != "nourriture" && square[s] + cli.inv[s] < incant[cli.lvl][s])
					return (false);
			return (true);
		}

		var getNeedyPlace = function (see) {
			var needy = [ ], score, direction;

			for (var i = 0; i < 4; ++i) {
				score = 0;
				for (s in see[i]) {
					if (s != "joueur" && s != "nourriture") {
						if (see[i][s] > 0 && incant[cli.lvl][s]) {
							score += 10;
						}
						if (see[i][s] > 0 && incant[cli.lvl + 1 == 7 ? cli.lvl : cli.lvl][s]) {
							score += 1;
						}
					} else if (s == "joueur") {
						if (see[i][s] > 0)
							score -= 10 * see[i][s];
					}
				}
				needy.push({ score : score,  index : i});
			}

			for (var i = 0, l = needy.length; i < l; ++i)
				needy[0] = needy[0].score > needy[i].score ? needy[0] : needy[i];

			if (needy[0].score > 0) {
				direction = needy[0].index;
			}
			if (needy[0].score == 0) {
				for (var i = 0, l = needy.length; i < l; ++i)
					if (needy[i].score < 0) {
						direction = needy[0].index;
						break ;
					} else {
						direction = Math.floor(Math.random() * 10) % 3 + 1;
					}
			}
			if (needy[0].score < 0) {
				direction = Math.floor(Math.random() * 10) % 3 + 1;
			}

			return (coresPos[direction]);
		}

		var takeStonesAndMove = function (see) {
			var square = see[0];
			var nextLvl = cli.lvl + 1 == 7 ? cli.lvl : cli.lvl + 1;

			for (s in square)
				if (s != "joueur" && square[s] && (incant[cli.lvl][s] || incant[nextLvl][s])) {
						return (cli.prend(s, function (res) {
									cli.voir(function (see) {
										takeStonesAndMove(see);
									});
								}));
				}

			cli.goDirection(getNeedyPlace(see), function (dir) {
				cli.voir(function (see) {
					searchStones(see);
				});
			});
		}

		var callbackStone = function (res) {
			cli.voir(function (see) {
				if (!res)
					cli.goDirection(getNeedyPlace(see), function (dir) {
						cli.voir(function (see_update) {
							searchStones(see_update);
						});
					});
				else
					searchStones(see);
			});
		}

		var searchStones = function (see) {
			var square = see[0];

			if (cli.levels(cli.lvl) < incant[cli.lvl].joueur) {
				cli.debug("Pas assez de joueur de mon lvl sur la map !");
				return (survive(cli.inv.nourriture + 10, see));
			}
			if (!possibleIncant(square))
				return (takeStonesAndMove(see));

			for (s in square) {
				if (s != "joueur") {
					if (square[s] > incant[cli.lvl][s]) {
						cli.debug("Je prend un " + s);
						return (cli.prend(s, callbackStone));
					}

					if (square[s] < incant[cli.lvl][s]) {
						cli.debug("Je pose un " + s);
						return (cli.pose(s, callbackStone));
					}
				}
			}
			cli.debug("Il devrait y avoir le bon nombre de pierres sur la case");
			return (callTeam(square));
		}

		// ====> Begin of the life loop
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
				begin((cli.lvl + 1) * 10);
			});
		});
	}

    new client(console, opt, doAlgo);

})();
