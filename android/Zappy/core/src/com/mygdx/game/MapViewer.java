package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.Intersector;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.math.collision.Ray;

import java.io.IOException;
import java.util.List;

import manage.map.Map;
import manage.map.Network;
import manage.map.Player;

/**
 * Created by debas_e on 27/06/2014.
 */
public class MapViewer implements Screen {

    private Zappy game;
    private Network network;
    private MainMenuScreen menu_screen;
    private OrthographicCamera camera;
    private Player player;
    private Player player1;
    private SpriteBatch batch;
    private Sprite groundSprite[][];
    private Matrix4 groundMatrix = new Matrix4();
    private Vector2 sizeMap;
    private float zoom;
    private InputMultiplexer inputMultiplexer;

    public MapViewer(Network network, Zappy game, MainMenuScreen menu_screen) {
        this.game = game;
        this.menu_screen = menu_screen;
        this.network = network;
        this.sizeMap = network.getMap().getSize();

        this.camera = new OrthographicCamera(20, 20 * (Gdx.graphics.getHeight() / (float) Gdx.graphics.getWidth()));
        this.player = new Player(new Vector2(0, 0), "team", 0, 0, Player.eDirection.Sud);
        this.player1 = new Player(new Vector2(0, 1), "team", 0, 0, Player.eDirection.Sud);

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

        inputMultiplexer = new InputMultiplexer();

        Gdx.input.setInputProcessor(inputMultiplexer);

        MyGestureHandler gestureHandler = new MyGestureHandler();
        MapInputProcessor inputProcessor = new MapInputProcessor();

        inputMultiplexer.addProcessor(new GestureDetector(gestureHandler));
        inputMultiplexer.addProcessor(inputProcessor);
    }

    public void update(Map map, float delta) {
        camera.zoom = zoom;
        camera.update();
        batch.setProjectionMatrix(camera.combined);

        List<Player> players = map.getPlayers();

        for (Player p : players) {
            p.act(delta);
        }
        // update all element of the map : animation, matrix ...
    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        try {
            network.update();
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

    class MapInputProcessor implements InputProcessor {

        final Plane xzPlane = new Plane(new Vector3(0, 1, 0), 0);
        final Vector3 intersection = new Vector3();
        Sprite lastSelectedTile = null;
        final Vector3 curr = new Vector3();
        final Vector3 last = new Vector3(-1, -1, -1);
        final Vector3 delta = new Vector3();

        @Override
        public boolean keyDown(int keycode) {
            return false;
        }

        @Override
        public boolean keyUp(int keycode) {
            return false;
        }

        @Override
        public boolean keyTyped(char character) {
            return false;
        }

        @Override
        public boolean touchDown(int screenX, int screenY, int pointer, int button) {
            return false;
        }

        @Override
        public boolean touchDragged(int x, int y, int pointer) {
            Ray pickRay = camera.getPickRay(x, y);
            Intersector.intersectRayPlane(pickRay, xzPlane, curr);

            if (!(last.x == -1 && last.y == -1 && last.z == -1)) {
                pickRay = camera.getPickRay(last.x, last.y);
                Intersector.intersectRayPlane(pickRay, xzPlane, delta);
                delta.sub(curr);
                camera.position.add(delta.x, delta.y, delta.z);
            }
            last.set(x, y, 0);
            return false;
        }

        @Override
        public boolean touchUp(int x, int y, int pointer, int button) {
            last.set(-1, -1, -1);
            return false;
        }

        @Override
        public boolean mouseMoved(int screenX, int screenY) {
            return false;
        }

        @Override
        public boolean scrolled(int amount) {
            return false;
        }
    }

    class MyGestureHandler implements GestureDetector.GestureListener {

        public float initialScale = 1.0f;

        @Override
        public boolean touchDown(float x, float y, int pointer, int button) {

            initialScale = zoom;

            return false;
        }

        @Override
        public boolean tap(float x, float y, int count, int button) {
            return false;
        }

        @Override
        public boolean longPress(float x, float y) {
            return false;
        }

        @Override
        public boolean fling(float velocityX, float velocityY, int button) {
            return false;
        }

        @Override
        public boolean pan(float x, float y, float deltaX, float deltaY) {
            return false;
        }

        @Override
        public boolean panStop(float x, float y, int pointer, int button) {
            return false;
        }

        @Override
        public boolean zoom(float initialDistance, float distance) {

            //Calculate pinch to zoom
            float ratio = initialDistance / distance;

            //Clamp range and set zoom
            zoom = MathUtils.clamp(initialScale * ratio, 0.1f, 1.0f);

            return true;
        }

        @Override
        public boolean pinch(Vector2 initialPointer1, Vector2 initialPointer2, Vector2 pointer1, Vector2 pointer2) {
            return false;
        }
    }
}
