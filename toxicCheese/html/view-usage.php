<?php
$page = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
$sec = "4";
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="css/style.css" />
<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
</head>
<body>
<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
<script src="https://code.highcharts.com/highcharts.js"></script>
<script src="https://code.highcharts.com/modules/exporting.js"></script>

<div id="container" style="min-width: 310px; height: 400px; margin: 0 auto"></div>

		
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


	/*while ($row = mysql_fetch_array($result)) {
   		extract $row;
   		$datetime *= 1000; // convert from Unix timestamp to JavaScript time
   		$data[] = "[$datetime, $value]";
	}*/
	
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
        echo "Your water consumption for the last month was <span class='" .$waterUsageStyle . "'>";

	echo $waterTotal . " litres</span>.";
	echo "<br>";
	

        echo "Your average humidity for the last month  was <span class='" .$HumidityUsageStyle . "'>";

	echo $average_humidity_last_month . "%</span>.";
	echo "<br>";
	$average_temperature_last_month = $DB->average_temperature_last_month();
	echo "Your average temperature for the last month was " .$average_temperature_last_month. "&deg;C.";


} 

else 

{
	echo "I don't know who you are, access denied";
}

?>

<script type="text/javascript">

Highcharts.chart('container', {
        chart: {
            zoomType: 'x'
        },

        title: {
            text: 'Humidity against time'
        },
        subtitle: {
            text: document.ontouchstart === undefined ?
                    'Click and drag in the plot area to zoom in' : 'Pinch the chart to zoom in'
        },
        xAxis: {
            type: 'datetime'
        },
        yAxis: {
            title: {
                text: 'Humidity / %'
            }
        },
        legend: {
            enabled: false
        },

        plotOptions: {
            area: {
                fillColor: {
                    linearGradient: {
                        x1: 0,
                        y1: 0,
                        x2: 0,
                        y2: 0,


                    },
                    stops: [
                        [0, Highcharts.getOptions().colors[2]],
                        [1, Highcharts.Color(Highcharts.getOptions().colors[3]).setOpacity(0).get('rgba')]
                    ]
                },
                marker: {
                    radius: 2
                },
                lineWidth: 1,
                states: {
                    hover: {
                        lineWidth: 1
                    }
                },
                threshold: null
            },


    
        },


        series: [{
            type: 'area',
            name: 'Humidity',
            data: [Date.UTC(2014,7,4), 60]//[<?php echo join($data, ',') ?>]
	}]
        
    });



		</script>
</body>
</html>