package com.zappy.InputCam;

import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.input.GestureDetector;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;

/**
 * Created by debas_e on 04/07/2014.
 */
public class MapGestureHandler implements GestureDetector.GestureListener {

    private float initialScale = 1.0f;
    private OrthographicCamera cam;

    public MapGestureHandler(OrthographicCamera cam) {
        this.cam = cam;
    }

    @Override
    public boolean touchDown(float x, float y, int pointer, int button) {
        initialScale = cam.zoom;
        return false;
    }

    @Override
    public boolean tap(float x, float y, int count, int button) {
        return false;
    }

    @Override
    public boolean longPress(float x, float y) {
        return false;
    }

    @Override
    public boolean fling(float velocityX, float velocityY, int button) {
        return false;
    }

    @Override
    public boolean pan(float x, float y, float deltaX, float deltaY) {
        return false;
    }

    @Override
    public boolean panStop(float x, float y, int pointer, int button) {
        return false;
    }

    @Override
    public boolean zoom(float initialDistance, float distance) {
        float ratio = initialDistance / distance;
        cam.zoom = MathUtils.clamp(initialScale * ratio, 0.1f, 1.0f);
        return true;
    }

    @Override
    public boolean pinch(Vector2 initialPointer1, Vector2 initialPointer2, Vector2 pointer1, Vector2 pointer2) {
        return false;
    }
}