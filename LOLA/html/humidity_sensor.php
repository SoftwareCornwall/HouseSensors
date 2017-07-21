<?php

require_once 'DB_connect.php';

$humidity = $_POST["humidityValue"];
$timestamp = $_POST['timestamp'];
$db = new DB_Connect();
$db->Connect();
$db->Update($humidity, $timestamp);