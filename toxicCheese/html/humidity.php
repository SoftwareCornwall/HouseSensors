<?php
$host = "127.0.0.1";
$dbname = "sensor";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Get humidity POST variables 

$humidityValue = $_POST['humidity'];
$timestamp = $_POST['date'] . " " . $_POST['timestamp'];
$macaddress = $_POST['mac'];

// Get waterflow POST variables

// $waterValue = $_POST['waterflow'];

// Insert humidity POST values into database

$stmt = $pdo->prepare("INSERT INTO humidity (humidity, timestamp, macaddress) values (:humidity, :time, :mac)");
$stmt->bindParam(':humidity', $humidityValue, PDO::PARAM_INT);
$stmt->bindParam(':time', $timestamp, PDO::PARAM_STR);
$stmt->bindParam(':mac', $macaddress, PDO::PARAM_STR);
$result = $stmt->execute();
echo "OK :";
print_r ($_POST);

// Insert waterflow POST values into database

//$stmt = $pdo->prepare("INSERT INTO water (waterusage) values (:waterflow)");
//$stmt->bindParam(':waterflow', $waterValue, PDO::PARAM_INT);
//$result = $stmt->execute();

?>
