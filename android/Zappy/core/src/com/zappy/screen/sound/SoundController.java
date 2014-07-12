package com.zappy.screen.sound;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Rectangle;
import com.zappy.assets.Assets;
import com.zappy.screen.MainMenuScreen;

import java.util.HashMap;

/**
 * Created by debas_e on 12/07/2014.
 */
public class SoundController {
    private HashMap<Boolean, TextureRegion> soundImage = new HashMap<Boolean, TextureRegion>();
    private boolean sound;
    Rectangle rec = new Rectangle(Gdx.graphics.getWidth() - 100, Gdx.graphics.getHeight() - 100, 90, 90);

    public SoundController() {
        soundImage.put(true, Assets.soundOn);
        soundImage.put(false, Assets.soundOff);

        sound = true;
    }

    private void update(Screen screen) {
        if (Gdx.input.justTouched()) {
            System.out.println("x: " + Gdx.input.getX() + " - y:" + Gdx.input.getY());
            if ((Gdx.input.getX() >= rec.x && Gdx.input.getX() <= rec.x + rec.width) &&
                    (Gdx.graphics.getHeight() - Gdx.input.getY() >= rec.y && (Gdx.graphics.getHeight() - Gdx.input.getY()) <= rec.y + rec.getHeight())) {
                sound = !sound;
                if (sound) {
                    if (screen instanceof MainMenuScreen) {
                        Assets.menuMusic.setVolume(1);
                    } else {
                        Assets.gameMusic.setVolume(1);
                    }
                } else {
                    if (screen instanceof MainMenuScreen) {
                        Assets.menuMusic.setVolume(0);
                    } else {
                        Assets.gameMusic.setVolume(0);
                    }
                }
            }
        }
    }

    public void draw(Batch batch, Screen screen) {
        TextureRegion tmp = soundImage.get(sound);

        update(screen);
        batch.begin();
        batch.draw(tmp, (float) rec.x, (float) rec.y, (float) rec.getWidth(), (float) rec.getHeight());
        batch.end();
    }
}
