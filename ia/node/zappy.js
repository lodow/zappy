#!/usr/bin/env node
//
// zappy.js for Zappy
// 
// Made by vincent giersch
// Login   <giersc_v@epitech.net>
//

(function(){
    var net = require('net'),
        events = require('events');
    
    var zappyObjects = {
        nourriture:     { id: 0, str: "nourriture" },
        linemate:       { id: 1, str: "linemate" },
        deraumere:      { id: 2, str: "deraumere" },
        sibur:          { id: 3, str: "sibur" },
        mendiane:       { id: 4, str: "mendiane" },
        phiras:         { id: 5, str: "phiras" },
        thystame:       { id: 6, str: "thystame" }
    };

    var CRLF = '\n', nbias = 0;

    // zappyOptions format : { host: "127.0.0.1", port:4242, team:"myTeam", multipleClients:true, max:20 }
    var zappyClient = function(logger, zappyOptions, callback) {
        var self = this, onData, connectHandshake, zappyReceive, lockElevation = false;
        this.dataCallback = null;
        
        this.logger = logger;
        this.commandList = [];

        logger.info("Connecting to", zappyOptions.host, "port", zappyOptions.port);
        this.zpy = net.createConnection(zappyOptions.port, zappyOptions.host);
        
        this.zpy.addListener('end', function() {
            nbias--;
            logger.error('Connection to server ended unexpectedly.');
        });
        this.zpy.addListener('error', function(e) {
            logger.error('Socket error :', e.message);
            self.zpy.destroy();
        });
        this.zpy.addListener('timeout', function() {
            nbias--;
            logger.error('Connection to server timed out unexpectedly.');
            self.zpy.destroy();
        });
        this.zpy.addListener('close', function(hadError) {
            nbias--;
            if (hadError)
                logger.error('Connection to server closed.');
        });
        
        this.zpy.addListener('connect', function() {
            nbias++;
            self.dataCallback = function(data) {
                self.zpy.removeListener('data', onData);
                if (data.toString().indexOf('BIENVENUE') < 0)
                    logger.error('No welcome string');
                self.dataCallback = null;
                return connectHandshake();
            };
            self.zpy.addListener('data', onData);
        });
        
        events.EventEmitter.call(this);
        
        onData = function(data) {
            if (this.buffer === undefined)
                this.buffer = '';
            if (data.length === 0)
                return;
            this.buffer += data;
            while (this.buffer.indexOf(CRLF) >= 0)
            {
                data = this.buffer.substring(0, this.buffer.indexOf(CRLF));
                this.buffer = this.buffer.substring(this.buffer.indexOf(CRLF) + 1);
                logger.debug(self.zpy.hashClient, '| [fd]', self.zpy.fd, '| Receive line : ', data);
                if (self.dataCallback)
                    self.dataCallback(data.toString());
            }
        };
        
        zappyReceive = function(data) {
            logger.debug('Receive', data);
            if (!data.indexOf('message'))
            {
                if (self.emit('message', parseInt(data.split(',')[0].split(' ')[1]), data.split(',')[1]) &&
                    self.commandList.length === 0)
                        self.emit('slack');
                return true;
            }
            if (!data.indexOf('niveau actuel'))
            {
                this.lockElevation = false;
                return self.emit('level', data);
            }
            if (!data.indexOf('mort'))
    	    {
        		self.zpy.destroy();
        		return true;
    	    }
            if (!data.indexOf('deplacement'))
                return self.emit('expulse', data);
            logger.debug(this.zpy.hashClient, '| [fd]', this.zpy.fd, '| Command list :', self.commandList);
            if (data.indexOf('{') && self.commandList.length > 0 && (!self.commandList[0].data.indexOf('inventaire') || !self.commandList[0].data.indexOf('voir')))
                return false;
            if ((cmd = self.commandList.shift()) !== undefined)
            {
                logger.debug(this.zpy.hashClient, '| [fd]', this.zpy.fd, '| Association : ', cmd, 'to', data);
                cmd.callback(data);
                if (self.commandList.length === 0)
                    self.emit('slack');
            }
            return true;
        };
        
        connectHandshake = function()
        {
            var connectState = 0, id_player;
            self.dataCallback = function(data) {
                if (!(connectState++))
                    id_player = data;
                else
                {
                    data = data.split(' ');
                    if (data.length != 2)
                        self.logger.error('Error while recepting x / y');
                    self.dataCallback = zappyReceive;
                    callback(self, zappyOptions, parseInt(id_player),
                             parseInt(data[0]), parseInt(data[1]));
                    self.emit('slack');
                }
            };
            
            logger.info('Sending team name', zappyOptions.team);
            self.zpy.write(zappyOptions.team + "\n");
            self.zpy.addListener('data', onData);
        };
    };
        
    zappyClient.prototype = new process.EventEmitter();
    
    zappyClient.prototype.zappyGetNbIas = function() {
        return nbias;
    };
    
    zappyClient.prototype.zappySetHash = function(hash) {
        this.zpy.hashClient = hash;
    };
    
    zappyClient.prototype.zappyCmd = function(data, callback) {
        if (this.commandList.length >= 10 || this.lockElevation)
            return false;
        this.logger.info(this.zpy.hashClient, '| [fd]', this.zpy.fd, '|', data);
        this.commandList.push({data:data, callback:callback});
        try { this.zpy.write(data + "\n"); } catch(e) { console.error('Error :', e.message); this.zpy.destroy() };
        return true;
    };

    zappyClient.prototype.zappyAvance = function() {
        var args = arguments;
        return this.zappyCmd('avance', function(data) { for (var i = 0 ; i < args.length ; ++i) args[i](true); });
    };
    
    zappyClient.prototype.zappyDroite = function() {
        var args = arguments;
        return this.zappyCmd('droite', function(data) { for (var i = 0 ; i < args.length ; ++i) args[i](true); });
    };
    
    zappyClient.prototype.zappyGauche = function() {
        var args = arguments;
        return this.zappyCmd('gauche', function(data) { for (var i = 0 ; i < args.length ; ++i) args[i](true); });
    };
    
    zappyClient.prototype.zappyVoir = function() {
        var args = arguments;
        return this.zappyCmd('voir', function(data) {
            data = data.replace("{", "").replace("}", "").split(',');
            for (c in data)
            {
                data[c] = data[c].replace(/^ /, '');
                if (data[c] === '')
                    data[c] = null;
                else
                    data[c] = data[c].split(' ');
            }
            for (var i = 0 ; i < args.length ; ++i)
                args[i](data);
            return true;
        });
    };
    
    zappyClient.prototype.zappyObjectFromStr = function(str) {
        for (i in zappyObjets)
            if (zappyObjets[i] == str)
                return i;
        return -1;
    };
    
    zappyClient.prototype.zappyInventaire = function() {
        var args = arguments;
        return this.zappyCmd('inventaire', function(data) {
            if (args.length === 0 || data == 'ko')
                return false;
            try {
		data = data.replace(/(, | ,)/g, ',').replace(/ /g, ':').replace(/({|,)/g, '$1"').replace(/:/g, '":');
		data = JSON.parse(data);
	    }
            catch (e) { console.error('JSON.parse error :', e.message); return false; }
            for (var i = 0 ; i < args.length ; ++i)
                args[i](data);
            return true;
        });
    };
    
    zappyClient.prototype.zappyPrendre = function(type) {
        var args = arguments;
        if (typeof type == 'object')
            type = type.str;
        return this.zappyCmd('prend ' + type, function(data) {
            for (var i = 1 ; i < args.length ; ++i)
                args[i](data == "ok" ? true : false);
            return true;
        });
    };
    
    zappyClient.prototype.zappyPose = function(type) {
        var args = arguments;
        if (typeof type == 'object')
            type = type.str;
        return this.zappyCmd('pose ' + type, function(data) {
            for (var i = 1 ; i < args.length ; ++i)
                args[i](data == "ok" ? true : false);
        });
    };
    
    zappyClient.prototype.zappyIncantation = function() {
        var args = arguments;
        return this.zappyCmd('incantation', function(data) {
            if (data.indexOf('elevation en cours') >= 0)
                this.lockElevation = true;
            for (var i = 0 ; i < args.length ; ++i)
                args[i](data.indexOf('elevation en cours') >= 0);
        });
    };
    
    zappyClient.prototype.zappyFork = function() {
        var args = arguments;
        return this.zappyCmd('fork', function(data) {
            for (var i = 0 ; i < args.length ; ++i)
                args[i](data == "ok" ? true : false);
        });
    };
    
    zappyClient.prototype.zappyConnectNbr = function() {
        var args = arguments;
        return this.zappyCmd('connect_nbr', function(val) {
            for (var i = 0 ; i < args.length ; ++i)
                args[i](parseInt(val));
        });
    };
    
    zappyClient.prototype.zappyBroadcast = function(msg) {
        var args = arguments;
        return this.zappyCmd('broadcast ' + msg, function(data) {
            for (var i = 1 ; i < args.length ; ++i)
                args[i](data);
        });
    };
    
    zappyClient.prototype.zappyExpulse = function() {
        var args = arguments;
        return this.zappyCmd('expulse', function(data) {
            for (var i = 1 ; i < args.length ; ++i)
                args[i](data == "ok" ? true : false);
        });
    };

    exports.zappyClient = zappyClient;
    exports.zappyObjects = zappyObjects;
})();
