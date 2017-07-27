<?php
/**
 * Created by PhpStorm.
 * User: itsli
 * Date: 26/07/2017
 * Time: 16:59
 */

include 'config.php';

require_once 'fetch_data.php';

if($_POST['houseId'])
{
    $selectedHouse = $_POST['houseId'];

    $sensorCount = FetchData::FetchHouseSensorCount($selectedHouse);

    $sensors = FetchData::FetchHouseSensors($selectedHouse);

    $temperatureData = FetchData::FetchTemperatureDataAndroid($sensors);


    $temperatureFiltered = [];
    foreach($temperatureData as $item)
    {
        $temperatureFiltered[$item['temperature_timestamp']][] = $item['temperature_value'];
    }

    foreach($temperatureFiltered as $time => $values)
    {
        $valuesCount = count($values);
        $valuesSum = array_sum($values);


        $averageValue = round($valuesSum / $valuesCount);
    }



    $response["error"] = FALSE;
    $response["user"]["temperatureAverage"] = round($averageValue);



    echo json_encode($response);
}