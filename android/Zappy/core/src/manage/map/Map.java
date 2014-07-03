package manage.map;

import com.badlogic.gdx.math.Vector2;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by max on 24/06/14.
 */
public class Map {
    Vector2 size;

    private Square[][] map;
    List<Egg> eggs = new ArrayList<Egg>();
    List<Player> players = new ArrayList<Player>();

    Map(int x, int y) {
        map = new Square[x][y];
        int i = 0;
        while (i < map.length) {
            int j = 0;
            while (j < map[i].length)
            {
                map[i][j] = new Square();
                j++;
            }
            i++;
        }
        size = new Vector2(x, y);
    }

    public Vector2 getSize(){
        return size;
    }

    public Boolean setMap(int x, int y, Square.eType type, int number) {
        map[x][y].setItem(type, number);
        return true;
    }

    public Boolean addPlayer(Player player) {
        players.add(player);
        return true;
    }

    public Player getPlayer(Integer id) {
        Iterator i = players.iterator();

        while (i.hasNext()) {
            Player x = (Player) i.next();
            if (x.get_id() == id)
                return x;
        }
        throw new NullPointerException();
    }

    public Boolean deletePlayer(Integer id) {
        Iterator i = players.iterator();

        while (i.hasNext()) {
            Player x = (Player) i.next();
            if (x.get_id() == id) {
                i.remove();
                return true;
            }
        }
        return false;
    }

    public Boolean addEgg(Egg egg) {
        eggs.add(egg);
        return true;
    }

    public Egg getEgg(Integer id) {
        Iterator i = eggs.iterator();

        while (i.hasNext()) {
            Egg x = (Egg) i.next();
            if (x.get_id() == id)
                return x;
        }
        return null;
    }

    public Boolean deleteEgg(Integer id) {
        Iterator i = eggs.iterator();

        while (i.hasNext()) {
            Egg x = (Egg) i.next();
            if (x.get_id() == id) {
                i.remove();
                return true;
            }
        }
        return false;
    }

    public List<Player> getPlayers() {
        return players;
    }
}
