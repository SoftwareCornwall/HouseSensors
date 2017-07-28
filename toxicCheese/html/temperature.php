<?php
$host = "localhost";
$dbname = "sensor";
$user = "toxicCheese";
$password = "1234567890";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Get temperature POST variables 

$temperatureValue = $_POST['temperature'];
$timestamp = $_POST['date'] . " " . $_POST['timestamp'];
$macaddress = $_POST['mac'];



// Insert temperature POST values into database

$stmt = $pdo->prepare("INSERT INTO temperature (temperature, timestamp, macaddress) values (:temperature, :time, :mac)");
$stmt->bindParam(':temperature', $temperatureValue, PDO::PARAM_INT);
$stmt->bindParam(':time', $timestamp, PDO::PARAM_STR);
$stmt->bindParam(':mac', $macaddress, PDO::PARAM_STR);
$result = $stmt->execute();
echo "OK :";
print_r ($result);



?>
