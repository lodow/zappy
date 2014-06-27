package com.mygdx.game;

import com.badlogic.gdx.Game;

/**
 * Created by debas_e on 24/06/2014.
 */
public class Zappy extends Game {

        @Override
        public void create() {
            Assets.Load();
            setScreen(new MainMenuScreen(this));
        }

        @Override
        public void dispose () {
            super.dispose();

            getScreen().dispose();
        }
}
