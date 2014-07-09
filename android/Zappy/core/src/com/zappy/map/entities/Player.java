package com.zappy.map.entities;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.zappy.assets.Assets;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by max on 26/06/14.
 */
public class Player extends Actor {

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

    private boolean selected = false;
    private Vector2 _pos;
    private Vector2 _oldPos;
    private String _team;
    private int _id;
    private int _level;
    private eDirection _dir;
    private HashMap<eDirection, Animation> player_animation;
    private HashMap<eDirection, Sprite> player_static;
    private float state_time = 0;
    private TextureRegion currentFrame;
    private SpriteBatch batch = new SpriteBatch();
    private Map<Square.eType, Integer> content = new HashMap<Square.eType, Integer>();
    private Matrix4 matrix4 = new Matrix4(), defaultMat = new Matrix4();
    private Vector3 rotation = new Vector3(0, 1, 0);
    private Vector2 randPos = new Vector2();

    public Player(Vector2 pos, String team, int id, int level, eDirection dir) {
        _pos = pos;
        _oldPos = _pos;
        _team = team;
        _id = id;
        _level = level;
        _dir = dir;
        player_animation = Assets.getAnimationPlayer();
        player_static= Assets.getStaticPlayer();

        randPos.x = (float)(randPos.x + Math.random() - 0.5) / 1.8f;
        randPos.y = (float)(randPos.y + Math.random() - 0.5) / 1.8f;

        content.put(Square.eType.Nourriture, 0);
        content.put(Square.eType.Linemate, 0);
        content.put(Square.eType.Deraumere, 0);
        content.put(Square.eType.Sibur, 0);
        content.put(Square.eType.Mendiane, 0);
        content.put(Square.eType.Phiras, 0);
        content.put(Square.eType.Thystame, 0);
    }

    @Override
    public void act(float delta) {
        Animation currentAnimation = player_animation.get(_dir);

        state_time += delta;

        if (_oldPos != _pos) {
            currentFrame = currentAnimation.getKeyFrame(state_time, true);
        }
        else {
            currentFrame = player_static.get(_dir);
        }
    }

    public void draw(SpriteBatch batch, float parentAlpha) {
        Sprite current = new Sprite(currentFrame);

        matrix4.set(defaultMat);
        current.setSize(1f, 1f);

        matrix4.translate(_pos.x + 0.2f + randPos.x, 0, -_pos.y + randPos.y);
        matrix4.rotate(rotation, 45);

        batch.setTransformMatrix(matrix4);

        current.draw(batch);
    }

    public Boolean setItem(Square.eType type, Integer number) {
        content.put(type, number);
        return true;
    }

    public void setSelected(boolean s) {
        selected = s;
    }
    public Map<Square.eType, Integer> getContent () {
        return content;
    }

    public boolean isSelected() {
        return selected;
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
