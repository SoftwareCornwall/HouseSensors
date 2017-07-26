<html>
<head><title>Demo</title></head>
<body>
<?php
require_once "database.php";

$host = "127.0.0.1";
$dbname = "sensor";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Read latest humidity reading from database and print on screen
// Currently disabled for purpose of demo on Tuesday

$DB = new database();
$row = $DB->latest_humidity();

$humidityValue = $row['humidity'];
echo "<p>Last recorded humidity value on " . $row['date'] . $row['timestamp'] . " is " . $row['humidity'] . "% </p>";

// Calculate average humidity reading from all data for last hour in humidity table and print on screen

try {
	$humidity = $DB->average_humidity_last_hour();
	echo "<h3>Average humidity for last 60 minutes</h3>";
	echo "<p>Both sensors combined  : ";
	echo $humidity;
	echo "% </p>";
} catch (Exception $e) {
	echo "ERROR calculating humidity average";
}


// Calculate average humidity for living space sensor

try {
	$humidity = $DB->average_humidity_last_hour_for_living_space();
	echo "<p>Living space sensor : ";
	echo $humidity;
	echo "% </p>";
} catch (Exception $e) {
	echo "ERROR calculating humidity average";
}

// Calculate average humidity for kitchen sensor

try {
	$humidity = $DB->average_humidity_last_hour_for_kitchen();
	echo "<p>Kitchen space sensor : ";
	echo $humidity;
	echo "% </p>";
} catch (Exception $e) {
	echo "ERROR calculating humidity average";
}

// Calculate total litres of water usage for water sensor for the last hour


try {
	$totalWater = $DB->total_water_sensor_usage_last_hour();
	echo "<p>Total water usage for the last hour is : ";
	echo $totalWater;
	echo " litres </p>";
} catch (Exception $e) {
	echo "ERROR calculating total water usage";
}



?>
</body>
</html>
