<?php
$host = "localhost";
$dbname = "sensor";
$user = "toxicCheese";
$password = "1234567890";

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

require_once "database.php"; // database usage class
require_once "water-spike-check.php";
require_once "sms.php";

$DB = new database(); // set up database object

function sendAlert($message) 
	{
		$response = sendSMS('2eaTYE', 'DvBGcA', '44', $message, 'ALERT');
		echo $response;
	}

try {
	$waterReadings = $DB->last_two_water_sensor_readings();
	print_r($waterReadings);
	waterSpikeCheck($waterReadings,'sendAlert'); 	

} catch (Exception $e) {
	echo "ERROR calculating total water usage";
}

?>
