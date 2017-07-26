<?php

$host = "127.0.0.1";
$dbname = "sensor";
$user = "root";
$password = "";

$pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);

// Read latest humidity reading from database and print on screen
// Currently disabled for purpose of demo on Tuesday

//$humidityData = $pdo->prepare("SELECT * FROM humidity ORDER BY id DESC LIMIT 1");
//if ($humidityData->execute())
//{
//    while ($row = $humidityData->fetch())
//    {
//        $humidityValue = $row['humidity'];
//        echo "<p>Last recorded humidity value on " . $row['date'] . $row['timestamp'] . " is " . $row['humidity'] . "% </p>";
//    }
//}

// Calculate average humidity reading from all data in humidity table and print on screen

$averageHumidity = $pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR");
$total = 0;
$counter = 0;

if ($averageHumidity->execute())
{
    while ($row = $averageHumidity->fetch())
    {
        $total = $total + $row['humidity'];
	$counter++;
    }

echo "<h3>Average humidity for last 60 minutes</h3>";
echo "<p>Both sensors combined  : ";
echo round($total / $counter);
echo "% </p>";

}

// Calculate average humidity for living space sensor

$averageHumidity = $pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR AND macaddress='b8:27:eb:2e:48:3c' ");
$total = 0;
$counter = 0;

if ($averageHumidity->execute())
{
    while ($row = $averageHumidity->fetch())
    {
        $total = $total + $row['humidity'];
	$counter++;
    }

echo "<p>Living space sensor : ";
echo round($total / $counter);
echo "% </p>";

}

// Calculate average humidity for kitchen sensor

$averageHumidity = $pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR AND macaddress='b8:27:eb:27:77:c9' ");
$total = 0;
$counter = 0;

if ($averageHumidity->execute())
{
    while ($row = $averageHumidity->fetch())
    {
        $total = $total + $row['humidity'];
	$counter++;
    }

echo "<p>Kitchen sensor  : ";
echo round($total / $counter);
echo "% </p>";

}

// Calculate total litres of water usage for water sensor for the last hour

$totalWater = $pdo->prepare("SELECT * FROM water WHERE timestamp>NOW()-INTERVAL 1 HOUR");
$total = 0;

if ($totalWater->execute())
{
    while ($row = $totalWater->fetch())
    {
        $total = $total + $row['waterflow'];
    }

echo "<h3>Total water usage for the last hour is  : ";
echo ($total);
echo " litres.</h3>";

}



?>