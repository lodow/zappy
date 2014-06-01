#!/usr/bin/env node

(function () {
	var stdio = require('stdio');
	var net = require('net');

	var opt = stdio.getopt({
		'team': {key: 'n', args: 1, description: 'Teamname for te ia', mandatory: true},
	    'port': {key: 'p', args: 1, description: 'Connexion port', mandatory: false},
	    'host': {key: 'h', args: 1, description: 'Connexion host', mandatory: false},
	});

	var nbCli = 0;
	var items = {
		nourriture:     { id: 0, str: "nourriture" },
        linemate:       { id: 1, str: "linemate" },
        deraumere:      { id: 2, str: "deraumere" },
        sibur:          { id: 3, str: "sibur" },
        mendiane:       { id: 4, str: "mendiane" },
        phiras:         { id: 5, str: "phiras" },
        thystame:       { id: 6, str: "thystame" }
	};

	opt.port = parseInt(opt.port) || 4242;
	opt.host = opt.host || "127.0.0.1";
	console.err = function (msg) { console.error("\033[0;31m!!! " + msg + "\033[0;0m"); }
	console.warn = function (msg) { console.log("\033[0;33m*** " + msg + "\033[0;0m"); }

	// principal qui crée un client
	// chaque client est indépendant, prend un print + options en param
	// a sa propre fonction de callback quand il recoit de la data

	var client = function (print, opt) {
		var self = this, connect;


		print.warn('Connection to ' + opt.host + " port " + opt.port);
		socket = net.createConnection(opt.port, opt.host);
		
		socket.addListener('error', function(e) {
			print.err("Socket error: " + e.message);
			this.destroy();
		});
		
		socket.addListener('close', function(err) {
			print.warn('Connection to server closed.');
		});

		socket.addListener('connect', function() {
			++nbCli;
		    socket.addListener('data', getCmd)
		});

		getCmd = function (data) {
			if (this.buffer === undefined)
                this.buffer = '';
            if (data.length === 0)
                return ;
            this.buffer += data;
            while (this.buffer.indexOf('\n') >= 0) {
                data = this.buffer.substring(0, this.buffer.indexOf('\n'));
                this.buffer = this.buffer.substring(this.buffer.indexOf('\n') + 1);
                if (data.length)
                 	self.handleData(data.toString());
            }
        }

        handleData = function (data) {
        	if (data == "fork") {
        		client(print, opt);
        	}

        	socket.write(data + '\n');

        }


	}(console, opt);

})();
