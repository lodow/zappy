package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector3;

/**
 * Created by debas_e on 24/06/2014.
 */
public class MainMenuScreen implements Screen {

    private Zappy game;
    private OrthographicCamera guiCam;
    private SpriteBatch batcher;
    private Rectangle ipBounds;
    private Rectangle portBounds;
    private Rectangle soundBounds;
    private Rectangle launchBounds;
    private Vector3 touchPoint;
    private String ip, port;

    public MainMenuScreen(Zappy game) {
        this.game = game;

        ipBounds = new Rectangle(350, 615, 550, 130);
        portBounds = new Rectangle(350, 380, 550, 130);
        soundBounds = new Rectangle(Gdx.graphics.getWidth() - 135, Gdx.graphics.getHeight() - 5, 130, 130);
        launchBounds = new Rectangle(40, 1080 - 970, 400 - 40, 65);
        touchPoint = new Vector3();

        guiCam = new OrthographicCamera(1920, 1080);
        guiCam.position.set(1920 / 2, 1080 / 2, 0);
        batcher = new SpriteBatch();
        ip = "";
        port = "";

        Assets.pokeFont.setColor(Color.valueOf("f7f92c"));
        Assets.pokeFont.scale(-0.5f);
    }

    void update(float delta) {
        if (Gdx.input.justTouched()) {
            guiCam.unproject(touchPoint.set(Gdx.input.getX(), Gdx.input.getY(), 0));

//            Gdx.app.log("coord", "x : " + touchPoint.x + " - y : " + touchPoint.y);
            if (OverlapTester.pointInRectangle(ipBounds, touchPoint.x, touchPoint.y)) {
                Gdx.input.getTextInput(new Input.TextInputListener() {
                    @Override
                    public void input(String text) {
                        ip = text;
                    }

                    @Override
                    public void canceled() {
                    }
                }, "Ip Host", ip);
            }
            if (OverlapTester.pointInRectangle(portBounds, touchPoint.x, touchPoint.y)) {
                Gdx.input.getTextInput(new Input.TextInputListener() {
                    @Override
                    public void input(String text) {
                        port = text;
                    }

                    @Override
                    public void canceled() {
                    }
                }, "Port", port);
            }
            if (OverlapTester.pointInRectangle(soundBounds, touchPoint.x, touchPoint.y)) {
                if (game.music) {
                    Assets.ambientMusic.pause();
                } else {
                    Assets.ambientMusic.play();
                }
                game.music = !game.music;
            }
            if (OverlapTester.pointInRectangle(launchBounds, touchPoint.x, touchPoint.y)) {
                Gdx.app.log("Launch", "");
//                game.setScreen();
            }
        }
    }

    @Override
    public void render(float delta) {
        update(delta);
        draw();
    }

    private void draw() {
        GL20 gl = Gdx.gl;
        gl.glClearColor(1, 0, 0, 1);
        gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        guiCam.update();
        batcher.setProjectionMatrix(guiCam.combined);

        batcher.disableBlending();
        batcher.begin();
        batcher.draw(Assets.background, 0, 0, 1920, 1080);
        batcher.end();

        batcher.enableBlending();
        batcher.begin();

        Assets.pokeFont.draw(batcher, (ip.length() > 0 ? ip : "tap to edit"), 400, 580);
        Assets.pokeFont.draw(batcher, (port.length() > 0 ? port : "tap to edit"), 400, 330);

        //draw sound
        TextureRegion sound = (game.music ? Assets.soundOn : Assets.soundOff);
        batcher.draw(sound, Gdx.graphics.getWidth() - sound.getRegionWidth() - 5, Gdx.graphics.getHeight() - sound.getRegionHeight() - 5);

        if (ip.length() > 0 && port.length() > 0) {
            Assets.pokeFont.setColor(Color.valueOf("f7f92c"));
            Assets.pokeFont.draw(batcher, "Launch", 130, 130);
        }
        else {
            Assets.pokeFont.setColor(Color.valueOf("858585"));
            Assets.pokeFont.draw(batcher, "Launch", 130, 130);
            Assets.pokeFont.setColor(Color.valueOf("f7f92c"));
        }
        batcher.end();
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
