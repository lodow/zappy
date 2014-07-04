package com.zappy.screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.zappy.InputCam.MapGestureHandler;
import com.zappy.InputCam.MapInputProcessor;
import com.zappy.Zappy;
import com.zappy.assets.Assets;
import com.zappy.map.Map;
import com.zappy.map.entities.Player;
import com.zappy.network.Network;

import java.io.IOException;
import java.util.List;

public class MapViewer implements Screen {

    private Zappy game;
    private Network network;
    private MainMenuScreen menu_screen;
    private OrthographicCamera camera;
    private SpriteBatch batch;
    private Sprite groundSprite[][];
    private Matrix4 groundMatrix = new Matrix4();
    private Vector2 sizeMap;
    private float zoom;

    public MapViewer(Network network, Zappy game, MainMenuScreen menu_screen) {
        this.game = game;
        this.menu_screen = menu_screen;
        this.network = network;
        this.sizeMap = network.getMap().getSize();

        this.camera = new OrthographicCamera(20, 20 * (Gdx.graphics.getHeight() / (float) Gdx.graphics.getWidth()));

        this.camera.position.set(5, 5, 10);
        this.camera.direction.set(-1, -1, -1);
        this.camera.near = 1;
        this.camera.far = 100;

        groundSprite = new Sprite[(int) sizeMap.y][(int) sizeMap.x];
        for (int z = 0; z < sizeMap.y; z++) {
            for (int x = 0; x < sizeMap.x; x++) {
                groundSprite[x][z] = new Sprite(Assets.ground);
                groundSprite[x][z].setPosition(x, z);
                groundSprite[x][z].setSize(1, 1);
            }
        }

        batch = new SpriteBatch();

        groundMatrix.setToRotation(new Vector3(1, 0, 0), -90);

        zoom = camera.zoom;

        initaliseInputProcessors();
    }

    public void initaliseInputProcessors() {

        InputMultiplexer inputMultiplexer = new InputMultiplexer();

        Gdx.input.setInputProcessor(inputMultiplexer);

        MapGestureHandler gestureHandler = new MapGestureHandler(camera);
        MapInputProcessor inputProcessor = new MapInputProcessor(camera);

        inputMultiplexer.addProcessor(new GestureDetector(gestureHandler));
        inputMultiplexer.addProcessor(inputProcessor);
    }

    public void update(Map map, float delta) {
        camera.update();
        batch.setProjectionMatrix(camera.combined);

        List<Player> players = map.getPlayers();
        System.out.println("players : " + players.size());

        for (Player p : players) {
            p.act(delta);
        }
        // update all element of the map : animation, matrix ...
    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        try {
//            long startTime = System.currentTimeMillis();
            network.update();
//            long endTime = System.currentTimeMillis();
            //System.out.println("That took " + (endTime - startTime) + " milliseconds");
        } catch (IOException e) {
            // implementer pop up
            System.err.println("You've been disconnected");
            game.setScreen(menu_screen);
            e.printStackTrace();
        }
        Map map = network.getMap();
        update(map, delta);

        batch.setTransformMatrix(groundMatrix);

        batch.begin();
        for (int z = 0; z < sizeMap.y; z++) {
            for (int x = 0; x < sizeMap.x; x++) {
                groundSprite[x][z].draw(batch);
            }
        }
        batch.end();

        List<Player> players = map.getPlayers();
        for (Player p : players) {
            p.draw(batch, delta);
        }
        // draw all element of the map ...
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
