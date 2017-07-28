<?php
/**
 * Created by PhpStorm.
 * User: itsli
 * Date: 26/07/2017
 * Time: 16:59
 */

require_once 'config.php';

require_once 'fetch_data.php';

if($_POST['houseId'])
{
    $selectedHouse = $_POST['houseId'];

    $sensorCount = FetchData::FetchHouseSensorCount($selectedHouse);

    $sensors = FetchData::FetchHouseSensors($selectedHouse);

    //$waterData = FetchData::FetchWaterDataAndroid($sensors);

    $waterArray = [];
    //$waterFiltered = [];
    //foreach($temperatureData as $item)
    //{
    //    $temperatureFiltered[$item['temperature_timestamp']][] = $item['temperature_value'];
    //}

    $waterData = $pdo->prepare("SELECT * FROM water LIMIT 43200");
    //$waterData->execute();
    if($waterData->execute()) {
        while ($row = $waterData->fetch()) {
            $waterArray[] = $row['water_value'];
        }
    }


    //foreach($waterData as $time => $values)
    //{
        //$valuesSum = array_sum($values);

        //$averageValue = round($valuesSum / $valuesCount);
    //}

    $valuesSum = array_sum($waterArray);

    $response["error"] = FALSE;
    $response["user"]["waterUsage"] = round($valuesSum, 2);



    echo json_encode($response);
}