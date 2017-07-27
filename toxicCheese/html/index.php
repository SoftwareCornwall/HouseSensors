<html>
<head>
<title>Demo</title>
<link rel="stylesheet" type="text/css" href="css/style.css" />
</head>
<body>
<?php

require_once "database.php"; // database usage class

$DB = new database(); // set up database object
$row = $DB->latest_humidity(); // request latest humidity

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
