package com.mygdx.game;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input.TextInputListener;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class TextInputDialogTest implements ApplicationListener {
    String message;
    SpriteBatch batch;
    BitmapFont font;

    public void create () {
        message = "Touch screen for dialog";
        batch = new SpriteBatch();
        font = new BitmapFont();
    }

    @Override
    public void resize(int width, int height) {

    }

    public void render () {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        batch.begin();
        font.draw(batch, message, 10, 40);
        batch.end();

        if (Gdx.input.justTouched()) {
            Gdx.input.getTextInput(new TextInputListener() {
                @Override
                public void input (String text) {
                    message = "message: " + text + ", touch screen for new dialog";
                }

                @Override
                public void canceled () {
                    message = "cancled by user";
                }
            }, "enter something funny", "funny");
        }
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

    public boolean needsGL20 () {
        return false;
    }

}