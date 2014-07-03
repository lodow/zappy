package manage.map;

import com.badlogic.gdx.math.Vector2;

/**
 * Created by max on 26/06/14.
 */
public class Egg {

    enum eState {
        Laid,
        Bloom
    };

    private eState _state;
    private Vector2 _pos;
    private int _id;

    Egg(Vector2 pos, int id) {

    }

    public void set_pos(Vector2 _pos) {
        this._pos = _pos;
    }

    public void set_state(eState _state) {
        this._state = _state;
    }

    public eState get_state() {
        return _state;
    }

    public Vector2 get_pos() {
        return _pos;
    }

    public int get_id() {
        return _id;
    }
}
