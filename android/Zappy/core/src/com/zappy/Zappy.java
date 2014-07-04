package com.zappy;

import com.badlogic.gdx.Game;
import com.zappy.assets.Assets;
import com.zappy.screen.MainMenuScreen;

/**
 * Created by debas_e on 24/06/2014.
 */
public class Zappy extends Game {

        public boolean music = true;

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
