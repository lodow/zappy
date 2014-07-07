package com.zappy.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Created by debas_e on 27/06/2014.
 */
public class Assets {

    public static Texture player_sheet, ground;

    private static TextureRegion[][] anim_tab;
    private static HashMap<Player.eDirection, Animation> player_animation = new HashMap<Player.eDirection, Animation>();
    private static HashMap<Player.eDirection, Sprite> player_static = new HashMap<Player.eDirection, Sprite>();
    private static HashMap<Square.eType, Sprite> sprite_ressource = new HashMap<Square.eType, Sprite>();
    public static List<TextureRegion> food = new ArrayList<TextureRegion>();
    private static int FRAME_COLS = 8;
    private static int FRAME_ROWS = 5;
    private static float speed = 0.15f;

    public static void Load() {
        player_sheet = new Texture(Gdx.files.internal("data/animation_sheet.png"));
        ground = new Texture(Gdx.files.internal("data/ground.jpg"));

        anim_tab = TextureRegion.split(player_sheet, player_sheet.getWidth() / FRAME_COLS, player_sheet.getHeight() / FRAME_ROWS);
        player_animation.put(Player.eDirection.Nord, new Animation(speed, anim_tab[1]));
        player_animation.put(Player.eDirection.Ouest, new Animation(speed, anim_tab[2]));
        player_animation.put(Player.eDirection.Est, new Animation(speed, anim_tab[3]));
        player_animation.put(Player.eDirection.Sud, new Animation(speed, anim_tab[4]));

        player_static.put(Player.eDirection.Nord, new Sprite(anim_tab[0][0]));
        player_static.put(Player.eDirection.Ouest, new Sprite(anim_tab[0][1]));
        player_static.put(Player.eDirection.Est, new Sprite(anim_tab[0][2]));
        player_static.put(Player.eDirection.Sud, new Sprite(anim_tab[0][3]));

        Texture ressource = new Texture(Gdx.files.internal("data/ressource_zappy.png"));
        sprite_ressource.put(Square.eType.Deraumere, (new Sprite(ressource, 0, 24, 22, 43 - 24)));
        sprite_ressource.put(Square.eType.Linemate, (new Sprite(ressource, 52, 0, 73 - 52, 18)));
        sprite_ressource.put(Square.eType.Mendiane, (new Sprite(ressource, 26, 0, 47 - 26, 19)));
        sprite_ressource.put(Square.eType.Phiras, (new Sprite(ressource, 102, 24, 124 - 102, 43 - 24)));
        sprite_ressource.put(Square.eType.Sibur, (new Sprite(ressource, 52, 49, 73 - 52, 66 - 49)));
        sprite_ressource.put(Square.eType.Thystame, (new Sprite(ressource, 78, 49, 98 - 78, 66 - 49)));

        ressource = new Texture(Gdx.files.internal("data/food_zappy.png"));
        TextureRegion foodTmp[][] = TextureRegion.split(ressource, ressource.getWidth() / 7, ressource.getHeight() / 2);
        for (int i = 0; i < foodTmp.length; i++) {
            for (int j = 0; j < foodTmp[i].length; j++) {
                food.add(foodTmp[i][j]);
            }
        }
    }

    public static HashMap<Player.eDirection, Animation> getAnimationPlayer() {
        return (HashMap<Player.eDirection, Animation>) player_animation.clone();
    }

    public static HashMap<Player.eDirection, Sprite> getStaticPlayer() {
        return (HashMap<Player.eDirection, Sprite>) player_static.clone();
    }

    public static HashMap<Square.eType, Sprite> getSpriteRessource() {
        return (HashMap<Square.eType, Sprite>) sprite_ressource.clone();
    }
}
