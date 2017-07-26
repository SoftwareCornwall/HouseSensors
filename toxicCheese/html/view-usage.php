<?php

$message = $_GET['house'];

if ($message == '89hab723hd') {
	
	echo "Hello Will.<br>";
        echo "Your water consumption for the last month is ";
 
	// Calculate total litres of water usage for water sensor for the last hour

	$host = "127.0.0.1";
	$dbname = "sensor";
	$user = "root";
	$password = "";
	$usageStyle = "";

	$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

	$totalWater = $pdo->prepare("SELECT * FROM water WHERE timestamp>NOW()-INTERVAL 1 MONTH");
	$total =0;

	if ($totalWater->execute())
	{
	   while ($row = $totalWater->fetch())
	   {
	       $total = $total + $row['waterflow'];
	   }

	}

	if ($totalwater >= 1001) {
		$usageStyle = "high_usage";
	}

	if ($totalwater <1001 && $totalwater > 500) {
		$usageStyle = "decent_usage";
	}

	if ($totalwater <500) {
		$usageStyle = "low_usage";
	}


	echo $total . " litres.";
	echo "<br>";
	echo $usageStyle;



} 

else 

{
	echo "I don't know who you are, access denied";
}

?>