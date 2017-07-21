<?php

require_once 'DB_connect.php';

$humidity = $_POST["humidityValue"];
$timestamp = $_POST['timestamp'];
$macAddress = $_POST['mac'];
$temperature = $_POST['temperatureValue'];
$db = new DB_Connect();
$db->Connect();
$db->SaveHumidity($humidity, $timestamp, $macAddress);
$db->SaveTemperature($temperature, $timestamp, $macAddress);