<?php
$host = "localhost";
$dbname = "sensor";
$user = "toxicCheese";
$password = "1234567890";


$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Get humidity POST variables 

$humidityValue = $_POST['humidity'];
$timestamp = $_POST['date'] . " " . $_POST['timestamp'];
$macaddress = $_POST['mac'];

// Get waterflow POST variables

// $waterValue = $_POST['waterflow'];

// Insert humidity POST values into database

$stmt = $pdo->prepare("INSERT INTO humidity (humidity, date, timestamp, macaddress) values (:humidity, :date, :time, :mac)");
$stmt->bindParam(':humidity', $humidityValue, PDO::PARAM_INT);
$stmt->bindParam(':date', $_POST['date'], PDO::PARAM_STR);
$stmt->bindParam(':time', $timestamp, PDO::PARAM_STR);
$stmt->bindParam(':mac', $macaddress, PDO::PARAM_STR);
$result = $stmt->execute();
echo "OK :";
print_r ($result);

// Insert waterflow POST values into database

//$stmt = $pdo->prepare("INSERT INTO water (waterusage) values (:waterflow)");
//$stmt->bindParam(':waterflow', $waterValue, PDO::PARAM_INT);
//$result = $stmt->execute();

?>
