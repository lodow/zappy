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
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

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
    private Vector2 _realPos = new Vector2(0, 0);
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
    private Queue<SmoothMove> smoothMoves = new LinkedList<SmoothMove>();

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

        if (smoothMoves.size() > 0) {
            currentFrame = currentAnimation.getKeyFrame(state_time, true);
            state_time += delta;
        }
        else {
            currentFrame = player_static.get(_dir);
            state_time = 0;
        }
    }

    public void draw(SpriteBatch batch, Vector2 sizeMap) {
        Sprite current = new Sprite(currentFrame);

        matrix4.set(defaultMat);
        current.setSize(1f, 1f);

        if (smoothMoves.size() > 0) {
            SmoothMove tmp = smoothMoves.peek();
            float delta = 1.0f / tmp.totalIteration;

            if (tmp.currentIteration > 0) {
                switch (tmp.dir) {
                    case Nord :
                        if (_pos.y - delta < 0)
                            _pos.y = sizeMap.y - 1 + delta * tmp.currentIteration;
                        _pos.y -= delta;
                        break;
                    case Sud :
                        if (_pos.y + delta > sizeMap.y - 1)
                            _pos.y =  - delta * tmp.currentIteration;
                        _pos.y += delta;
                        break;
                    case Est :
                        if (_pos.x + delta > sizeMap.x - 1)
                            _pos.x = - delta * tmp.currentIteration;
                        _pos.x += delta;
                        break;
                    case Ouest :
                        if (_pos.x - delta < 0)
                            _pos.x = sizeMap.x  - 1 + delta * tmp.currentIteration;
                        _pos.x -= delta;
                        break;
                }
                tmp.currentIteration--;
            } else {
                smoothMoves.poll();
            }
        }

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

        if (this._realPos.x != _pos.x || this._realPos.y != _pos.y) {
            this._realPos.x = _pos.x;
            this._realPos.y = _pos.y;
            this.smoothMoves.add(new SmoothMove(this._dir, 32));
        }
    }

    private class SmoothMove {
        public eDirection dir;
        public int currentIteration = 0;
        public int totalIteration = 0;

        SmoothMove(eDirection dir, int iterate) {
            this.dir = dir;
            this.currentIteration = iterate;
            this.totalIteration = iterate;
        }
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
