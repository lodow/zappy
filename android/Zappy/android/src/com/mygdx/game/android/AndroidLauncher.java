package com.mygdx.game.android;

import android.os.Bundle;
import android.os.StrictMode;

import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.backends.android.AndroidApplicationConfiguration;
import com.zappy.Zappy;

public class AndroidLauncher extends AndroidApplication {
	@Override
	protected void onCreate (Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        /*try {
            new Network("37.187.16.16", 4242);
        } catch (IOException e) {
            e.printStackTrace();
        }*/
        AndroidApplicationConfiguration config = new AndroidApplicationConfiguration();
		initialize(new Zappy(), config);
	}
}
