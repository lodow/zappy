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

    public static Texture player_sheet, ground, incantation;

    private static TextureRegion[][] anim_tab;
    private static HashMap<Player.eDirection, Animation> player_animation = new HashMap<Player.eDirection, Animation>();
    private static HashMap<String, Animation> incantation_animation = new HashMap<String, Animation>();
    private static HashMap<Player.eDirection, Sprite> player_static = new HashMap<Player.eDirection, Sprite>();
    private static HashMap<Square.eType, Sprite> sprite_ressource = new HashMap<Square.eType, Sprite>();
    public static List<TextureRegion> food = new ArrayList<TextureRegion>();
    public static TextureRegion ressource;
    public static Texture all;
    private static int FRAME_COLS = 8;
    private static int FRAME_ROWS = 5;
    private static float speed = 0.06f;
    private static int index = 0;


    public static void Load() {
        player_sheet = new Texture(Gdx.files.internal("data/sprites/animation_sheet.png"));
        ground = new Texture(Gdx.files.internal("data/sprites/ground.jpg"));

        anim_tab = TextureRegion.split(player_sheet, player_sheet.getWidth() / FRAME_COLS, player_sheet.getHeight() / FRAME_ROWS);
        player_animation.put(Player.eDirection.Nord, new Animation(speed, anim_tab[1]));
        player_animation.put(Player.eDirection.Ouest, new Animation(speed, anim_tab[2]));
        player_animation.put(Player.eDirection.Est, new Animation(speed, anim_tab[3]));
        player_animation.put(Player.eDirection.Sud, new Animation(speed, anim_tab[4]));

        player_static.put(Player.eDirection.Nord, new Sprite(anim_tab[0][0]));
        player_static.put(Player.eDirection.Ouest, new Sprite(anim_tab[0][1]));
        player_static.put(Player.eDirection.Est, new Sprite(anim_tab[0][2]));
        player_static.put(Player.eDirection.Sud, new Sprite(anim_tab[0][3]));

        all = new Texture(Gdx.files.internal("data/sprites/all_sprite.png"));
        ressource = new TextureRegion(all, 0, 0, 150, 68);

        // create incantations
        TextureRegion incantation;
        incantation = new TextureRegion(all, 0, 432, 393, 824 - 432);
        anim_tab = incantation.split(incantation.getRegionWidth() / 5, incantation.getRegionHeight() / 5);
        TextureRegion[] incantation1 = new TextureRegion[5 * 5];
        index = 0;
        for (int i = 0; i < anim_tab.length; i++) {
            for (int j = 0; j < anim_tab[i].length; j++) {
                incantation1[index++] = anim_tab[i][j];
            }
        }
        incantation_animation.put("fire", new Animation(0.15f, incantation1));

        incantation = new TextureRegion(all, 393, 431, 800 - 393, 900 - 431);
        anim_tab = incantation.split(incantation.getRegionWidth() / 5, incantation.getRegionHeight() / 6);
        TextureRegion[] incantation2 = new TextureRegion[5 * 6];
        index = 0;
        for (int i = 0; i < anim_tab.length; i++) {
            for (int j = 0; j < anim_tab[i].length; j++) {
                incantation2[index++] = anim_tab[i][j];
            }
        }
        incantation_animation.put("tornado", new Animation(0.15f, incantation2));


        TextureRegion foodRegion = new TextureRegion(all, 2, 72, 101 - 2, 101 - 72);
        TextureRegion foodTmp[][] = foodRegion.split(foodRegion.getRegionWidth() / 7, foodRegion.getRegionHeight() / 2);
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

    public static HashMap<String, Animation> getIncantationAnimation() {
        return (HashMap<String, Animation>) incantation_animation.clone();
    }
}
