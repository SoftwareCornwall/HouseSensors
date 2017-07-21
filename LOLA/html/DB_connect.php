<?php
class DB_Connect
{
    private $conn;

    // Connecting to database
    public function Connect()
    {
        require_once 'config.php';

        // Connecting to mysql database
        $this->conn = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_DATABASE);

        // return database handler
        return $this->conn;
    }


    public function SaveHumidity($humidity, $timestamp, $macAddress)
    {
        $stmt = $this->conn->prepare("INSERT INTO humidity (humidity_value, humidity_timestamp, mac_address) values (?, ?, ?)");
        $stmt->bind_param("sss", $humidity, $timestamp, $macAddress);
        $result = $stmt->execute();
        $stmt->close();
    }

    public function SaveTemperature($temperature, $timestamp, $macAddress)
    {
        $stmt = $this->conn->prepare("INSERT INTO temperature (temperature_value, temperature_timestamp, mac_address) values (?, ?, ?)");
        $stmt->bind_param("sss", $temperature, $timestamp, $macAddress);
        $result = $stmt->execute();
        $stmt->close();
    }
}
?>