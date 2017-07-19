<?php
class DB_Connect {
    private $conn;

    // Connecting to database
    public function connect() {
        require_once 'config.php';

        // Connecting to mysql database
        $this->conn = new mysqli(DB_HOST, DB_USER, DB_PASSWORD, DB_DATABASE);

        // return database handler
        return $this->conn;
    }

    public function Update($humidity)
    {
        $stmt = $this->conn->prepare("UPDATE humidity SET humiditycol = ? WHERE id = 1");
        $stmt->bind_param("s", $humidity);
        $result = $stmt->execute();
        $stmt->close();
    }
}
?>