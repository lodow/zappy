package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

/**
 * Created by debas_e on 27/06/2014.
 */
public class Assets {
    public static BitmapFont pokeFont;
    public static Music ambientMusic;
    public static TextureRegion soundOn;
    public static TextureRegion soundOff;
    public static Texture background;

    public static void Load() {
        pokeFont = new BitmapFont(Gdx.files.internal("data/pokemon_100.fnt"), false);
        ambientMusic = Gdx.audio.newMusic(Gdx.files.internal("data/music.ogg"));
        ambientMusic.setLooping(true);
        ambientMusic.play();

        Texture items = new Texture(Gdx.files.internal("data/items.png"));
        soundOn = new TextureRegion(items, 0, 0, 135, 130);
        soundOff = new TextureRegion(items, 150, 0, 135, 130);

        background = new Texture(Gdx.files.internal("data/zappy_main.png"));
    }
}
