package manage.map;

import com.badlogic.gdx.math.Vector2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

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
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Nourriture, Integer.parseInt(parts[3]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Linemate, Integer.parseInt(parts[4]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Deraumere, Integer.parseInt(parts[5]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Sibur, Integer.parseInt(parts[6]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Mendiane, Integer.parseInt(parts[7]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Phiras, Integer.parseInt(parts[8]));
            map.setMap(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]), Map.eType.Thystame, Integer.parseInt(parts[9]));
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
            // players
            map.addPlayer(new Player(new Vector2(Integer.parseInt(parts[2]), Integer.parseInt(parts[3])), parts[6], Integer.parseInt(parts[1]), Integer.parseInt(parts[5]), Player.eDirection.valueOf(parts[4])));
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
    }

    public Map getMap() {
        return map;
    }

    public boolean update() {
        return true;
    }
}
