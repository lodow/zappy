package com.zappy.map.entities;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.zappy.assets.Assets;

import java.util.HashMap;

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

    private Vector2 _pos;
    private String _team;
    private int _id;
    private int _level;
    private eDirection _dir;
    private HashMap<eDirection, Animation> player_animation;
    private float state_time = 0;
    private TextureRegion currentFrame;
    private SpriteBatch batch = new SpriteBatch();

    public Player(Vector2 pos, String team, int id, int level, eDirection dir) {
        _pos = pos;
        _team = team;
        _id = id;
        _level = level;
        _dir = dir;
        player_animation = Assets.getAnimationPlayer();
    }

    @Override
    public void act(float delta) {
        Animation currentAnimation = player_animation.get(_dir);

        state_time += delta;
        currentFrame = currentAnimation.getKeyFrame(state_time, true);
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {
        Sprite current = new Sprite(currentFrame);
        Matrix4 matTmp = new Matrix4();

        current.setSize(1f, 1f);

        matTmp.translate(_pos.x, 0, -_pos.y);
        matTmp.rotate(new Vector3(0, 1, 0), 45);

//        Matrix4 old = batch.getTransformMatrix();

        batch.setTransformMatrix(matTmp);

        batch.begin();
        current.draw(batch);
        batch.end();

//        batch.setTransformMatrix(old);
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
