package com.zappy.screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputMultiplexer;
import com.badlogic.gdx.Screen;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.Intersector;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Plane;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.math.collision.Ray;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.scenes.scene2d.utils.Drawable;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.zappy.InputCam.MapGestureHandler;
import com.zappy.InputCam.MapInputProcessor;
import com.zappy.Zappy;
import com.zappy.assets.Assets;
import com.zappy.map.Map;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;
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

    private final Plane xzPlane = new Plane(new Vector3(0, 1, 0), 0);
    private final Vector3 intersection = new Vector3();
    private Sprite lastSelectedTile = null;
    private Skin skin;
    private BitmapFont font = new BitmapFont();
    private Stage stage;
    private Table table;
    public MapViewer(Network network, Zappy game, MainMenuScreen menu_screen, Skin skin) {
        this.game = game;
        this.menu_screen = menu_screen;
        this.network = network;
        this.sizeMap = network.getMap().getSize();
        this.skin = skin;
        this.font.setColor(Color.RED);
        this.font.scale(2);
        this.stage = new Stage();
        this.camera = new OrthographicCamera(20, 20 * (Gdx.graphics.getHeight() / (float) Gdx.graphics.getWidth()));

        this.camera.position.set(10, 10, 20);
        this.camera.direction.set(-1, -1, -1);
        this.camera.near = 1;
        this.camera.far = 100;

        table = new Table();
        table.debug();
        Drawable patch = new TextureRegionDrawable(new TextureRegion(Assets.all, 175, 0, 50, 50));

        Image cross = new Image(new Texture(Gdx.files.internal("mainMenu/remove_cross.png")));
        cross.addListener(new ClickListener() {
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                if(lastSelectedTile != null)
                    lastSelectedTile.setColor(1, 1, 1, 1);
                lastSelectedTile = null;
                return true;
            }
        });

        Label info = new Label("Information : ", skin, "default-font", Color.WHITE);
        info.setFontScale(0.3f);
        table.setSize(Gdx.graphics.getWidth() / 3, Gdx.graphics.getHeight() / 3);
        table.setBackground(patch);

        table.add(info).expand().top().left();
        table.add(cross).expand().top().right();
        table.setPosition(Gdx.graphics.getWidth() - table.getWidth(), 0);
        stage.addActor(table);
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

        initaliseInputProcessors();
    }

    public void initaliseInputProcessors() {

        InputMultiplexer inputMultiplexer = new InputMultiplexer();

        Gdx.input.setInputProcessor(inputMultiplexer);

        MapGestureHandler gestureHandler = new MapGestureHandler(camera);
        MapInputProcessor inputProcessor = new MapInputProcessor(camera);

        inputMultiplexer.addProcessor(new GestureDetector(gestureHandler));
        inputMultiplexer.addProcessor(inputProcessor);
        inputMultiplexer.addProcessor(stage);
    }

    @Override
    public void render(float delta) {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        Gdx.gl.glClearColor(1, 1, 1, 1);

        try {
            network.update();
        } catch (IOException e) {
            System.err.println("You've been disconnected");
            game.setScreen(new MainMenuScreen(game));
            e.printStackTrace();
        }

        Map map = network.getMap();

        camera.update();
        batch.setProjectionMatrix(camera.combined);

        // draw ground
        batch.setTransformMatrix(groundMatrix);
        batch.disableBlending();

        batch.begin();
        for (int z = 0; z < sizeMap.y; z++) {
            for (int x = 0; x < sizeMap.x; x++) {
                groundSprite[x][z].draw(batch);
            }
        }

        batch.enableBlending();

        // draw ressource
        Square[][] square = map.getSquare();
        for (int i = 0; i < square.length; i++) {
            for (int j = 0; j < square[i].length; j++) {
                square[i][j].draw(batch, delta);
            }
        }

        List<Player> currentPlayer = map.getPlayers();

        boolean touched =  checkTileTouched(), selected = false, dead = true;
        for (Player p : currentPlayer) {
            Vector2 playerPos = p.get_pos();

            if (touched && intersection.x == playerPos.x && intersection.z == -playerPos.y && !selected) {
                p.setSelected(true);
                selected = true;
            } else if (touched) {
                p.setSelected(false);
            }
            if (p.isSelected()) {
                if(lastSelectedTile != null)
                    lastSelectedTile.setColor(1, 1, 1, 1);
                Sprite sprite = groundSprite[(int)playerPos.x][(int)playerPos.y];
                sprite.setColor(1, 0, 0, 1);
                System.out.println("pos : x " + playerPos.x + " -  y : " + playerPos.y);
                lastSelectedTile = sprite;
            }
            if (lastSelectedTile != null) {
                if (lastSelectedTile.getX() == playerPos.x && lastSelectedTile.getY() == playerPos.y) {
                    dead = false;
                }
            }
            p.act(delta);
            p.draw(batch, delta);
        }

        if (dead && lastSelectedTile != null) {
            lastSelectedTile.setColor(1, 1, 1, 1);
        }

        batch.end();

        batch.setTransformMatrix(new Matrix4());
        batch.setProjectionMatrix(new Matrix4().setToOrtho2D(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight()));

        batch.begin();
        font.draw(batch, "FPS : " + Gdx.graphics.getFramesPerSecond(), 0, Gdx.graphics.getHeight());
        batch.end();

        if (!dead && lastSelectedTile != null) {
            stage.act(delta);
            stage.draw();
            Table.drawDebug(stage);
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
        stage.dispose();
        skin.dispose();
    }
}
