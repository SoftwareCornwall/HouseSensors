<?php
	$DB = new database();

	try {
		$waterUsage = $DB->total_water_sensor_usage_last_hour();
		echo $waterUsage;
	}
	catch {
			echo "error calculting total water usage";
	}
?>
