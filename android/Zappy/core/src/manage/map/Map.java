package manage.map;

import com.badlogic.gdx.math.Vector2;

/**
 * Created by max on 24/06/14.
 */
public class Map {
    Vector2 size;

    enum eType
    {
        Nourriture,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    Map(int x, int y) {
        size = new Vector2(x, y);
    }

    public Vector2 getSize(){
        return size;
    }

    public Boolean setMap(int x, int y, eType type, int number) {
        return true;
    }

    public Boolean addPlayer(Player player) { return true; }

    public Boolean addEgg(Egg egg) { return true; }
}
