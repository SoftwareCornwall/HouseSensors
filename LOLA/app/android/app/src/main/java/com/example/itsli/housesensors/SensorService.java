package com.example.itsli.housesensors;




import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Color;
import android.os.Build;
import android.os.IBinder;
import android.support.annotation.Nullable;

import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationManagerCompat;
import android.support.v4.app.TaskStackBuilder;
import android.util.Log;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by fabio on 30/01/2016.
 */
public class SensorService extends Service {
    public int counter=0;
    Notification.Builder notificationBuilder;

    SQLiteDatabase sqLiteDatabase;
    Cursor cursor;
    SessionManager session;
    SQLiteHandler databaseHandler;
    String house;


    public SensorService(Context applicationContext) {
        super();
        Log.i("HERE", "here I am!");
    }

    public SensorService() {
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        startTimer();

        databaseHandler = new SQLiteHandler(getApplication());
        sqLiteDatabase = databaseHandler.getReadableDatabase();
        cursor = databaseHandler.getLoggedInUser(sqLiteDatabase);
        if (cursor.moveToFirst()) {
            do {

                house = cursor.getString(5);
            } while (cursor.moveToNext());
        }

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {



        } else {
            notificationBuilder = new Notification.Builder(getApplicationContext());
            notificationBuilder = new Notification.Builder(getApplicationContext())
                    .setSmallIcon(R.drawable.ic_drop_silhouette)
                    .setContentTitle("Alert!")
                    .setContentText("You've used over 1000 liters of water over the past month!");
        }



        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i("EXIT", "ondestroy!");
        //Intent broadcastIntent = new Intent("uk.ac.shef.oak.ActivityRecognition.RestartSensor");
        //sendBroadcast(broadcastIntent);
        stoptimertask();
    }

    private Timer timer;
    private TimerTask timerTask;
    long oldTime=0;
    public void startTimer() {
        //set a new Timer
        timer = new Timer();

        //initialize the TimerTask's job
        initializeTimerTask();

        //schedule the timer, to wake up every 1 second
        timer.schedule(timerTask, 1000, 60000); //
    }

    /**
     * it sets the timer to print the counter every x seconds
     */
    public void initializeTimerTask() {
        timerTask = new TimerTask() {
            public void run() {

                // send to server here, get response and if it is bad then notification!
                getWaterUsage(house);
                //startNotification();
                Log.i("in timer", "in timer ++++  "+ (counter++));
            }
        };
    }

    /**
     * not needed
     */
    public void stoptimertask() {
        //stop the timer, if it's not already null
        if (timer != null) {
            timer.cancel();
            timer = null;
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public void startNotification()
    {
    Log.e("notif", "test");

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {

            NotificationManager mNotificationManager =
                    (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

// The id of the channel.
            String id = "my_channel_01";
// The user-visible name of the channel.
            CharSequence name = getString(R.string.channel_name);
// The user-visible description of the channel.
            String description = getString(R.string.channel_description);
            int importance = NotificationManager.IMPORTANCE_LOW;
            NotificationChannel mChannel = new NotificationChannel(id, name, importance);
// Configure the notification channel.
            mChannel.setDescription(description);
            mChannel.enableLights(true);
// Sets the notification light color for notifications posted to this
// channel, if the device supports this feature.
            mChannel.setLightColor(Color.RED);
            mChannel.enableVibration(true);
            mChannel.setVibrationPattern(new long[]{100, 200, 300, 400, 500, 400, 300, 200, 400});
            mNotificationManager.createNotificationChannel(mChannel);


            mNotificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
// Sets an ID for the notification, so it can be updated.
            int notifyID = 1;
// The id of the channel.
            String CHANNEL_ID = "my_channel_01";
// Create a notification and set the notification channel.
            Notification notification = new Notification.Builder(getApplicationContext())
                    .setContentTitle("Alert!")
                    .setContentText("You've used over 1000 liters of water over the past month!")
                    .setSmallIcon(R.drawable.ic_drop_silhouette)
                    .setChannelId(CHANNEL_ID)
                    .build();
// Issue the notification.
            mNotificationManager.notify(1, notification);
        } else {
            NotificationManager mNotificationManager =
                    (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);


            mNotificationManager.notify(1, notificationBuilder.build());
        }




    }



    private void getWaterUsage(final String house) {
        // Tag used to cancel the request
        String tag_string_req = "req_product";

        Log.e("GETTING USER INFO", "getting user information....");


        StringRequest strReq = new StringRequest(Request.Method.POST,
                AppConfig.URL_WATER_USAGE, new Response.Listener<String>() {

            @Override
            public void onResponse(String response) {
                Log.d("HELLO", "Register Response: " + response);

                try {
                    JSONObject jObj = new JSONObject(response);
                    boolean error = jObj.getBoolean("error");
                    if (!error) {
                        // User successfully stored in MySQL
                        // Now store the user in sqlite


                        JSONObject productJSON = jObj.getJSONObject("user");
                        int waterUsageReceived = productJSON.getInt("waterUsage");

                        if(waterUsageReceived > 1000)
                        {
                            startNotification();
                        }



                        Log.e("FRIEND REQUESTS", "variables are: " +house + " " + waterUsageReceived);
                        // String name = nameDecrypted;

                    } else {

                        // Error occurred in registration. Get the error
                        // message
                        String errorMsg = jObj.getString("error_msg");
                        Toast.makeText(getApplication().getApplicationContext(),
                                errorMsg, Toast.LENGTH_LONG).show();
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                    Toast.makeText(getApplication().getApplicationContext(), "Json error: " + e.getMessage(), Toast.LENGTH_LONG).show();
                }

            }
        }, new Response.ErrorListener() {

            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("HELLO", "Registration Error: " + error.getMessage());
                Toast.makeText(getApplication().getApplicationContext(),
                        error.getMessage(), Toast.LENGTH_LONG).show();
            }
        }) {

            @Override
            protected Map<String, String> getParams() {
                // Posting params to register url
                Log.e("GETTING USER INFO", "sending user information...." + house);
                Map<String, String> params = new HashMap<String, String>();

                params.put("houseId", house);


                return params;
            }

        };
        // Adding request to request queue
        AppController.getInstance().addToRequestQueue(strReq, tag_string_req);
    }
}