<?php
define("DB_HOST", "localhost");
define("DB_USER", "arron");
define("DB_PASSWORD", "helloworld");
define("DB_DATABASE", "sensor_data");

$host = "localhost";
$dbname = "sensor_data";
$user = "arron";
$password = "helloworld";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);
?>
