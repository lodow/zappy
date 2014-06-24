package manage.map;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by max on 24/06/14.
 */
public class Network {
    private Map map;
    private Socket socket;
    private BufferedReader input;
    private BufferedWriter output;

    public Network(String ip, int port) throws IOException, NumberFormatException {
        socket = new Socket(ip, port);
        this.input = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        this.output = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));
        input.readLine();
        output.write("GRAPHIC\n");
        output.flush();
        String tmp = input.readLine();
        String[] parts = tmp.split(" ");
        map = new Map(Integer.parseInt(parts[1]), Integer.parseInt(parts[2]));
        input.readLine();//time
        tmp = input.readLine();
        parts = tmp.split(" ");
        while (parts[0].compareTo("bct") == 0) {
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
    //        TODO: get players and stock them
    }

    public Map getMap() {
        return map;
    }

    public boolean update() {
        return true;
    }


}
