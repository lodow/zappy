package com.zappy.screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.Intersector;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.math.collision.Ray;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.zappy.InputCam.MapGestureHandler;
import com.zappy.InputCam.MapInputProcessor;
import com.zappy.Zappy;
import com.zappy.assets.Assets;
import com.zappy.map.Map;
import com.zappy.map.entities.Egg;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;
import com.zappy.network.Network;
import com.zappy.screen.popup.PopUpInformation;
import com.zappy.screen.popup.ReturnDialog;
import com.zappy.screen.popup.winDialog;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MapViewer implements Screen {

    private Zappy game;
    private Network network;
    private OrthographicCamera camera;
    private SpriteBatch batch;
    private Sprite groundSprite[][];
    private Matrix4 groundMatrix = new Matrix4();
    private Vector2 sizeMap;

    private final Plane xzPlane = new Plane(new Vector3(0, 1, 0), 0);
    private final Vector3 intersection = new Vector3();
    private Sprite lastSelectedTile = null;
    private Skin skin;
    private BitmapFont font = new BitmapFont();
    private PopUpInformation info;
    private Player playerSelected = null;
    private boolean back = false, endOfGame = false;
    private ReturnDialog returnDialog;
    private winDialog winDialog;
    private Stage returnStage = new Stage(), winStage = new Stage();
    private List<Square.Incantation> incatationList = new ArrayList<Square.Incantation>();
    private List<Player.BroadCast> broadCastList = new ArrayList<Player.BroadCast>();

    public MapViewer(Network network, Zappy game, Skin skin) {
        this.game = game;
        this.network = network;
        this.sizeMap = network.getMap().getSize();
        this.skin = skin;
        this.font.setColor(Color.RED);
        this.font.scale(2);
        this.info = new PopUpInformation(skin);
        this.camera = new OrthographicCamera(20, 20 * (Gdx.graphics.getHeight() / (float) Gdx.graphics.getWidth()));

        this.camera.position.set(sizeMap.x / 2 + 10, 10, -sizeMap.y / 2 + 10);
        this.camera.direction.set(-1, -1, -1);
        this.camera.near = 1;
        this.camera.far = 100;

        groundSprite = new Sprite[(int) sizeMap.y][(int) sizeMap.x];
        for (int z = 0; z < sizeMap.y; z++) {
            for (int x = 0; x < sizeMap.x; x++) {
                groundSprite[z][x] = new Sprite(Assets.ground);
                groundSprite[z][x].setPosition(x, z);
                groundSprite[z][x].setSize(1, 1);
            }
        }

        batch = new SpriteBatch();

        groundMatrix.setToRotation(new Vector3(1, 0, 0), -90);

        returnDialog = new ReturnDialog("", skin);
        winDialog = new winDialog("", skin);
        initaliseInputProcessors();

    }

    public void initaliseInputProcessors() {

        InputMultiplexer inputMultiplexer = new InputMultiplexer();

        Gdx.input.setInputProcessor(inputMultiplexer);

        MapGestureHandler gestureHandler = new MapGestureHandler(camera);
        MapInputProcessor inputProcessor = new MapInputProcessor(camera);

        inputMultiplexer.addProcessor(new GestureDetector(gestureHandler));
        inputMultiplexer.addProcessor(inputProcessor);
        inputMultiplexer.addProcessor(info);
        inputMultiplexer.addProcessor(returnStage);
        inputMultiplexer.addProcessor(winStage);

        Gdx.input.setCatchBackKey(true);
    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        Gdx.gl.glClearColor(1, 1, 1, 1);

        Assets.soundController.draw(batch, this);

        if (Gdx.input.isKeyPressed(Input.Keys.BACK) && !back) {
            back = true;
            returnDialog.setShowing(true);
            returnDialog.show(returnStage);
        }

        try {
            network.update();
        } catch (IOException e) {
            System.err.println("You've been disconnected");
            game.setScreen(new MainMenuScreen(game));
            e.printStackTrace();
        }

         Map map = network.getMap();

        // map resized ?
        if (!map.getSize().equals(sizeMap)) {
            sizeMap = map.getSize();

            this.camera.position.set(sizeMap.x / 2 + 10, 10, -sizeMap.y / 2 + 10);

            groundSprite = new Sprite[(int) sizeMap.y][(int) sizeMap.x];
            for (int z = 0; z < sizeMap.y; z++) {
                for (int x = 0; x < sizeMap.x; x++) {
                    groundSprite[z][x] = new Sprite(Assets.ground);
                    groundSprite[z][x].setPosition(x, z);
                    groundSprite[z][x].setSize(1, 1);
                }
            }
        }

        camera.update();
        batch.setProjectionMatrix(camera.combined);

        // draw ground
        batch.setTransformMatrix(groundMatrix);
        batch.disableBlending();

        batch.begin();
        for (int z = 0; z < sizeMap.y; z++) {
            for (int x = 0; x < sizeMap.x; x++) {
                groundSprite[z][x].draw(batch);
            }
        }

        batch.enableBlending();

        List<Player> currentPlayer = map.getPlayers();
        boolean touched =  checkTileTouched(), selected = false, dead = true;

        // draw ressource
        Square[][] square = map.getSquare();
        for (Square[] aSquare : square)
            for (Square anASquare : aSquare) {
                anASquare.draw(batch);
                Square.Incantation incantation = anASquare.getIncantation();
                if (incantation != null) incatationList.add(incantation);
            }

        //draw eggs
        List<Egg> egg = map.getEggs();
        if (currentPlayer.size() > 0) {
            for (Egg anEgg : egg) {
                anEgg.draw(batch);
            }
        }

        for (Player p : currentPlayer) {
            Vector2 playerPos = p.get_pos();

            Player.BroadCast b = p.getBroadCast();
            if (b != null) broadCastList.add(b);

            if (touched && intersection.x == (int)playerPos.x && intersection.z == (int)-playerPos.y && !selected) {
                p.setSelected(true);
                selected = true;
            } else if (touched) {
                p.setSelected(false);
            }
            if (p.isSelected()) {
                info.setShowing(true);
                playerSelected = p;
                if(lastSelectedTile != null)
                    lastSelectedTile.setColor(1, 1, 1, 1);
                Sprite sprite = groundSprite[(int)playerPos.y][(int)playerPos.x];
                sprite.setColor(1, 0, 0, 1);
                lastSelectedTile = sprite;
            }
            if (lastSelectedTile != null) {
                if (lastSelectedTile.getX() == (int)playerPos.x && lastSelectedTile.getY() == (int)playerPos.y) {
                    dead = false;
                }
            }
            p.act(delta, network.getServTime(), sizeMap);
            p.draw(batch);
        }

        if (dead && lastSelectedTile != null) {
            lastSelectedTile.setColor(1, 1, 1, 1);
            info.setShowing(false);
        }

        for (Square.Incantation i : incatationList) {
            i.draw(batch, delta);
        }
        for (Player.BroadCast b : broadCastList) {
            b.draw(batch);
        }

        broadCastList.clear();
        incatationList.clear();

        batch.end();

        batch.setTransformMatrix(new Matrix4());
        batch.setProjectionMatrix(new Matrix4().setToOrtho2D(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight()));

        batch.begin();
        font.draw(batch, "FPS : " + Gdx.graphics.getFramesPerSecond(), 0, Gdx.graphics.getHeight());
        batch.end();

        if (!info.isShowing()) {
            if (lastSelectedTile != null)
                lastSelectedTile.setColor(1, 1, 1, 1);
            lastSelectedTile = null;
        } else if (!dead && lastSelectedTile != null) {
            info.update(playerSelected);
            info.act(delta);
            info.draw();
        }

        if (back) {
            if (returnDialog.isShowing()) {
                returnStage.act(delta);
                returnStage.draw();
            } else {
                back = false;
                boolean result = returnDialog.getResult();
                if (result) {
                    Assets.gameMusic.stop();
                    Assets.menuMusic.play();
                    game.setScreen(new MainMenuScreen(game));
                } else {
                    returnDialog.resetButton();
                }
            }
        }

        if (map.getEndOfGame().length() > 0) {
            if (!endOfGame) {
                winDialog.setShowing(true);
                winDialog.setLabelText("Team \"" + map.getEndOfGame() + "\" win the game !");
                winDialog.show(winStage);
                endOfGame = true;
            } else {
                if (winDialog.isShowing()) {
                    winStage.act(delta);
                    winStage.draw();
                } else {
                    Assets.gameMusic.stop();
                    game.setScreen(new MainMenuScreen(game));
                }
            }
        }
    }

    private boolean checkTileTouched() {
        if(Gdx.input.justTouched()) {
            Ray pickRay = camera.getPickRay(Gdx.input.getX(), Gdx.input.getY());
            Intersector.intersectRayPlane(pickRay, xzPlane, intersection);
            intersection.x = (int)intersection.x;
            intersection.z = (int)intersection.z;
            return true;
        }
        return false;
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
        Assets.gameMusic.dispose();
        info.dispose();
        skin.dispose();
        returnStage.dispose();
        winStage.dispose();
    }
}
