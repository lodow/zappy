package manage.map;

import com.badlogic.gdx.math.Vector2;

import java.util.ArrayList;
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

    public Boolean addEgg(Egg egg) {
        eggs.add(egg);
        return true;
    }
}
