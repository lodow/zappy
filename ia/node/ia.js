#!/usr/bin/env node

(function () {
	var stdio = require('stdio');
    var client = require("./client.js");

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

    var callback = function (msg) {
        console.log("on est dans le callback" + msg);
    }

    new client.Client(console, opt, callback));
    new client.Client(console, opt, callback));

})();
