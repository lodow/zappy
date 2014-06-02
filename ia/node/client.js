#!/usr/bin/env node

(function () {

	var net = require('net');
	var events = require('events');
	var nbClis = 0;

	var Client = function (print, opt, callback) {

		var self = this, handleData, handleConnect, handleCmd;

        this.dataCallback = null;
        this.print = print;
        this.cmds = [];
        this.id = -1;
        this.lvl = 0;
        this.inv = {};

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
                    self.id = parseInt(data);
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
            if (!data.indexOf("niveau actuel")) {
                data = data.replace('/ /g', "");
                self.lvl = parseInt(data.split(":")[1]) - 1;
                return ;
            }
            if (!data.indexOf("message")) {
                data = data.split(',');
                data[0] = data.split(' ')[1];
                self.emit('msg', parseInt(data[0]), data[1]);
                return ;
            }

        	if ((cmd = self.cmds.shift())) {
        		cmd.callback(data);
        	}
        }

        this.sendCmd = function (cmd, callback) {
        	print.send("[" + self.id + "] : " + cmd);
        	self.cmds.push({cmd:cmd, callback:callback});
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
					print.err("JSON error : " + e.message);
					rep = false;
				}
                self.inv = rep;
				callback(rep);
			});
		}

		this.prend = function (obj, callback) {
			this.sendCmd("prend " + obj, function (rep) {
				callback(rep == "ok");
			});
		}

		this.pose = function (obj, callback) {
			this.sendCmd("pose " + obj, function (rep) {
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
				callback(rep == "elevation en cours");
			});
		}

		this.fork = function (callback) {
			this.sendCmd("fork", function (rep) {
				callback(rep == "ok");
			});
		}

	}

	Client.prototype = new events.EventEmitter;
	module.exports = Client;

})();