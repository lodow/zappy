package com.zappy.popup;

import com.badlogic.gdx.scenes.scene2d.InputEvent;
import com.badlogic.gdx.scenes.scene2d.ui.Dialog;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.Align;
import com.badlogic.gdx.scenes.scene2d.utils.ClickListener;

/**
 * Created by debas_e on 13/07/2014.
 */
public class winDialog extends Dialog {
    private Label win;
    private TextButton exit;
    private boolean isShowing;

    public winDialog(String title, Skin skin) {
        super(title, skin);

        win = new Label("", skin);
        win.setWrap(true);
        win.setFontScale(.8f);
        win.setAlignment(Align.center);

        this.padTop(50).padBottom(50);
        this.getContentTable().add(win).width(850).row();
        this.getButtonTable().padTop(50);

        exit = new TextButton("Exit", skin);
        exit.addListener(new ClickListener() {
            @Override
            public boolean touchDown(InputEvent event, float x, float y, int pointer, int button) {
                isShowing = false;
                return super.touchDown(event, x, y, pointer, button);
            }
        });

        this.button(exit);

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

    public void setLabelText(String text) { win.setText(text); }

}
