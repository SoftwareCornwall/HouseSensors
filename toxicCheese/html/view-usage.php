<html>
<head>
<link rel="stylesheet" type="text/css" href="css/style.css" />
<meta http-equiv=”refresh” content=”1" />
</head>
<body>
<?php

require_once "database.php"; // database usage class

$DB = new database();
$row = $DB->latest_humidity();

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
	$total =0;

	if ($totalWater->execute())
	{
	   while ($row = $totalWater->fetch())
	   {
	       $total = $total + $row['waterflow'];
	   }

	}

	if ($total >= 1001) {
		$usageStyle = "high_usage";
	}

	if ($total <1001 && $total > 500) {
		$usageStyle = "average_usage";
	}

	if ($total <500) {
		$usageStyle = "low_usage";
	}


	
	echo "Hello Will <br>";
        echo "Your water consumption for the last month is <span class='" .$usageStyle . "'>";

	echo $total . " litres.<span>";
	echo "<br>";



} 

else 

{
	echo "I don't know who you are, access denied";
}

?>
</body>
</html>