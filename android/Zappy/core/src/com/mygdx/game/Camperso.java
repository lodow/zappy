package com.mygdx.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Camera;
import com.badlogic.gdx.graphics.g3d.utils.CameraInputController;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector3;


/**
 * See: http://blog.xoppa.com/loading-models-using-libgdx/
 * @author Xoppa
 */

public class Camperso extends CameraInputController {
    private float startX, startY;
    private final Vector3 tmpV1 = new Vector3();

    Camperso(final Camera camera) {
        super(camera);
        Gdx.app.debug("Camperso", "construct");
    }

    public boolean touchDragged (int screenX, int screenY, int pointer) {
        Gdx.app.debug("Camperso", "screenX" + screenX + "screenY" + screenY + "touch " + this.button);
        boolean result = false;// super.touchDragged(screenX, screenY, pointer);
        Gdx.app.debug("Camperso", "result" + result);
        if (result || this.button < 0) return super.touchDragged(screenX, screenY, pointer);;

        final float deltaX = (screenX - startX) / Gdx.graphics.getWidth();
        final float deltaY = (startY - screenY) / Gdx.graphics.getHeight();
        startX = screenX;
        startY = screenY;
        Gdx.app.debug("Camperso", "deltaX" + deltaX + "daltaY" + deltaY);
        tmpV1.set(camera.direction).crs(camera.up).y = 0f;
        camera.translate(tmpV1.set(camera.direction).crs(camera.up).nor().scl(-deltaX * translateUnits));
        camera.translate(tmpV1.set(camera.position).scl(((-deltaY * translateUnits)/100)*-1));
        camera.translate(tmpV1.set(camera.up).scl(-deltaY * translateUnits));
        //camera.translate(tmpV2.set(camera.up).scl(-deltaY * translateUnits));
        camera.update();
        return true;
        //return process(deltaX, deltaY, 1);
        //return super.touchDragged(screenX, screenY, pointer);
    }

    public boolean touchDown (int screenX, int screenY, int pointer, int button) {
        startX = screenX;
        startY = screenY;
        this.button = button;
        return super.touchDown(screenX, screenY, pointer, button);
    }
}
