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
            self.socket.addListener('data', handleData);
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
            self.socket.addListener('data', handleData);
        };

        this.getResponse = function (data) {
        	print.recv(self.id + " : " + data);
        	if (data == "mort")
        		return (self.socket.destroy());




        	if ((cmd = self.cmds.shift())) {
        		cmd.callback(data);
        	}
        }

        this.sendCmd = function (cmd, callback) {
        	print.send(self.id + " : " + cmd);
        	self.cmds.push({cmd:cmd, callback:callback});
        	self.socket.write(cmd + '\n');
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
				callback(rep);
			});
		}

		this.avance = function (callback) {
			this.sendCmd("avance", function (rep) {
				callback(rep);
			});
		}

		this.droite = function (callback) {
			this.sendCmd("droite", function (rep) {
				callback(rep);
			});
		}

		this.gauche = function (callback) {
			this.sendCmd("gauche", function (rep) {
				callback(rep);
			});
		}

		this.inventaire = function (callback) {
			this.sendCmd("inventaire", function (rep) {
				callback(rep);
			});
		}

		this.prend = function (obj, callback) {
			this.sendCmd("prend " + obj, function (rep) {
				callback(rep);
			});
		}

		this.pose = function (obj, callback) {
			this.sendCmd("pose " + obj, function (rep) {
				callback(rep);
			});
		}

		this.expulse = function (callback) {
			this.sendCmd("expulse", function (rep) {
				callback(rep);
			});
		}

		this.broadcast = function (msg, callback) {
			this.sendCmd("broadcast " + msg, function (rep) {
				callback(rep);
			});
		}

		this.incantation = function (callback) {
			this.sendCmd("incantation", function (rep) {
				callback(rep);
			});
		}

		this.fork = function (callback) {
			this.sendCmd("incantation", function (rep) {
				callback(rep);
			});
		}

	}

	Client.prototype = new events.EventEmitter;
	module.exports = Client;

})();