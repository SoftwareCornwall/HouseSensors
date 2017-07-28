<?php
/**
 * Created by PhpStorm.
 * User: Liam
 * Date: 28/07/2017
 * Time: 10:23
 */
class PrintCSV
{

    static function printHumidityReport($selectedHouse)
    {
        global $pdo;

        $sensors = FetchData::FetchHouseSensors($selectedHouse);

        header('Content-Type: text/csv; charset=utf-8');
        header('Content-Disposition: attachment; filename=humidity-house-' . $selectedHouse . '.csv');
        $output = fopen("php://output", "w");
        fputcsv($output, array('ID', 'Humidity Timestamp', 'Humidity Value', 'Sensor Location'));

        $printReport = $pdo->prepare("SELECT humidity.id, humidity.humidity_timestamp, humidity.humidity_value, sensor_location.room FROM humidity INNER JOIN sensor_location ON humidity.mac_address = sensor_location.mac_address  WHERE humidity.mac_address IN ('" . implode("','",$sensors) . "')");

        if ($printReport->execute()) {
            while ($row = $printReport->fetch(PDO::FETCH_ASSOC)) {
                fputcsv($output, $row);
            }
        }
        fclose($output);
        exit;
    }
    static function printTemperatureReport($selectedHouse)
    {
        global $pdo;

        $sensors = FetchData::FetchHouseSensors($selectedHouse);

        header('Content-Type: text/csv; charset=utf-8');
        header('Content-Disposition: attachment; filename=temperature-house-' . $selectedHouse . '.csv');
        $output = fopen("php://output", "w");
        fputcsv($output, array('ID', 'Temperature Timestamp', 'Temperature Value', 'Sensor Location'));

        $printReport = $pdo->prepare("SELECT temperature.id, temperature.temperature_timestamp, temperature.temperature_value, sensor_location.room FROM temperature INNER JOIN sensor_location ON temperature.mac_address = sensor_location.mac_address  WHERE temperature.mac_address IN ('" . implode("','",$sensors) . "')");

        if ($printReport->execute()) {
            while ($row = $printReport->fetch(PDO::FETCH_ASSOC)) {
                fputcsv($output, $row);
            }
        }
        fclose($output);
        exit;
    }
    static function printWaterReport($selectedHouse)
    {
        global $pdo;

        $sensors = FetchData::FetchHouseSensors($selectedHouse);

        header('Content-Type: text/csv; charset=utf-8');
        header('Content-Disposition: attachment; filename=water-house-' . $selectedHouse . '.csv');
        $output = fopen("php://output", "w");
        fputcsv($output, array('ID', 'Water Timestamp', 'Water Value', 'Sensor Location'));

        $printReport = $pdo->prepare("SELECT water.id, water.water_timestamp, water.water_value, sensor_location.room FROM water INNER JOIN sensor_location ON water.mac_address = sensor_location.mac_address  WHERE water.mac_address IN ('" . implode("','",$sensors) . "')");

        if ($printReport->execute()) {
            while ($row = $printReport->fetch(PDO::FETCH_ASSOC)) {
                fputcsv($output, $row);
            }
        }
        fclose($output);
        exit;
    }


}