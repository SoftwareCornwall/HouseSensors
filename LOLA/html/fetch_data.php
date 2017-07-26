<?php
/**
 * Created by PhpStorm.
 * User: liam
 * Date: 24/07/17
 * Time: 12:01
 */

require_once "config.php";

//$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

class FetchData
{

    static function FetchHouseSensorCount($selectedHouse)
    {
        global $pdo;
        $houseSensors = $pdo->prepare("SELECT DISTINCT mac_address FROM sensor_location WHERE house_id=:house");
        $houseSensors->bindValue(':house', $selectedHouse);
        $houseSensors->execute();

        $sensorCount = $houseSensors->rowCount();


        return $sensorCount;
    }

    static function FetchHouseSensors($selectedHouse)
    {
        global $pdo;
        $houseSensors = $pdo->prepare("SELECT DISTINCT mac_address FROM sensor_location WHERE house_id=:house");
        $houseSensors->bindValue(':house', $selectedHouse);
        $houseSensors->execute();

        $sensors = $houseSensors->fetchAll(PDO::FETCH_COLUMN, 0);


        return $sensors;
    }

    static function FetchHumidityData($sensorMacAddresses)
    {
        global $pdo;


        $humidityData = $pdo->prepare("SELECT * FROM humidity WHERE mac_address IN ('" . implode("','",$sensorMacAddresses) . "') ORDER BY id DESC LIMIT 288");
        $humidityData->bindValue('s', $sensorMacAddresses);
        $humidityData->execute();

        $humidityDataArray = $humidityData->fetchAll(PDO::FETCH_ASSOC);

        return $humidityDataArray;
    }

    static function FetchTemperatureData($sensorMacAddresses)
    {
        global $pdo;


        $temperatureData = $pdo->prepare("SELECT * FROM temperature WHERE mac_address IN ('" . implode("','",$sensorMacAddresses) . "') ORDER BY id DESC LIMIT 288");
        $temperatureData->bindValue('s', $sensorMacAddresses);
        $temperatureData->execute();

        $temperatureDataArray = $temperatureData->fetchAll(PDO::FETCH_ASSOC);

        return $temperatureDataArray;
    }

    static function FetchWaterData($sensorMacAddresses)
    {
        global $pdo;


        $waterData = $pdo->prepare("SELECT * FROM water WHERE mac_address IN ('" . implode("','",$sensorMacAddresses) . "') ORDER BY id DESC LIMIT 288");
        $waterData->bindValue('s', $sensorMacAddresses);
        $waterData->execute();

        $waterDataArray = $waterData->fetchAll(PDO::FETCH_ASSOC);

        return $waterDataArray;
    }
}
