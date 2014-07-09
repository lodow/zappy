package com.zappy.map.entities;

import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.zappy.assets.Assets;

/**
 * Created by max on 26/06/14.
 */
public class Egg {

    public enum eState {
        Laid,
        Bloom
    };

    private eState _state;
    private Vector2 _pos;
    private int _id;
    private Sprite egg;
    public Egg(Vector2 pos, int id)
    {
        _pos = pos;
        _id = id;
        _state = eState.Laid;

        egg = new Sprite(Assets.all, 153, 0, 12, 12);
        egg.setSize(0.45f, 0.7f); egg.rotate(45); egg.setPosition(pos.x - 5.2f, pos.y + 3.2f);
    }

    public void draw(SpriteBatch batch) {
        egg.draw(batch);
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
