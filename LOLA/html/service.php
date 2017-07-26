<?php

// Create connection
$con=mysqli_connect("127.0.0.1","root","","sensor_data");

// Check connection
if (mysqli_connect_errno())
{
    echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

// This SQL statement selects ALL from the table 'humidity'
$sql = "SELECT * FROM humidity ORDER BY ID DESC LIMIT 2";

// Check if there are results
if ($result = mysqli_query($con, $sql))
{
    // If so, then create a results array and a temporary one
    // to hold the data
    $resultArray = array();
    $tempArray = array();
    $humidityArray = array();

    while($row = $result->fetch_object())
    {
        array_push($humidityArray, $row['humidity_value']);
    }

    $humidityAverage = array_sum($humidityArray) / count($humidityArray);

    // Finally, encode the array to JSON and output the results
    echo json_encode($humidityAverage);
}

// Close connections
mysqli_close($con);
?>




