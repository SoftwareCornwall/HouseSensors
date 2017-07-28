<?php

include "config.php";
require_once 'fetch_data.php';
require_once 'print_csv.php';

$houseSelection = $pdo->prepare("SELECT DISTINCT house_id FROM sensor_location");

if(isset($_POST['printReport']))
{
    $selectedHouse = $_GET['houseId'];

    if(isset($_POST['export'])) {

        if($_POST['export'] == "humidityCheck")
        {
            PrintCSV::printHumidityReport($selectedHouse);
        }
        else  if($_POST['export'] == "temperatureCheck")
        {
            PrintCSV::printTemperatureReport($selectedHouse);
        }
        else  if($_POST['export'] == "waterCheck")
        {
            PrintCSV::printWaterReport($selectedHouse);
        }

    }
}

?>

<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Dashboard</title>

    <!-- Bootstrap Core CSS -->
    <link href="css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="css/sb-admin.css" rel="stylesheet">

    <!-- Morris Charts CSS -->
    <link href="css/morris.css" rel="stylesheet">

    <link href="css/css.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
            <!-- Brand and toggle get grouped for better mobile display -->
            <div class="navbar-header">
                <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-ex1-collapse">
                    <span class="sr-only">Toggle navigation</span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                    <span class="icon-bar"></span>
                </button>
                <a class="navbar-brand" href="index.php">House Sensor Dashboard</a>
            </div>
            <!-- Top Menu Items -->
            <ul class="nav navbar-right top-nav">
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-envelope"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu message-dropdown">
                        <li class="message-preview">
                            <a href="#">
                                <div class="media">
                                    <span class="pull-left">
                                        <img class="media-object" src="http://placehold.it/50x50" alt="">
                                    </span>
                                    <div class="media-body">
                                        <h5 class="media-heading"><strong>Sarah</strong>
                                        </h5>
                                        <p class="small text-muted"><i class="fa fa-clock-o"></i> Yesterday at 4:32 PM</p>
                                        <p>Lorem ipsum dolor sit amet, consectetur...</p>
                                    </div>
                                </div>
                            </a>
                        </li>


                        <li class="message-footer">
                            <a href="#">Read All New Messages</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-bell"></i> <b class="caret"></b></a>
                    <ul class="dropdown-menu alert-dropdown">
                        <li>
                            <a href="#">Alert Name <span class="label label-default">Alert Badge</span></a>
                        </li>
                        <li>
                            <a href="#">Alert Name <span class="label label-primary">Alert Badge</span></a>
                        </li>
                        <li>
                            <a href="#">Alert Name <span class="label label-success">Alert Badge</span></a>
                        </li>
                        <li>
                            <a href="#">Alert Name <span class="label label-info">Alert Badge</span></a>
                        </li>
                        <li>
                            <a href="#">Alert Name <span class="label label-warning">Alert Badge</span></a>
                        </li>
                        <li>
                            <a href="#">Alert Name <span class="label label-danger">Alert Badge</span></a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="#">View All</a>
                        </li>
                    </ul>
                </li>
                <li class="dropdown">
                    <a href="#" class="dropdown-toggle" data-toggle="dropdown"><i class="fa fa-user"></i> Sarah <b class="caret"></b></a>
                    <ul class="dropdown-menu">
                        <li>
                            <a href="#"><i class="fa fa-fw fa-user"></i> Profile</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-envelope"></i> Inbox</a>
                        </li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-gear"></i> Settings</a>
                        </li>
                        <li class="divider"></li>
                        <li>
                            <a href="#"><i class="fa fa-fw fa-power-off"></i> Log Out</a>
                        </li>
                    </ul>
                </li>
            </ul>
            <!-- Sidebar Menu Items - These collapse to the responsive navigation menu on small screens -->
            <div class="collapse navbar-collapse navbar-ex1-collapse">
                <ul class="nav navbar-nav side-nav">
                    <li >
                        <a href="index.php"><i class="fa fa-fw fa-dashboard"></i> Dashboard</a>
                    </li>
                    <li class="active">
                        <a href="reports.php"><i class="fa fa-fw fa-bar-chart-o"></i> Reports</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">

                <div class="row">
                    <div class="col-lg-12">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <h3 class="panel-title"><i class="fa fa-bar-chart-o fa-fw"></i> Household Report</h3>
                            </div>
                            <div class="panel-body">
                                <div class="dropdown">
                                    <button class="btn btn-default dropdown-toggle" type="button" id="dropdownMenu1" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true">
                                        <?php
                                        if(isset($_GET[houseId]))
                                        {
                                        echo "House " . $_GET['houseId'];
                                        }
                                        else
                                        {
                                        echo "Please Select a Household";
                                        }?>
                                        <span class="caret"></span>
                                    </button>
                                    <ul class="dropdown-menu scrollable-menu" role="menu" aria-labelledby="dropdownMenu1">

                                        <?php
                                        if ($houseSelection->execute())
                                        {
                                            while ($row = $houseSelection->fetch())
                                            {
                                                echo '<li><a href="reports.php?houseId=' . $row["house_id"] . '"> House ' . $row["house_id"] . '</a></li>';
                                                //echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humidity_timestamp'] . "</marquee></h1>";
                                            }
                                        }

                                        ?>
                                        <!-- when clicked reload the page with graphs or text?? ask the team :) showing the average
                                         humidity, temperature and water -->
                                    </ul>
                                </div>
                                maybe put some selected house information here?
                            </div>
                        </div>
                    </div>
                </div>

                <form method="post">
                <div class="col-lg-4">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <h3 class="panel-title"><i class="fa fa-clock-o fa-fw"></i> Humidity (%)</h3>
                        </div>
                        <div class="panel-body">
                            <div class="list-group">
                                <?php
                                if($_GET['houseId'])
                                {
                                    $houseID = $_GET['houseId'];

                                    $houseSensors = $pdo->prepare("SELECT * FROM sensor_location WHERE house_id=:house");
                                    $houseSensors->bindValue(':house', $houseID);

                                    if ($houseSensors->execute())
                                    {
                                        while ($roomRow = $houseSensors->fetch())
                                        {
                                            $getSensorMAC = $pdo->prepare("SELECT * FROM sensor_location WHERE room=:room");
                                            $getSensorMAC->bindParam(':room', $roomRow['room']);

                                            if ($getSensorMAC->execute())
                                            {
                                                while ($macRow = $getSensorMAC->fetch())
                                                {
                                                    $macAddress = $macRow['mac_address'];

                                                    $getSensorinfo = $pdo->prepare("SELECT * FROM humidity WHERE mac_address=:mac ORDER BY id LIMIT 12");
                                                    $getSensorinfo->bindParam(':mac', $macAddress);

                                                    //echo $macAddress;

                                                    $humidityArray = array();

                                                    if($getSensorinfo->execute())
                                                    {
                                                        while($averageRow = $getSensorinfo->fetch())
                                                        {
                                                            //echo $averageRow['humidity_value'];
                                                            array_push($humidityArray, $averageRow['humidity_value']);
                                                        }
                                                    }
                                                    //print_r ($humidityArray);
                                                    $humidityAverage = array_sum($humidityArray) / count($humidityArray);
                                                }
                                            }
                                            echo '<a href="#" class="list-group-item">
                                                        <span class="badge">' . round($humidityAverage) . '</span>
                                                        <i class="fa fa-fw fa-calendar"></i> ' . $roomRow['room'] . '
                                                  </a>';
                                            //echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humidity_timestamp'] . "</marquee></h1>";
                                        }
                                    }
                                }
                                else
                                {
                                    echo "Please select a house to view the sensor averages";
                                }
                                ?>
                            </div>
                            <div class="text-right">
                                <div class="checkbox">
                                    <label><input type="radio" name="export" id="humidityCheck" value="humidityCheck">Check to print humidity report</label>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col-lg-4">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <h3 class="panel-title"><i class="fa fa-clock-o fa-fw"></i> Temperature (&#8451;)</h3>
                        </div>
                        <div class="panel-body">
                            <div class="list-group">
                                <?php
                                if($_GET['houseId'])
                                {

                                    $houseID = $_GET['houseId'];

                                    $houseSensors = $pdo->prepare("SELECT * FROM sensor_location WHERE house_id=:house");
                                    $houseSensors->bindValue(':house', $houseID);

                                    if ($houseSensors->execute())
                                    {
                                        while ($roomRow = $houseSensors->fetch())
                                        {
                                            $getSensorMAC = $pdo->prepare("SELECT * FROM sensor_location WHERE room=:room");
                                            $getSensorMAC->bindParam(':room', $roomRow['room']);

                                            if ($getSensorMAC->execute())
                                            {
                                                while ($macRow = $getSensorMAC->fetch())
                                                {
                                                    $macAddress = $macRow['mac_address'];

                                                    $getSensorinfo = $pdo->prepare("SELECT * FROM temperature WHERE mac_address=:mac ORDER BY id LIMIT 12");
                                                    $getSensorinfo->bindParam(':mac', $macAddress);

                                                    //echo $macAddress;

                                                    $temperatureArray = array();

                                                    if($getSensorinfo->execute())
                                                    {
                                                        while($averageRow = $getSensorinfo->fetch())
                                                        {
                                                            //echo $averageRow['humidity_value'];
                                                            array_push($temperatureArray, $averageRow['temperature_value']);
                                                        }
                                                    }
                                                    //print_r ($humidityArray);
                                                    $temperatureAverage = array_sum($temperatureArray) / count($temperatureArray);
                                                }
                                            }
                                            echo '<a href="#" class="list-group-item">
                                                        <span class="badge">' . round($temperatureAverage) . '</span>
                                                        <i class="fa fa-fw fa-calendar"></i> ' . $roomRow['room'] . '
                                                  </a>';
                                            //echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humidity_timestamp'] . "</marquee></h1>";
                                        }
                                    }
                                }
                                else
                                {
                                    echo "Please select a house to view the sensor averages";
                                }
                                ?>
                            </div>
                            <div class="text-right">
                                <div class="checkbox">
                                    <label><input type="radio" name="export" id="temperatureCheck" value="temperatureCheck">Check to print temperature report</label>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col-lg-4">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            <h3 class="panel-title"><i class="fa fa-clock-o fa-fw"></i> Water Usage</h3>
                        </div>
                        <div class="panel-body">
                            <div class="list-group">
                                <?php
                                if($_GET['houseId'])
                                {
                                    $houseID = $_GET['houseId'];

                                    $houseSensors = $pdo->prepare("SELECT * FROM sensor_location WHERE house_id=:house");
                                    $houseSensors->bindValue(':house', $houseID);

                                    if ($houseSensors->execute())
                                    {
                                        while ($roomRow = $houseSensors->fetch())
                                        {
                                            $getSensorMAC = $pdo->prepare("SELECT * FROM sensor_location WHERE room=:room");
                                            $getSensorMAC->bindParam(':room', $roomRow['room']);

                                            if ($getSensorMAC->execute())
                                            {
                                                while ($macRow = $getSensorMAC->fetch())
                                                {
                                                    $macAddress = $macRow['mac_address'];

                                                    $getSensorinfo = $pdo->prepare("SELECT * FROM water WHERE mac_address=:mac ORDER BY id LIMIT 12");
                                                    $getSensorinfo->bindParam(':mac', $macAddress);

                                                    //echo $macAddress;

                                                    $waterArray = array();

                                                    if($getSensorinfo->execute())
                                                    {
                                                        while($averageRow = $getSensorinfo->fetch())
                                                        {
                                                            //echo $averageRow['humidity_value'];
                                                            array_push($waterArray, $averageRow['water_value']);
                                                        }
                                                    }
                                                    //print_r ($humidityArray);
                                                    $waterAverage = array_sum($waterArray) / count($waterArray);
                                                }
                                            }
                                            echo '<a href="#" class="list-group-item">
                                                        <span class="badge">' . $waterAverage . '</span>
                                                        <i class="fa fa-fw fa-calendar"></i> ' . $roomRow['room'] . '
                                                  </a>';
                                            //echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humidity_timestamp'] . "</marquee></h1>";
                                        }
                                    }
                                }
                                else
                                {
                                    echo "Please select a house to view the sensor averages";
                                }
                                ?>
                            </div>
                            <div class="text-right">
                                <div class="checkbox">
                                    <label><input type="radio" id="waterCheck" name="export" value="waterCheck">Check to print water report</label>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                    <input type="submit" id="printReport" name="printReport" class="btn btn-primary" value="export report">
                </form>
                <!-- /.row -->
            </div>
            <!-- /.container-fluid -->

        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="js/jquery.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="js/bootstrap.min.js"></script>

    <script src="https://code.highcharts.com/highcharts.js"></script>
    <script src="https://code.highcharts.com/modules/exporting.js"></script>



    <script src="js/raphael.min.js"></script>
    <script src="js/morris.min.js"></script>
    <script src="js/morris-data.js"></script>




</body>

</html>
