package com.zappy.screen;

import com.badlogic.gdx.scenes.scene2d.ui.Dialog;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.Align;

/**
 * Created by debas_e on 04/07/2014.
 */

public class ErrorPopUp extends Dialog {
    public ErrorPopUp(String title, String text, TextButton button, Skin skin) {
        super(title, skin);

        Label label = new Label(text, skin);
        label.setWrap(true);
        label.setFontScale(.8f);
        label.setAlignment(Align.center);

        this.padTop(50).padBottom(50);
        this.getContentTable().add(label).width(850).row();
        this.getButtonTable().padTop(50);

//        TextButton retry = new TextButton("Retry", skin);
        this.button(button);

        this.invalidateHierarchy();
        this.invalidate();
        this.layout();
    }
}
