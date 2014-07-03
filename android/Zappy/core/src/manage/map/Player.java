package manage.map;

import com.badlogic.gdx.math.Vector2;

/**
 * Created by max on 26/06/14.
 */
public class Player {

    public enum eDirection {
        Nord(1),
        Est(2),
        Sud(3),
        Ouest(4);

        private int value;

        private eDirection(int value) {
            this.value = value;
        }
    }

    private Vector2 _pos;
    private String _team;
    private int _id;
    private int _level;
    private eDirection _dir;

    Player(Vector2 pos, String team, int id, int level, eDirection dir) {
        _pos = pos;
        _team = team;
        _id = id;
        _level = level;
        _dir = dir;
    }

    public void set_dir(eDirection _dir) {
        this._dir = _dir;
    }

    public void set_level(int _level) {
        this._level = _level;
    }

    public void set_pos(Vector2 _pos) {
        this._pos = _pos;
    }

    public int get_id() {
        return _id;
    }

    public int get_level() {
        return _level;
    }

    public String get_team() {
        return _team;
    }

    public eDirection get_dir() {
        return _dir;
    }

    public Vector2 get_pos() {
        return _pos;
    }
}
