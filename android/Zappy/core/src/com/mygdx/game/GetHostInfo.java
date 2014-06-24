package com.mygdx.game;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Screen;

/**
 * Created by debas_e on 24/06/2014.
 */
public class GetHostInfo implements Screen {

    private Game game;
    private boolean hostInput, portInput;

    public GetHostInfo(Game game) {
        this.game = game;

        hostInput = true;
        portInput = false;
    }

    void update(float delta) {
        if (hostInput == true) {
            Gdx.input.getTextInput(new Input.TextInputListener() {
                @Override
                public void input(String text) {
                    portInput = true;
                }

                @Override
                public void canceled() {
                }
            }, "Host", "");
            hostInput = false;
        }
        if (portInput == true) {
            Gdx.input.getTextInput(new Input.TextInputListener() {
                @Override
                public void input(String text) {
                }

                @Override
                public void canceled() {
                }
            }, "Port", "");
            portInput = false;
        }
        if (portInput && hostInput) {
            //change screen game to new screen
        }
    }

    @Override
    public void render(float delta) {
        update(delta);
    }

    @Override
    public void resize(int width, int height) {

    }

    @Override
    public void show() {

    }

    @Override
    public void hide() {

    }

    @Override
    public void pause() {

    }

    @Override
    public void resume() {

    }

    @Override
    public void dispose() {

    }
}
