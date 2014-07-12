package com.zappy.screen.sound;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Rectangle;
import com.zappy.assets.Assets;

import java.util.HashMap;

/**
 * Created by debas_e on 12/07/2014.
 */
public class SoundController {
    private HashMap<Boolean, TextureRegion> soundImage = new HashMap<Boolean, TextureRegion>();
    private boolean sound;
    Rectangle rec = new Rectangle(Gdx.graphics.getWidth() - 100, Gdx.graphics.getHeight() - 100, 90, 90);
//    Rectangle rec = new Rectangle(0, 0, 100, 100);

    public SoundController() {
        soundImage.put(true, Assets.soundOn);
        soundImage.put(false, Assets.soundOff);
    }

    public void draw(Batch batch) {

        if (Gdx.input.justTouched()) {
            System.out.println("x: " + Gdx.input.getX() + " - y:" + Gdx.input.getY());
            if ((Gdx.input.getX() >= rec.x && Gdx.input.getX() <= rec.x + rec.width) &&
                (Gdx.graphics.getHeight() - Gdx.input.getY() >= rec.y + rec.getHeight() && (Gdx.graphics.getHeight() - Gdx.input.getY()) >= rec.y)) {
                sound = !sound;
            }
        }
        TextureRegion tmp = soundImage.get(sound);

        batch.begin();
        batch.draw(tmp, (float) rec.x, (float) rec.y, (float) rec.getWidth(), (float) rec.getHeight());
        batch.end();
    }
}
