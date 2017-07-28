package com.example.itsli.housesensors;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CalendarView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;

import org.json.JSONException;
import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by itsli on 26/07/2017.
 */

public class DashboardFragment extends Fragment
    {
        TextView humidityAverage, temperatureAverage, waterUsage;
        SQLiteDatabase sqLiteDatabase;
        Cursor cursor;
        SessionManager session;
        SQLiteHandler databaseHandler;
        String house;
        ProgressBar humidityProgressBar, temperatureProgressBar, waterProgressBar;

        public static DashboardFragment newInstance() {
        DashboardFragment fragment = new DashboardFragment();
        return fragment;
    }

        @Override
        public void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
        }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_dashboard, container, false);
        // Set title bar

        humidityProgressBar = view.findViewById(R.id.humidity_progress_bar);
        temperatureProgressBar = view.findViewById(R.id.temperature_progress_bar);
        waterProgressBar = view.findViewById(R.id.water_progress_bar);

        databaseHandler = new SQLiteHandler(getActivity());
        sqLiteDatabase = databaseHandler.getReadableDatabase();
        cursor = databaseHandler.getLoggedInUser(sqLiteDatabase);
        if (cursor.moveToFirst()) {
            do {
                house = cursor.getString(5);
            } while (cursor.moveToNext());
        }


        humidityAverage = view.findViewById(R.id.humidity_average);
        temperatureAverage = view.findViewById(R.id.temperature_average);
        waterUsage = view.findViewById(R.id.water_usage);

        getHumidityAverage(house);
        getTemperatureAverage(house);
        getWaterUsage(house);



        return view;

    }



        private void getHumidityAverage(final String house) {
            // Tag used to cancel the request
            String tag_string_req = "req_product";

            Log.e("GETTING USER INFO", "getting user information....");


            StringRequest strReq = new StringRequest(Request.Method.POST,
                    AppConfig.URL_HUMIDITY_AVERAGE, new Response.Listener<String>() {

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
                            String humidityAverageRecieved = productJSON.getString("humidityAverage");

                            humidityAverage.setText(humidityAverageRecieved + "%");
                            humidityProgressBar.setProgress(Integer.valueOf(humidityAverageRecieved));


                            Log.e("FRIEND REQUESTS", "variables are: " +house + " " + humidityAverageRecieved);
                            // String name = nameDecrypted;

                        } else {

                            // Error occurred in registration. Get the error
                            // message
                            String errorMsg = jObj.getString("error_msg");
                            //Toast.makeText(getActivity().getApplicationContext(),
                                    //errorMsg, Toast.LENGTH_LONG).show();
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                        //Toast.makeText(getActivity().getApplicationContext(), "Json error: " + e.getMessage(), Toast.LENGTH_LONG).show();
                    }

                }
            }, new Response.ErrorListener() {

                @Override
                public void onErrorResponse(VolleyError error) {
                    Log.e("HELLO", "Registration Error: " + error.getMessage());
                    //Toast.makeText(getActivity().getApplicationContext(),
                           // error.getMessage(), Toast.LENGTH_LONG).show();
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

        private void getTemperatureAverage(final String house) {
            // Tag used to cancel the request
            String tag_string_req = "req_product";

            Log.e("GETTING USER INFO", "getting user information....");


            StringRequest strReq = new StringRequest(Request.Method.POST,
                    AppConfig.URL_TEMPERATURE_AVERAGE, new Response.Listener<String>() {

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
                            String temperatureAverageReceived = productJSON.getString("temperatureAverage");

                            temperatureAverage.setText(temperatureAverageReceived + " \u2103");
                            temperatureProgressBar.setProgress(Integer.valueOf(temperatureAverageReceived));


                            Log.e("FRIEND REQUESTS", "variables are: " +house + " " + temperatureAverageReceived);
                            // String name = nameDecrypted;

                        } else {

                            // Error occurred in registration. Get the error
                            // message
                            String errorMsg = jObj.getString("error_msg");
                            Toast.makeText(getActivity().getApplicationContext(),
                                    errorMsg, Toast.LENGTH_LONG).show();
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                        //Toast.makeText(getActivity().getApplicationContext(), "Json error: " + e.getMessage(), Toast.LENGTH_LONG).show();
                    }

                }
            }, new Response.ErrorListener() {

                @Override
                public void onErrorResponse(VolleyError error) {
                    Log.e("HELLO", "Registration Error: " + error.getMessage());
                    //Toast.makeText(getActivity().getApplicationContext(),
                            //error.getMessage(), Toast.LENGTH_LONG).show();
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
                            Double waterUsageReceived = productJSON.getDouble("waterUsage");

                            waterUsage.setText(waterUsageReceived + " L/mo");
                            waterProgressBar.setProgress(waterUsageReceived.intValue());


                            Log.e("FRIEND REQUESTS", "variables are: " +house + " " + waterUsageReceived);
                            // String name = nameDecrypted;

                        } else {

                            // Error occurred in registration. Get the error
                            // message
                            String errorMsg = jObj.getString("error_msg");
                            //Toast.makeText(getActivity().getApplicationContext(),
                                    //errorMsg, Toast.LENGTH_LONG).show();
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                        //Toast.makeText(getActivity().getApplicationContext(), "Json error: " + e.getMessage(), Toast.LENGTH_LONG).show();
                    }

                }
            }, new Response.ErrorListener() {

                @Override
                public void onErrorResponse(VolleyError error) {
                    Log.e("HELLO", "Registration Error: " + error.getMessage());
                    //Toast.makeText(getActivity().getApplicationContext(),
                           // error.getMessage(), Toast.LENGTH_LONG).show();
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