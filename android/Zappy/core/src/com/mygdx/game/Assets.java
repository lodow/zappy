package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.graphics.g2d.BitmapFont;

/**
 * Created by debas_e on 27/06/2014.
 */
public class Assets {
    public static BitmapFont pokeFont;
    public static Music ambientMusic;

    public static void Load() {
        pokeFont = new BitmapFont(Gdx.files.internal("data/pokemon_100.fnt"), false);
        ambientMusic = Gdx.audio.newMusic(Gdx.files.internal("data/music.ogg"));
    }
}
