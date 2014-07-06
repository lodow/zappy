package com.zappy.map.entities;

import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.zappy.assets.Assets;

import java.util.HashMap;
import java.util.Map;
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

    private Vector2 pos;
    private Map<eType, Matrix4> transform = new HashMap<eType, Matrix4>();
    private Map<eType, Integer> content = new HashMap<eType, Integer>();
    private Map<eType, Sprite> sprite_ressource;
    public Square(Vector2 pos) {
        this.pos = pos;
        this.sprite_ressource = Assets.getSpriteRessource();

        for (int i = 0; i < 7; i++) {
            transform.put(eType.values()[i], new Matrix4());
        }

        Sprite tmpSprite; Matrix4 tmpMat;
        tmpSprite = sprite_ressource.get(eType.Deraumere); tmpSprite.setSize(.5f, .35f);
        tmpMat = transform.get(eType.Deraumere); tmpMat.translate(pos.x + 0.13f, 0, -pos.y + 0.13f); tmpMat.rotate(new Vector3(0, 1, 0), 45);


        content.put(eType.Nourriture, 0);
        content.put(eType.Linemate, 0);
        content.put(eType.Deraumere, 1);
        content.put(eType.Sibur, 0);
        content.put(eType.Mendiane, 0);
        content.put(eType.Phiras, 0);
        content.put(eType.Thystame, 0);
    }

    public Boolean setItem(eType type, Integer number) {
        content.put(type, number);
        return true;
    }

    @Override
    public void draw(Batch batch, float parentAlpha) {

/*        for (int i = 0; i < 7; i++) {
            eType type = eType.values()[i];
            int number = content.get(type);
            if (number > 0) {
                Sprite sprite = sprite_ressource.get(type);
                Matrix4 tmp = transform.get(type);
                batch.setTransformMatrix(tmp);
                sprite.draw(batch);
            }
        }*/
        int number = content.get(eType.Deraumere);
        for (int i = 0; i < 7; i++) {
            eType type = eType.values()[i];
            System.out.println(content.get(type));
        }
        if (number > 0) {
            Sprite sprite = sprite_ressource.get(eType.Deraumere);
            Matrix4 tmp = transform.get(eType.Deraumere);
            batch.setTransformMatrix(tmp);
            sprite.draw(batch);
        }
    }

    public Integer getItem(eType type) {
        return content.get(type);
    }

    public Set getItems() {
        return content.entrySet();
    }
}
