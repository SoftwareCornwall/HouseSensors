<?php

class database 
{
	private $pdo;

	public function __construct() {
		$host = "127.0.0.1";
		$dbname = "sensor";
		$user = "root";
		$password = "";
		$this->pdo = new PDO("mysql:dbname=$dbname;host=$host" , $user , $password);
	}

	public function latest_humidity() {
		$humidityData = $this->pdo->prepare("SELECT * FROM humidity ORDER BY id DESC LIMIT 1");
		if ($humidityData->execute())
		{
		    while ($row = $humidityData->fetch())
		    {
			return $row;
		    }
		}
	}

	public function average_humidity_last_hour() {
		$averageHumidity = $this->pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR");
		$total = 0;
		$counter = 0;
		
		if ($averageHumidity->execute())
		{
		    while ($row = $averageHumidity->fetch())
		    {
		        $total = $total + $row['humidity'];
			$counter++;
		    }
		
			return round($total / $counter);
		
		}
		throw new Exception("Unable to calculate humidity");

	}

	public function average_humidity_last_hour_for_living_space() {
		$averageHumidity = $this->pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR AND macaddress='b8:27:eb:2e:48:3c'");
		$total = 0;
		$counter = 0;
		
		if ($averageHumidity->execute())
		{
		    while ($row = $averageHumidity->fetch())
		    {
		        $total = $total + $row['humidity'];
			$counter++;
		    }
			return round($total / $counter);
		
		}
		throw new Exception("Unable to calculate living room sensor humidity");

	}

	public function average_humidity_last_hour_for_kitchen() {
		$averageHumidity = $this->pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 HOUR AND macaddress='b8:27:eb:27:77:c9'");
		$total = 0;
		$counter = 0;
		
		if ($averageHumidity->execute())
		{
		    while ($row = $averageHumidity->fetch())
		    {
		        $total = $total + $row['humidity'];
			$counter++;
		    }
			return round($total / $counter);
		
		}
		throw new Exception("Unable to calculate kitchen sensor humidity");

	}

	public function total_water_sensor_usage_last_hour() {
		$totalWater = $this->pdo->prepare("SELECT * FROM water WHERE timestamp>NOW()-INTERVAL 1 HOUR");
		$total = 0;
		
		if ($totalWater->execute())
		{
		    while ($row = $totalWater->fetch())
		    {
		        $total = $total + $row['waterflow'];
		    }
			return ($total);
		}
		throw new Exception("Unable to calculate water usage");
	}

	public function average_humidity_last_month() {
		$averageHumidity = $this->pdo->prepare("SELECT * FROM humidity WHERE timestamp>NOW()-INTERVAL 1 MONTH");
		$total = 0;
		$counter = 0;
		
		if ($averageHumidity->execute())
		{
		    while ($row = $averageHumidity->fetch())
		    {
		        $total = $total + $row['humidity'];
			$counter++;
		    }
		
			return round($total / $counter);
		
		}
		throw new Exception("Unable to calculate humidity");

	}
	
};
