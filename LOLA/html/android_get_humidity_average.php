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

    $humidityData = FetchData::FetchHumidityDataAndroid($sensors);


    $humidityFiltered = [];
    foreach($humidityData as $item)
    {
        $humidityFiltered[$item['humidity_timestamp']][] = $item['humidity_value'];
    }

    foreach($humidityFiltered as $time => $values)
    {
        $valuesCount = count($values);
        $valuesSum = array_sum($values);


        $averageValue = round($valuesSum / $valuesCount);
    }



    $response["error"] = FALSE;
    $response["user"]["humidityAverage"] = round($averageValue);



    echo json_encode($response);
}