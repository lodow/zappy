package com.zappy.screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Image;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;
import com.badlogic.gdx.scenes.scene2d.utils.Drawable;
import com.badlogic.gdx.scenes.scene2d.utils.TextureRegionDrawable;
import com.zappy.assets.Assets;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by debas_e on 08/07/2014.
 */
public class PopUpInformation extends Stage {
    private boolean showing = false;
    private Label level, team;
    private HashMap<Square.eType, Label> labelInfo = new HashMap<Square.eType, Label>();

    public PopUpInformation (Skin skin) {

        TextureRegion ressource = Assets.ressource;
        HashMap<Square.eType, Image> img_ressource = new HashMap<Square.eType, Image>();

        img_ressource.put(Square.eType.Deraumere, new Image(new Sprite(ressource, 0, 24, 22, 43 - 24)));
        img_ressource.put(Square.eType.Linemate, new Image(new Sprite(ressource, 52, 0, 73 - 52, 18)));
        img_ressource.put(Square.eType.Mendiane, new Image(new Sprite(ressource, 26, 0, 47 - 26, 19)));
        img_ressource.put(Square.eType.Phiras, new Image(new Sprite(ressource, 102, 24, 124 - 102, 43 - 24)));
        img_ressource.put(Square.eType.Sibur, new Image(new Sprite(ressource, 52, 49, 73 - 52, 66 - 49)));
        img_ressource.put(Square.eType.Thystame, new Image(new Sprite(ressource, 78, 49, 98 - 78, 66 - 49)));
        img_ressource.put(Square.eType.Nourriture, new Image(new Sprite(Assets.food.get(0))));

        this.labelInfo.put(Square.eType.Deraumere, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Linemate, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Mendiane, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Phiras, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Sibur, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Thystame, new Label("", skin, "default-font", Color.WHITE));
        this.labelInfo.put(Square.eType.Nourriture, new Label("", skin, "default-font", Color.WHITE));

        Drawable patch = new TextureRegionDrawable(new TextureRegion(Assets.all, 175, 0, 50, 50));

        Image cross = new Image(new Texture(Gdx.files.internal("data/mainMenu/remove_cross.png")));
        cross.addListener(new CrossClick());
        Table table = new Table();
        this.addActor(table);

        level = new Label("", skin, "default-font", Color.WHITE);
        level.setFontScale(0.5f);
        team = new Label("", skin, "default-font", Color.WHITE);
        team.setFontScale(0.4f);

        table.setSize(Gdx.graphics.getWidth() / 3, Gdx.graphics.getHeight() / 2.8f);
        table.setBackground(patch);

        table.columnDefaults(4);
        table.add(level).top().left().expand().colspan(2).padLeft(5);
        table.add(cross).top().right().colspan(2);
        table.row();
        table.add(team).top().left().expand().colspan(4).padLeft(5);
        table.row();

        img_ressource.get(Square.eType.Thystame).scaleBy(2);
        img_ressource.get(Square.eType.Sibur).scaleBy(2);
        img_ressource.get(Square.eType.Phiras).scaleBy(2);
        img_ressource.get(Square.eType.Mendiane).scaleBy(2);
        img_ressource.get(Square.eType.Linemate).scaleBy(2);
        img_ressource.get(Square.eType.Deraumere).scaleBy(2);
        img_ressource.get(Square.eType.Nourriture).scaleBy(3);

        labelInfo.get(Square.eType.Thystame).setFontScale(0.3f);
        labelInfo.get(Square.eType.Sibur).setFontScale(0.3f);
        labelInfo.get(Square.eType.Phiras).setFontScale(0.3f);
        labelInfo.get(Square.eType.Mendiane).setFontScale(0.3f);
        labelInfo.get(Square.eType.Linemate).setFontScale(0.3f);
        labelInfo.get(Square.eType.Deraumere).setFontScale(0.3f);
        labelInfo.get(Square.eType.Nourriture).setFontScale(0.3f);

        table.add(img_ressource.get(Square.eType.Thystame)).left().bottom().expand().padLeft(5);
        table.add(labelInfo.get(Square.eType.Thystame)).left().top().expand();
        table.add(img_ressource.get(Square.eType.Sibur)).left().bottom().expand();
        table.add(labelInfo.get(Square.eType.Sibur)).left().top().expand();
        table.row();
        table.add(img_ressource.get(Square.eType.Phiras)).left().bottom().expand().padLeft(5);
        table.add(labelInfo.get(Square.eType.Phiras)).left().top().expand();
        table.add(img_ressource.get(Square.eType.Mendiane)).left().bottom().expand();
        table.add(labelInfo.get(Square.eType.Mendiane)).left().top().expand();
        table.row();
        table.add(img_ressource.get(Square.eType.Linemate)).left().bottom().expand().padLeft(5);
        table.add(labelInfo.get(Square.eType.Linemate)).left().top().expand();
        table.add(img_ressource.get(Square.eType.Deraumere)).left().bottom().expand();
        table.add(labelInfo.get(Square.eType.Deraumere)).left().top().expand();
        table.row();
        table.add(img_ressource.get(Square.eType.Nourriture)).left().bottom().expand().padLeft(5);
        table.add(labelInfo.get(Square.eType.Nourriture)).left().top().expand();
        table.setPosition(Gdx.graphics.getWidth() - table.getWidth(), 0);

        //table.debug();
    }

    public boolean isShowing() {
        return showing;
    }

    public void setShowing(boolean show) {
        showing = show;
    }

    public void update(Player player) {
        Map<Square.eType, Integer> content = player.getContent();

        for (Map.Entry<Square.eType, Label> entry : labelInfo.entrySet())
        {
            Integer number = content.get(entry.getKey());
            Label tmp = entry.getValue();
            tmp.setText(entry.getKey() + " : " + number.toString());
        }
        level.setText("level : " + player.get_level());
        team.setText("(team " + player.get_team() + ")");
    }

    private class CrossClick extends ClickListener {
        public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
            showing = false;
            return true;
        }
    }
}
