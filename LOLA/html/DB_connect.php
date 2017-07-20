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


    public function Update($humidity, $timestamp)
    {
        $stmt = $this->conn->prepare("INSERT INTO humidity (humiditycol, humidity_timestamp) values (?, ?)");
        $stmt->bind_param("ss", $humidity, $timestamp);
        $result = $stmt->execute();
        $stmt->close();
    }
}
?>