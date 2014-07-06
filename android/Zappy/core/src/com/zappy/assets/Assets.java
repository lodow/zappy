package com.zappy.assets;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Animation;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.TextureRegion;
import com.zappy.map.entities.Player;
import com.zappy.map.entities.Square;

import java.util.HashMap;

/**
 * Created by debas_e on 27/06/2014.
 */
public class Assets {

    public static Texture player_sheet, ground;

    private static TextureRegion[][] anim_tab;
    private static HashMap<Player.eDirection, Animation> player_animation = new HashMap<Player.eDirection, Animation>();
    private static HashMap<Player.eDirection, Sprite> player_static = new HashMap<Player.eDirection, Sprite>();
    private static HashMap<Square.eType, Sprite> sprite_ressource = new HashMap<Square.eType, Sprite>();
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

        Texture ressource = new Texture(Gdx.files.internal("data/zappy_ressource.png"));
        sprite_ressource.put(Square.eType.Deraumere, (new Sprite(ressource, 8, 488, 52 - 8, 520 - 488)));
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
