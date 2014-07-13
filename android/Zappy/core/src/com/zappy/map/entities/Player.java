package com.zappy.map.entities;

import com.badlogic.gdx.Gdx;
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


    private float servTime = 0;
    private float frameDuration = 0;
    private boolean selected = false;
    private Vector2 _realPos;
    private Vector2 _pos;
    private String _team;
    private int _id;
    private int _level;
    private eDirection _dir;
    private HashMap<eDirection, Animation> player_animation;
    private HashMap<eDirection, Sprite> player_static;
    private float state_time = 0;
    private TextureRegion currentFrame;
    private Map<Square.eType, Integer> content = new HashMap<Square.eType, Integer>();
    private Matrix4 matrix4 = new Matrix4(), defaultMat = new Matrix4();
    private Vector3 rotation = new Vector3(0, 1, 0);
    private Vector2 randPos = new Vector2();
    private Queue<SmoothMove> smoothMoves = new LinkedList<SmoothMove>();
    private Sprite current = new Sprite();
    private Sprite broadCastSprite;
    private Vector2 sizeMap = null;
    private BroadCast broadCast = null;

    public Player(Vector2 pos, String team, int id, int level, eDirection dir) {
        _pos = pos;
        _realPos = pos;
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

        broadCastSprite = new Sprite(Assets.broadCast);
        broadCastSprite.setSize(1, 1);
        broadCastSprite.setPosition(0, 0.8f);
    }

    public void act(float delta, float servTime, Vector2 sizeMap) {
        this.sizeMap = sizeMap;
        if (this.servTime != servTime) {
            this.servTime = servTime;
            if (servTime < 100) {
                frameDuration = (servTime + 100) * 0.06f / 100.0f;
            } else {
                frameDuration = servTime * 0.06f / 100.0f;
            }
        }

        if (smoothMoves.size() > 0) {
            eDirection tmp = smoothMoves.peek().dir;
            Animation currentAnimation = player_animation.get(tmp);

            currentAnimation.setFrameDuration(frameDuration);
            currentFrame = currentAnimation.getKeyFrame(state_time, true);
            state_time += delta;
        }
        else {
            currentFrame = player_static.get(_dir);
            state_time = 0;
        }
    }

    public void draw(SpriteBatch batch) {
        current.setRegion(currentFrame);

        matrix4.set(defaultMat);
        current.setSize(1f, 1f);

        if (smoothMoves.size() > 0) {
            SmoothMove tmp = smoothMoves.peek();
            float delta = Gdx.graphics.getDeltaTime() * (servTime / 7.0f);

            tmp.distParcouru += delta;

            if (tmp.distParcouru < tmp.dist && smoothMoves.size() <= 5) {
                switch (tmp.dir) {
                    case Nord:
                        if (_pos.y - delta < 0)
                            _pos.y = sizeMap.y - 1 + tmp.dist - tmp.distParcouru;
                        _pos.y -= delta;
                        break;
                    case Sud:
                        if (_pos.y + delta > sizeMap.y - 1)
                            _pos.y = -tmp.dist - tmp.distParcouru;
                        _pos.y += delta;
                        break;
                    case Est:
                        if (_pos.x + delta > sizeMap.x - 1)
                            _pos.x = -tmp.dist - tmp.distParcouru;
                        _pos.x += delta;
                        break;
                    case Ouest:
                        if (_pos.x - delta < 0)
                            _pos.x = sizeMap.x - 1 + tmp.dist - tmp.distParcouru;
                        _pos.x -= delta;
                        break;
                }
            } else {
                _pos.x = tmp.posToGo.x;
                _pos.y = tmp.posToGo.y;
                smoothMoves.poll();
            }
        }

        matrix4.translate(_pos.x + 0.2f + randPos.x, 0, -_pos.y + randPos.y);
        matrix4.rotate(rotation, 45);

        batch.setTransformMatrix(matrix4);

        current.draw(batch);

        if (broadCast != null && broadCast.getElapsedTime() > (7.0f / servTime)) {
                broadCast = null;
            }
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
        if (_pos.x < 0 || _pos.y < 0) {
            System.err.println(_pos.toString());
        } else if (!this._realPos.equals(_pos)) {
            this._realPos = _pos;
            this.smoothMoves.add(new SmoothMove(this._dir, 1.0f, _pos));
          }
    }

    private class SmoothMove {
        public eDirection dir;
        public float distParcouru = 0;
        public float dist;
        public Vector2 posToGo;

        SmoothMove(eDirection dir, float distance, Vector2 posToGo) {
            this.dir = dir;
            this.dist = distance;
            this.posToGo = posToGo;
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
        if (sizeMap == null || _pos.x < 0 ||_pos.y < 0 || (_pos.x > sizeMap.x - 1) || (_pos.y > sizeMap.y - 1)) {
            return _realPos;
        } else {
            return _pos;
        }
    }

    public void createBrodcast() {
//        System.out.println("broadcast");
        if (broadCast == null) {
            broadCast = new BroadCast();
        }
    }

    public BroadCast getBroadCast() {
        return broadCast;
    }

    public class BroadCast {
        private Matrix4 matBroad;
        private float broadCastTime = 0;

        BroadCast() {
            matBroad = new Matrix4();
            matBroad.translate(_pos.x + 0.2f + randPos.x, 0, -_pos.y + randPos.y);
            matBroad.rotate(rotation, 45);
        }

        public void draw(Batch batch) {
            batch.setTransformMatrix(matBroad);
            broadCastSprite.draw(batch);
            broadCastTime += Gdx.graphics.getDeltaTime();
            broadCastSprite.draw(batch);
        }

        public float getElapsedTime() {
            return this.broadCastTime;
        }
    }
}
