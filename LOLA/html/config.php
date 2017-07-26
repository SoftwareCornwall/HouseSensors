<?php
define("DB_HOST", "127.0.0.1");
define("DB_USER", "root");
define("DB_PASSWORD", "");
define("DB_DATABASE", "sensor_data");

$host = "127.0.0.1";
$dbname = "sensor_data";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);
?>