<?php
$page = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
$sec = "4";
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="css/style.css" />
<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
</head>
<body>
<?php

require_once "database.php"; // database usage class

$DB = new database();
$average_humidity_last_month = $DB->average_humidity_last_month();

$message = $_GET['house'];

if ($message == '89hab723hd') {
 
	// Calculate total litres of water usage for water sensor for the last hour

	$host = "127.0.0.1";
	$dbname = "sensor";
	$user = "root";
	$password = "";
	$usageStyle = "";

	$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

	$totalWater = $pdo->prepare("SELECT * FROM water WHERE timestamp>NOW()-INTERVAL 1 MONTH");
	$waterTotal =0;
	
	if ($totalWater->execute())
	{
	   while ($row = $totalWater->fetch())
	   {
	       $waterTotal = $waterTotal + $row['waterflow'];
	   }

	}


	if ($waterTotal >= 1001) {
		$waterUsageStyle = "high_usage";
	}

	if ($waterTotal <1001 && $waterTotal > 500) {
		$waterUsageStyle = "average_usage";
	}

	if ($waterTotal <500) {
		$waterUsageStyle = "low_usage";
	}

	//Humidity over last month for all sensors in the house
	
	if ($average_humidity_last_month > 60) {

		$HumidityUsageStyle = "high_usage";
		

	}

	if ($average_humidity_last_month <= 60 && $average_humidity_last_month > 55) {
		$HumidityUsageStyle = "average_usage";
	}

	if ($average_humidity_last_month <= 55) {
		$HumidityUsageStyle = "low_usage";
	}

	echo "Hello Will <br>";
        echo "Your water consumption for the last month is <span class='" .$waterUsageStyle . "'>";

	echo $waterTotal . " litres</span>.";
	echo "<br>";
	

        echo "Your average humidity for the last month  is <span class='" .$HumidityUsageStyle . "'>";

	echo $average_humidity_last_month . "%</span>.";
	echo "<br>";



} 

else 

{
	echo "I don't know who you are, access denied";
}

?>
</body>
</html>