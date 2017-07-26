<?php
$host = "127.0.0.1";
$dbname = "sensor";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Get water POST variables 

$waterValue = $_POST['waterflow'];
$timestamp = $_POST['date'] . " " . $_POST['timestamp'];
$macaddress = $_POST['mac'];


// Insert water POST values into database

$stmt = $pdo->prepare("INSERT INTO water (waterflow, timestamp, macaddress) values (:waterflow, :time, :mac)");
$stmt->bindParam(':waterflow', $waterValue, PDO::PARAM_INT);
$stmt->bindParam(':time', $timestamp, PDO::PARAM_STR);
$stmt->bindParam(':mac', $macaddress, PDO::PARAM_STR);
$result = $stmt->execute();
echo "OK :";

// We could check here to see if water consumption is high enough to send an SMS alert

?>
