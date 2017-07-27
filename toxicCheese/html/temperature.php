<?php
$host = "127.0.0.1";
$dbname = "sensor";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Get temperature POST variables 

$temperatureValue = $_POST['temperature'];
$timestamp = $_POST['date'] . " " . $_POST['timestamp'];
$macaddress = $_POST['mac'];

echo "POST temperature is " . $temperatureValue;

// Insert temperature POST values into database

$stmt = $pdo->prepare("INSERT INTO temperature (temperature, timestamp, macaddress) values (:temperature, :time, :mac)");
$stmt->bindParam(':temperature', $temperatureValue, PDO::PARAM_INT);
$stmt->bindParam(':time', $timestamp, PDO::PARAM_STR);
$stmt->bindParam(':mac', $macaddress, PDO::PARAM_STR);
$result = $stmt->execute();
echo "OK :";
print_r ($_POST);



?>
