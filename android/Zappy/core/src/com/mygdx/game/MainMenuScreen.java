package com.mygdx.game;

import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector3;

/**
 * Created by debas_e on 24/06/2014.
 */
public class MainMenuScreen implements Screen {

    private Game game;
    private OrthographicCamera guiCam;
    private SpriteBatch batcher;
    private Rectangle ipBounds;
    private Rectangle portBounds;
    private Rectangle launchBounds;
    private Vector3 touchPoint;
    private Texture background;
    private TextureRegion backgroundRegion;
    private String ip, port;

    public MainMenuScreen(Game game) {
        this.game = game;
        background = new Texture(Gdx.files.internal("data/zappy_menu.png"));
        this.backgroundRegion = new TextureRegion(background, 0, 0, 1920, 1080);

        ipBounds = new Rectangle(350, 615, 550, 130);
        portBounds = new Rectangle(350, 380, 550, 130);
        touchPoint = new Vector3();

        guiCam = new OrthographicCamera(1920, 1080);
        guiCam.position.set(1920 / 2, 1080 / 2, 0);
        batcher = new SpriteBatch();
        ip = "";
        port = "";

        Assets.pokeFont.setColor(Color.valueOf("f7f92c"));
        Assets.pokeFont.scale(-0.5f);
        Assets.ambientMusic.setLooping(true);
        Assets.ambientMusic.play();
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
        batcher.draw(backgroundRegion, 0, 0, 1920, 1080);
        batcher.end();

        batcher.enableBlending();
        batcher.begin();

        Assets.pokeFont.draw(batcher, (ip.length() > 0 ? ip : "tap to edit"), 400, 580);
        Assets.pokeFont.draw(batcher, (port.length() > 0 ? port : "tap to edit"), 400, 330);

        batcher.end();
/*        batcher.enableBlending();
        batcher.begin();
        batcher.draw(Assets.logo, 160 - 274 / 2, 480 - 10 - 142, 274, 142);
        batcher.draw(Assets.mainMenu, 10, 200 - 110 / 2, 300, 110);
        batcher.draw(Settings.soundEnabled ? Assets.soundOn : Assets.soundOff, 0, 0, 64, 64);
        batcher.end();
*/
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
