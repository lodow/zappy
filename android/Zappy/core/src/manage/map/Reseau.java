package manage.map;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Created by max on 24/06/14.
 */
public class Reseau {
    private Map map;
    private Socket socket;

    Reseau() {
        try {
            socket = new Socket("37.187.16.16", 4242);
        } catch (UnknownHostException e) {
            
        } catch (IOException e) {

        }
    }
    public Map getMap() {
        return map;
    }

    public boolean update() {
        return true;
    }
}
