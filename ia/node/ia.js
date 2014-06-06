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

    var coresPos = [2, 1, 8];

	var doAlgo = function (cli, mapX, mapY) {

		var takeFood = function (numSquare, nbFood) {
			var pos;

			pos = coresPos[numSquare - 1] || 0;
			console.log("[" + cli.id + "]", 'Je prend la nourriture de la case:', pos);
			cli.goDirection(pos, function (res) {
				cli.prend("nourriture", function (res) {
					if (res) {
						console.log("[" + cli.id + "]", "J'ai réussi a prendre la nourriture");
						begin(nbFood);
					} else {
						console.log("[" + cli.id + "]", "Je n'ai pas réussi a prendre la nourriture (quelqu'un la prise avant moi)");
						searchFood(nbFood);
					}
				});
			});
		}

		var searchFood = function (nbFood) {
			console.log("[" + cli.id + "]", "J'avance");
			cli.goDirection(Math.floor(Math.random() * 10) % 8 + 1, function (res) {
				cli.voir(function (see) {
					foodInFrontOf(see, nbFood);
				});
			});
		}	

		var foodInFrontOf = function (see, nbFood) {
			try {
				for (var i = 0; i < 4;  ++i) // 4 => see.length, commencer par la case devant + opti
					if (see[i].nourriture) {
						console.log("[" + cli.id + "]", 'Il y a de la nourriture devant moi');
						return (takeFood(i, nbFood));
					}
			} catch (e) {
				console.err(cli.id + 'ERROR');
				process.exit(0);
			}
			console.log("[" + cli.id + "]", "Il n'y a pas de la nourriture devant moi");
			searchFood(nbFood);
		}

		var takeRock =  function (item) {
			console.log("[" + cli.id + "]", "je prend un ", item);
			cli.prend(item, function (res) {
				cli.voir(function (see) {
					hasMsg(see);
				});
			});
		}

		var putRock = function (item) {
			console.log("[" + cli.id + "]", "Je pose un", item);
			cli.pose(item, function (res) {
				cli.voir(function (see) {
					hasMsg(see);
				});
			});
		}

		var nextSquare = function () {
			console.log("[" + cli.id + "]", "J'avance");
			cli.goDirection(Math.floor(Math.random() * 10) % 8 + 1, function (res) {
				cli.voir(function (see) {
					hasMsg(see);
				});
			});
		}

		var launchIncant = function () { 
			if (!cli.lock) {
				console.log("[" + cli.id + "]", "J'incante");
				cli.incantation(function (res) {
					if (!res)
						begin((mapX + mapY) / 2);
					else {
						cli.broadcast(cli.lvl.toString() + "-ok", function (res) { });
					}
				});
			}
		}

		var callRenfort = function (square) {
			if (square.joueur < incant[cli.lvl].joueur) {
				console.log("[" + cli.id + "]", "je demande de l'aide");
				cli.broadcast(cli.lvl.toString() + "-help", function (res) {
					cli.voir(function (see) {
						callRenfort(see[0]);
					});
				});
			} else {
				checkNbPlayers(square);
			}
		}

		var checkNbPlayers = function (square) {
			console.log("[" + cli.id + "]", 'Je vérifie le nombre de joueurs');

			if (square.joueur == incant[cli.lvl].joueur) {
				console.log("[" + cli.id + "]", 'Il y a le bon nombre de joueurs sur la case')
				return (launchIncant());
			} else if (square.joueur < incant[cli.lvl].joueur) {
				console.log(cli.id, "Il manque des joueurs sur la case");
				if (cli.msg) {
					console.log("[" + cli.id + "]", "J'ai reçu un message, je cherche d'ou il vient");
					return (cli.voir(function (see) {
						hasMsg(see);
					}));
				}

				cli.connect_nbr(function (res) {
					if (!res) {
						if (cli.nbClis() + cli.nbFork() >= incant[cli.lvl].joueur) {
							callRenfort(square);
						} else {
							console.log("[" + cli.id + "]", "Je fork et je broadcast");
							cli.fork(function (res) {
								callRenfort(square);
							});
						}
					} else {
						console.log("[" + cli.id + "]", 'Je connecte un nouveau client, et je broadcast');
						new client(console, opt, doAlgo);
						callRenfort(square);
					}
				});
			} else {
				console.log("[" + cli.id + "]", "Nous sommes trop sur la case, je m'en vais");
				begin(3);
			}
		};

		var takeAllAndGoNext = function (square) {
			for (c in square) {
				if (c != "joueur") {
					if (square[c] > 0) {
						return (cli.prend(c, function (res) {
							cli.voir(function (see) {
								takeAllAndGoNext(see[0]);
							});
						}));
					}
				}
			}
			return (nextSquare());
		}

		var hasGoodNbOfRocks = function (square) {
			for (c in square) {
				if (c != "joueur") {
					if (cli.inv[c] === undefined || incant[cli.lvl][c] > square[c] + cli.inv[c]) {
						return (false);
					}
				}
			}
			return (true);
		}

		var checkRock = function (square) {
			if (!hasGoodNbOfRocks(square)) {
				console.log("[" + cli.id + "]","Il manque des ressources, je prend tout et je bouge");
				return (takeAllAndGoNext(square));
			}

			for (c in square) {
				if (c != "joueur") {
					if (square[c] > incant[cli.lvl][c]) {
						console.log("[" + cli.id + "]", "Il a a trop de :", c, "sur la case");
						return (takeRock(c));
					}

					if (square[c] < incant[cli.lvl][c]) {
						console.log("[" + cli.id + "]", "Il manque de :", c, "sur la case");
						if (square[c] + cli.inv[c] >= incant[cli.lvl][c]) {
							console.log("[" + cli.id + "]","Je pose:", c);
							return (putRock(c));
						} 
					}
				}
			}
			checkNbPlayers(square);
		}

		// /!\ Verif pas 2 incantation au même moment sur la même case ! msg.direction == 0, même case
		// Si on a les bonnes ressources, on vérifie que personne ne nous apelle, puis on appelle
		// Si on nous appelle, on va dans la bonne direction tant qu'on a pas reçu de "ok"
		// si on recoit "ko", fail de l'incant du mec

		var followMsg = function (see) {
			var recv = cli.msg;

			if (!recv) {
				return (cli.voir(function (see) {
						hasMsg(see);
					}));
			}
			cli.msg = null;
			if (recv && recv.msg == "ok") {
				if (recv.direction == 0)
					console.log("[" + cli.id + "]", "Le  mec qui m'a appelé incante");
				else {
					console.log("[" + cli.id + "]", "J'étais trop loin on a plus besoin de moi")
					begin(5);
				}
				return ;
			}

			if (recv && recv.msg == "ko" && recv.direction == 0) {
				console.log("[" + cli.id + "]", "Le  mec qui m'a appelé a raté son incantation");
				return (begin(5));
			}

			if (recv.msg == "help") {
				console.log("[" + cli.id + "]", "J'ai reçu:", recv.msg);
				cli.goDirection(recv.direction, function (dir) {
					cli.voir(function (see) {
						followMsg(see);
					});
				});
			}
		}

		
		var hasMsg = function (see) {
			console.log("[" + cli.id + "]", "Je check mes messages");
			if (cli.msg) {
				followMsg(see);
			} else {
				checkRock(see[0]);
			}
		}

		
		var begin =  function (nbFood) {
			cli.inventaire(function (inv) {
				cli.voir(function (see) {
					if (inv.nourriture >= nbFood) {
						hasMsg(see);
					} else {
						foodInFrontOf(see, nbFood);
					}
				});
			});
		}

		cli.fork(function (res) {
			cli.setLevelCallback(begin);
			begin((mapX + mapY) / 2);
		});
    }

    new client(console, opt, doAlgo);

})();
