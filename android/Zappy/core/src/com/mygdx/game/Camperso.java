package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.g3d.utils.CameraInputController;
import com.badlogic.gdx.math.Vector3;

public class Camperso extends CameraInputController {
    private float startX, startY;
    private final Vector3 tmpV1 = new Vector3();

    Camperso(final Camera camera) {
        super(camera);
    }

    public boolean touchDragged (int screenX, int screenY, int pointer) {
        if (this.button < 0)
            return super.touchDragged(screenX, screenY, pointer);

        final float deltaX = (screenX - startX) / Gdx.graphics.getWidth();
        final float deltaY = (startY - screenY) / Gdx.graphics.getHeight();
        startX = screenX;
        startY = screenY;

        tmpV1.set(camera.direction).crs(camera.up).y = 0f;
        camera.translate(tmpV1.set(camera.direction).crs(camera.up).nor().scl(-deltaX * translateUnits));

        tmpV1.set(camera.direction).y = 0f;
        camera.translate(tmpV1.scl(-deltaY * translateUnits));

        camera.update();
        return true;
    }

    public boolean touchDown (int screenX, int screenY, int pointer, int button) {
        startX = screenX;
        startY = screenY;
        this.button = button;
        return super.touchDown(screenX, screenY, pointer, button);
    }
}
