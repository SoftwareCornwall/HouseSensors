<?php
include 'config.php';


$humidityData = $pdo->prepare("SELECT * FROM humidity WHERE id =1");



if ($humidityData->execute()) {
    while ($row = $humidityData->fetch()) {
        echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humiditycol'] . "</marquee></h1>";
    }
}

