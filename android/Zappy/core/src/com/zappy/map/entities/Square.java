package com.zappy.map.entities;

import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.zappy.assets.Assets;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Set;

/**
 * Created by max on 27/06/14.
 */
public class Square extends Actor {
    public enum eType
    {
        Nourriture,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    private float stateTime = 0;
    private Map<eType, Matrix4> transform = new HashMap<eType, Matrix4>();
    private Map<eType, Integer> content = new HashMap<eType, Integer>();
    private Map<eType, Sprite> sprite_ressource = new HashMap<eType, Sprite>();
    private HashMap<String, Animation> incantationAnimations = new HashMap<String, Animation>();
    private Vector2 pos;
    private Incantation incantation = null;

    public Square(Vector2 pos) {

        this.pos = pos;

        TextureRegion ressource = Assets.ressource;
        this.sprite_ressource.put(Square.eType.Deraumere, (new Sprite(ressource, 0, 24, 22, 43 - 24)));
        this.sprite_ressource.put(Square.eType.Linemate, (new Sprite(ressource, 52, 0, 73 - 52, 18)));
        this.sprite_ressource.put(Square.eType.Mendiane, (new Sprite(ressource, 26, 0, 47 - 26, 19)));
        this.sprite_ressource.put(Square.eType.Phiras, (new Sprite(ressource, 102, 24, 124 - 102, 43 - 24)));
        this.sprite_ressource.put(Square.eType.Sibur, (new Sprite(ressource, 52, 49, 73 - 52, 66 - 49)));
        this.sprite_ressource.put(Square.eType.Thystame, (new Sprite(ressource, 78, 49, 98 - 78, 66 - 49)));

        incantationAnimations = Assets.getIncantationAnimation();

        for (int i = 0; i < 7; i++) {
            transform.put(eType.values()[i], new Matrix4());
        }

        Random rand = new Random();
        int random = rand.nextInt(Assets.food.size());

        sprite_ressource.put(eType.Nourriture, new Sprite(Assets.food.get(random)));

        Sprite tmpSprite; Matrix4 tmpMat;

        tmpSprite = sprite_ressource.get(eType.Deraumere); tmpSprite.setSize(0.25f, 0.35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 9.8f, pos.x + 5.0f);

        tmpSprite = sprite_ressource.get(eType.Linemate); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 9.3f, pos.x + 5.15f);

        tmpSprite = sprite_ressource.get(eType.Mendiane); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 9.65f, pos.x + 5.3f);

        tmpSprite = sprite_ressource.get(eType.Phiras); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 9.45f, pos.x + 5.0f);

        tmpSprite = sprite_ressource.get(eType.Sibur); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 8.65f, pos.x + 5.6f);

        tmpSprite = sprite_ressource.get(eType.Thystame); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y - 8.15f, pos.x + 4.6f);

        tmpSprite = sprite_ressource.get(eType.Nourriture); tmpSprite.setSize(.25f, .35f);
        tmpSprite.rotate(45); tmpSprite.setPosition(pos.y + 0.8f - 7.0f, pos.x + 0.25f + 3.0f);

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

    public void draw(Batch batch) {
        for (eType type : eType.values()) {
            int number = content.get(type);
            if (number > 0) {
                Sprite sprite = sprite_ressource.get(type);
                sprite.draw(batch);
            }
        }
    }

    public Integer getItem(eType type) {
        return content.get(type);
    }

    public Set getItems() {
        return content.entrySet();
    }

    public void setIncentation(boolean bool) {
        if (bool == true) {
            System.out.println("incantation on : " + pos.toString());
            int rand = (int)(Math.random() * 2);
            incantation = new Incantation(incantationAnimations.get((rand == 1 ? "fire" : "tornado")));
        } else {
            incantation = null;
        }
    }

    public Incantation getIncantation() {
        return incantation;
    }

    public class Incantation {
        private Animation incantation = null;
        private Sprite currentFrame = new Sprite();
        private Matrix4 matrix4 = new Matrix4(), defaultMat = new Matrix4();
        private Vector3 rotation = new Vector3(0, 1, 0);

        Incantation(Animation incantation) {
            this.incantation = incantation;
        }

        public void draw(Batch batch, float delta) {
            matrix4.set(defaultMat);

            matrix4.translate(pos.y + 0.2f, 0, -pos.x - 0.2f);
            matrix4.rotate(rotation, 45);
            TextureRegion tmp = incantation.getKeyFrame(stateTime, true);
            stateTime += delta;
            currentFrame.setRegion(tmp);
            currentFrame.setSize(1, 1);

            batch.setTransformMatrix(matrix4);
            currentFrame.draw(batch);
        }
    }
}
