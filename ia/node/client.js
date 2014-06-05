#!/usr/bin/env node

(function () {

	var net = require('net');
	var events = require('events');
	var nbClis = 0;
    var nbFork = 0;
    var cliId = 0;

	var Client = function (print, opt, callback) {

		var self = this, handleData, handleConnect;

        this.dataCallback = null;
        this.levelCallback = null;
        this.print = print;
        this.cmds = [ ];
        this.msg = null;
        this.id = cliId;
        this.lvl = 0;
        this.lock = false;
        this.inv = {linemate : 0, deraumere : 0, sibur : 0, mendiane : 0, phiras : 0, thystame : 0};

        // =================== Creating socket connection ================

        print.warn("Connecting to " + opt.host + ":" + opt.port);
        this.socket = net.createConnection(opt.port, opt.host);
        
        this.socket.addListener('error', function(e) {
            print.err('Socket error: ' + e.message);
            self.socket.destroy();
        });

        this.socket.addListener('close', function(err) {
            nbClis--;
            print.warn('Closing connection... Exiting.');
        });
        
        this.socket.addListener('connect', function() {
            nbClis++;
            cliId++;
            if (nbFork)
                --nbFork;
            self.dataCallback = handleConnect;
            self.socket.on('data', handleData);
        });
        
       	handleData = function(data) {
            this.rb = this.rb || '';
            this.rb += data;
            while (this.rb.indexOf('\n') >= 0) {
                data = this.rb.substring(0, this.rb.indexOf('\n'));
                this.rb = this.rb.substring(this.rb.indexOf('\n') + 1);
                if (data.length && self.dataCallback)
                    self.dataCallback(data.toString());
            }
        };

        // =============== handle the connection and the map size =========

        handleConnect = function(data) {
            self.socket.removeListener('data', handleData);
            print.recv(data);

            if (data != "BIENVENUE") {
                print.err("Wrong welcome msg");
                return (self.socket.destroy());
            }
            
            self.dataCallback = function(data) {
            	this.turn = this.turn || 0;
            	print.recv(data);
                if (!(this.turn++))
                    self.id = nbClis;
                else {
                    data = data.split(' ');
                    if (data.length != 2) {
                        self.print.err('Wrong X/Y format');
                        return (self.socket.destroy());
                    }
                    self.dataCallback = this.getResponse;
                    print.warn("Connection successfully initialized");
                    callback(self, parseInt(data[0]), parseInt(data[1]));
                }
            };
            print.send(opt.team);
            self.socket.write(opt.team + '\n');
            self.socket.on('data', handleData);
        };

        this.getResponse = function (data) {
        	print.recv("[" + self.id + "] : " + data);
        	if (data == "mort")
        		return (self.socket.destroy());
            if (data == 'ko' && self.lock) {
                print.log("[" + self.id + "] : " + data + " => INCANTATION FAILED");
                self.lock = false;
                self.broadcast(self.lvl.toString() + "-ok", function (res) {

                });
                return (self.levelCallback(3));
            } 
            if (!data.indexOf("niveau actuel")) {
                data = data.replace('/ /g', "");
                self.lvl = parseInt(data.split(":")[1]) - 1;
                self.lock = false;
                return (self.levelCallback(3));
            }
            if (!data.indexOf("message")) {
                data = data.split(',');
                data[0] = data[0].split(' ')[1];
                if (parseInt(data[1].split('-')[0]) == self.lvl) {
                    self.msg = { direction : parseInt(data[0]) , msg : data[1].split('-')[1]};
                }
                return ;
            }

        	if ((cmd = self.cmds.shift())) {
        		cmd.callback(data);
        	}
        }

        this.sendCmd = function (cmd, callback) {
            if (self.cmds.length >= 10) {
                print.err("[" + self.id + "] " + " Trop de commandes en même temps !");
                return ;
            }

        	print.send("[" + self.id + "] : " + cmd);
        	self.cmds.push({cmd : cmd, callback : callback});
        	self.socket.write(cmd + '\n');
        }

        this.numberOf = function (cmd, to_find) {
        	var ret = 0, begin, end;

        	while (cmd.indexOf(to_find) != -1) {
        		begin = cmd.substring(0, cmd.indexOf(to_find));
        		end = cmd.substring(cmd.indexOf(to_find) + to_find.length);
        		cmd = begin + end;
        		++ret;
        	}
        	return (ret);
        }

        this.creatObject = function (cmd) {
        	var ret = { };

        	ret.joueur = self.numberOf(cmd, "joueur");
        	ret.nourriture = self.numberOf(cmd, "nourriture");
        	ret.linemate = self.numberOf(cmd, "linemate");
        	ret.deraumere = self.numberOf(cmd, "deraumere");
        	ret.sibur = self.numberOf(cmd, "sibur");
        	ret.mendiane = self.numberOf(cmd, "mendiane");
        	ret.phiras = self.numberOf(cmd, "phiras");
        	ret.thystame = self.numberOf(cmd, "thystame");
        	return (ret);
        }

        // ======================= COMMANDS ==================

        this.nbClis = function () {
			return (nbClis);
		}

        this.nbFork = function () {
            return (nbFork);
        }

        this.setLevelCallback = function (callback) {
            this.levelCallback = callback;
        }

        this.goDirection = function (direction, callback) {
            if (direction == 0) {
                callback(direction);
            } else if (direction == 1) {
                self.avance(function (res) {
                    callback(res);
                });
            } else if (direction == 2) {
                self.avance(function (res) {
                    self.gauche(function (res) {
                        self.avance(function (res) {
                            callback(direction);
                        });
                    });
                });
            } else if (direction == 3) {
                self.gauche(function (res) {
                    self.avance(function (res) {
                        callback(direction);
                    });
                });
            } else if (direction == 4) {
                self.gauche(function (res) {
                    self.avance(function (res) {
                        self.gauche(function (res) {
                            self.avance(function (res) {
                                callback(direction);
                            });
                        });
                    });
                });
            } else if (direction == 5) {
                self.gauche(function (res) {
                    self.gauche(function (res) {
                        self.avance(function (res) {
                            callback(direction);
                        });
                    });
                });
            } else if (direction == 6) {
                self.droite(function (res) {
                    self.avance(function (res) {
                        self.droite(function (res) {
                            self.avance(function (res) {
                                callback(direction);
                            });
                        });
                    });
                });
            } else if (direction == 7) {
                self.droite(function (res) {
                    self.avance(function (res) {
                        callback(direction);
                    });
                });
            } else if (direction == 8) {
                self.avance(function (res) {
                    self.droite(function (res) {
                        self.avance(function (res) {
                            callback(direction);
                        });
                    });
                });
            } else 
                print.err("[" + this.id + "] : Wrong direction (> 8 || < 0)");
        }

		this.connect_nbr = function (callback) {
			this.sendCmd("connect_nbr", function (rep) {
				callback(parseInt(rep));
			});
		}

		this.voir = function (callback) {
			this.sendCmd("voir", function (rep) {
				rep = rep.replace("{ ", "").replace("}", "").split(',');
				for (var i = 0, l = rep.length; i < l; ++i)
					rep[i] = self.creatObject(rep[i]);
				callback(rep);
			});
		}

		this.avance = function (callback) {
			this.sendCmd("avance", function (rep) {
				callback(rep == "ok");
			});
		}

		this.droite = function (callback) {
			this.sendCmd("droite", function (rep) {
				callback(rep == "ok");
			});
		}

		this.gauche = function (callback) {
			this.sendCmd("gauche", function (rep) {
				callback(rep == "ok");
			});
		}

		this.inventaire = function (callback) {
			this.sendCmd("inventaire", function (rep) {
				rep = rep.replace(/(, | ,)/g, ',').replace(/ /g, ':').replace(/({|,)/g, '$1"').replace(/:/g, '":');
				try {
					rep = JSON.parse(rep);
				} catch (e) {
					print.err(self.id + " JSON error : " + e.message);
					rep = false;
				}
                self.inv = rep;
				callback(rep);
			});
		}

		this.prend = function (obj, callback) {
			this.sendCmd("prend " + obj, function (rep) {
                if (rep == "ok")
                    self.inv[obj]++;
				callback(rep == "ok");
			});
		}

		this.pose = function (obj, callback) {
			this.sendCmd("pose " + obj, function (rep) {
                if (rep == "ok")
                    self.inv[obj]--;
				callback(rep == "ok");
			});
		}

		this.expulse = function (callback) {
			this.sendCmd("expulse", function (rep) {
				callback(rep == "ok");
			});
		}

		this.broadcast = function (msg, callback) {
			this.sendCmd("broadcast " + msg, function (rep) {
                callback(rep ==  "ok");
			});
		}

		this.incantation = function (callback) {
			this.sendCmd("incantation", function (rep) {
                if (rep == "elevation en cours")
                    self.lock = true;
				callback(rep == "elevation en cours");
			});
		}

		this.fork = function (callback) {
			this.sendCmd("fork", function (rep) {
                ++nbFork;
				callback(rep == "ok");
			});
		}

	}

	Client.prototype = new events.EventEmitter();
	module.exports = Client;

})();