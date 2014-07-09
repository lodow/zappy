package com.zappy.network;


import com.badlogic.gdx.math.Vector2;
import com.zappy.map.Map;
import com.zappy.map.entities.Egg;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.lang.reflect.InvocationTargetException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by max on 24/06/14.
 */
public class Network {
    private Map map;
    private Socket socket;
    private BufferedReader input;
    private BufferedWriter output;
    private List<Player> players = new ArrayList<Player>();
    String[] parts;

    public Network(String ip, int port) throws IOException, NumberFormatException {
        socket = new Socket(ip, port);
        this.input = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        this.output = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));
        input.readLine();
        output.write("GRAPHIC\n");
        output.flush();
        String tmp = input.readLine(); // size of the map
        parts = tmp.split(" ");
        map = new Map(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]));
        input.readLine();// time of the server (T)
        tmp = input.readLine();
        parts = tmp.split(" ");
        while (parts[0].compareTo("bct") == 0) {
            // resources in the map
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Nourriture, Integer.parseInt(parts[3]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Linemate, Integer.parseInt(parts[4]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Deraumere, Integer.parseInt(parts[5]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Sibur, Integer.parseInt(parts[6]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Mendiane, Integer.parseInt(parts[7]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Phiras, Integer.parseInt(parts[8]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Thystame, Integer.parseInt(parts[9]));
            tmp = input.readLine();
            parts = tmp.split(" ");
        }
        while (tmp.compareTo("") != 0 && parts[0].compareTo("tna") == 0) {
            // name of teams
            if (input.ready())
                tmp = input.readLine();
            else
                tmp = "";
            parts = tmp.split(" ");
        }
        while (tmp.compareTo("") != 0 && parts[0].compareTo("pnw") == 0) {
            // playersl
            map.addPlayer(new Player(new Vector2(Integer.parseInt(parts[2]), Integer.parseInt(parts[3])), parts[6], Integer.parseInt(parts[1]), Integer.parseInt(parts[5]), Player.eDirection.values()[Integer.parseInt(parts[4]) - 1]));
            if (input.ready())
                tmp = input.readLine();
            else
                tmp = "";
            parts = tmp.split(" ");
        }
        while (tmp.compareTo("") != 0 && parts[0].compareTo("enw") == 0) {
            // eggs
            map.addEgg(new Egg(new Vector2(Integer.parseInt(parts[3]), Integer.parseInt(parts[4])), Integer.parseInt(parts[1])));
            if (input.ready())
                tmp = input.readLine();
            else
                tmp = "";
            parts = tmp.split(" ");
        }
        List<Player> players = map.getPlayers();
        Iterator it = players.iterator();
        while (it.hasNext()) {
            Player x = (Player)it.next();
            output.write("ppo " + x.get_id() + "\n");
            output.write("plv " + x.get_id() + "\n");
            output.write("pin " + x.get_id() + "\n");
        }
        output.flush();
    }

    public Map getMap() {
        return map;
    }

    public boolean update() throws IOException {
        if (parts[0].compareTo("") != 0)
            parse();
        String tmp;
        int i = 0;
        while (input.ready() && i < 1000) {
            tmp = input.readLine();
            parts = tmp.split(" ");
            parse();
            i++;
        }
        parts[0] = "";
        return true;
    }

    private void parse() {
        java.lang.reflect.Method method;
        try {
            method = this.getClass().getDeclaredMethod(parts[0]);
            method.invoke(this);
        } catch (NoSuchMethodException e) {
            System.err.println("no such method : " + parts[0]);
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    private void msz() {
        // taille de la carte
    }

    private void bct() {
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Nourriture, Integer.parseInt(parts[3]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Linemate, Integer.parseInt(parts[4]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Deraumere, Integer.parseInt(parts[5]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Sibur, Integer.parseInt(parts[6]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Mendiane, Integer.parseInt(parts[7]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Phiras, Integer.parseInt(parts[8]));
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Square.eType.Thystame, Integer.parseInt(parts[9]));
    }

    private void tna() {
        // name of teams
    }

    private void pnw() {
        Player x = new Player(new Vector2(Integer.parseInt(parts[2]), Integer.parseInt(parts[3])), parts[6], Integer.parseInt(parts[1]), Integer.parseInt(parts[5]), Player.eDirection.values()[Integer.parseInt(parts[4]) - 1]);
        map.addPlayer(x);
        try {
            output.write("plv " + x.get_id() + "\n");
            output.write("pin " + x.get_id() + "\n");
            output.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void ppo() {
        Player x =  map.getPlayer(Integer.parseInt(parts[1]));
        if (x != null) {
            x.set_dir(Player.eDirection.values()[Integer.parseInt(parts[4]) - 1]);
            x.set_pos(new Vector2(Integer.parseInt(parts[2]), Integer.parseInt(parts[3])));
        }
    }

    private void plv() {
        Player x =  map.getPlayer(Integer.parseInt(parts[1]));
        if (x != null) {
            x.set_level(Integer.parseInt(parts[2]));
        }
    }

    private void pin() {

        Player x =  map.getPlayer(Integer.parseInt(parts[1]));
        if (x != null) {
            x.setItem(Square.eType.Nourriture, Integer.parseInt(parts[4]));
            x.setItem(Square.eType.Linemate, Integer.parseInt(parts[5]));
            x.setItem(Square.eType.Deraumere, Integer.parseInt(parts[6]));
            x.setItem(Square.eType.Sibur, Integer.parseInt(parts[7]));
            x.setItem(Square.eType.Mendiane, Integer.parseInt(parts[8]));
            x.setItem(Square.eType.Phiras, Integer.parseInt(parts[9]));
            x.setItem(Square.eType.Thystame, Integer.parseInt(parts[10]));
        }
    }

    private void pex() {
        // un joueur expulse
    }

    private void pbc() {
        // broadcast
    }

    private void pic() {
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), true);
    }

    private void pie() {
        map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), false);
    }

    private void pfk() {
    }

    private void pdr() {
        // jette ressource
    }

    private void pgt() {
        // prend ressource
    }

    private void pdi() {
        map.deletePlayer(Integer.parseInt(parts[1]));
    }

    private void enw() {
        map.addEgg(new Egg(new Vector2(Integer.parseInt(parts[3]), Integer.parseInt(parts[4])), Integer.parseInt(parts[1])));
    }

    private void eht() {
        Egg x = map.getEgg(Integer.parseInt(parts[1]));
        if (x != null)
            x.set_state(Egg.eState.Bloom);
    }

    private void ebo() {
        map.deleteEgg(Integer.parseInt(parts[1]));
    }

    private void edi() {
        map.deleteEgg(Integer.parseInt(parts[1]));
    }

    private void sgt() {
        // time of server
    }

    private void seg() {
        map.setEndOfGame(parts[1]);
    }

    private void smg() {
        //msg du server
    }

    private void suc() {
        // bad command
    }

    private void sbp() {
        // bad params
    }
}
