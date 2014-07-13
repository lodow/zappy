package com.zappy.screen;

import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.ui.Dialog;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.Align;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;

/**
 * Created by debas_e on 08/07/2014.
 */
public class ReturnDialog extends Dialog {
    private boolean isShowing = false;
    private boolean result;
    private TextButton ok;
    private TextButton no;
    private Skin skin;

    public ReturnDialog(String title, Skin skin) {
        super(title, skin);

        this.skin = skin;

        Label label = new Label("Do you want to exit ?", skin);
        label.setWrap(true);
        label.setFontScale(.8f);
        label.setAlignment(Align.center);


        this.padTop(50).padBottom(50);
        this.getContentTable().add(label).width(850).row();
        this.getButtonTable().padTop(50);

        ok = new TextButton("Yes", skin);
        no = new TextButton("No", skin);

        ok.addListener(new ClickListener() {
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                isShowing = false;
                result = true;
                return super.touchDown(event, x, y, pointer, button);
            }
        });

        no.addListener(new ClickListener() {
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                isShowing = false;
                result = false;
                return super.touchDown(event, x, y, pointer, button);
            }
        });

        this.getButtonTable().setWidth(850);
        this.getButtonTable().add(ok).padRight(50);
        this.getButtonTable().add(no).padLeft(50);

        this.invalidateHierarchy();
        this.invalidate();
        this.layout();
    }

    public void setShowing(boolean bool) {
        isShowing = bool;
    }

    public boolean isShowing() {
        return isShowing;
    }

    public boolean getResult() {
        return result;
    }

    public void resetButton() {
//        ok.setStyle(skin.get("default", TextButton.TextButtonStyle.class));
//        no.setStyle(skin.get("default", TextButton.TextButtonStyle.class));

        this.getButtonTable().reset();

        ok = new TextButton("Yes", skin);
        no = new TextButton("No", skin);

        ok.addListener(new ClickListener() {
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                isShowing = false;
                result = true;
                return super.touchDown(event, x, y, pointer, button);
            }
        });

        no.addListener(new ClickListener() {
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                isShowing = false;
                result = false;
                return super.touchDown(event, x, y, pointer, button);
            }
        });

        this.getButtonTable().setWidth(850);
        this.getButtonTable().add(ok).padRight(50);
        this.getButtonTable().add(no).padLeft(50);
    }
}
