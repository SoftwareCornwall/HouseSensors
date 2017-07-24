<?php

require_once 'DB_connect.php';

$water = $_POST["waterValue"];
$timestamp = $_POST['timestamp'];
$macAddress = $_POST['mac'];
$db = new DB_Connect();
$db->Connect();
$db->SaveWater($water, $timestamp, $macAddress);
