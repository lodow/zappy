package manage.map;

import com.badlogic.gdx.utils.ArrayMap;

import java.util.*;

/**
 * Created by max on 27/06/14.
 */
public class Square {
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

    java.util.Map<eType, Integer> content = new HashMap<eType, Integer>();
    Square() {
        content.put(eType.Nourriture, 0);
        content.put(eType.Linemate, 0);
        content.put(eType.Deraumere, 0);
        content.put(eType.Sibur, 0);
        content.put(eType.Mendiane, 0);
        content.put(eType.Phiras, 0);
        content.put(eType.Thystame, 0);
    }

    public Boolean setItem(eType type, Integer number) {
        content.put(type, number);
        return true;
    }

    public Integer getItem(eType type) {
        return content.get(type);
    }

    public Set getItems() {
        return content.entrySet();
    }
}
