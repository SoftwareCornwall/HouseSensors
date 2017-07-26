<?php
include 'config.php';
require_once 'fetch_data.php';


//$humidityData = $pdo->prepare("SELECT * FROM humidity ORDER BY id DESC LIMIT 288");

$selectedHouse = $_GET['houseId'];

$sensorCount = FetchData::FetchHouseSensorCount($selectedHouse);

$sensors = FetchData::FetchHouseSensors($selectedHouse);

$humidityData = FetchData::FetchHumidityData($sensors);

$temperatureData = FetchData::FetchTemperatureData($sensors);

$waterData = FetchData::FetchWaterData($sensors);

$houseSelection = $pdo->prepare("SELECT DISTINCT house_id FROM sensor_location ORDER BY id");




//print_r($humidityData);


$humidityFiltered = [];
foreach($humidityData as $item)
{
    $humidityFiltered[$item['humidity_timestamp']][] = $item['humidity_value'];
}

$temperatureFiltered = [];
foreach($temperatureData as $item)
{
    $temperatureFiltered[$item['temperature_timestamp']][] = $item['temperature_value'];
}

$waterFiltered = [];
foreach($waterData as $item)
{
    $waterFiltered[$item['water_timestamp']][] = $item['water_value'];
}

//print_r($temperatureFiltered);


//echo ' rufhdeiodkmslfijdkmlsofijdskmadijdkslaoidfjkmslodwijfdksldwofiujdkslowdfiujckdliufhjlwoieureikwlefjh' . $sensors;


$sec = 60;

header("Refresh: $sec");

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
                    <li class="active">
                        <a href="index.php"><i class="fa fa-fw fa-dashboard"></i> Dashboard</a>
                    </li>
                    <li>
                        <a href="reports.php"><i class="fa fa-fw fa-bar-chart-o"></i> Reports</a>
                    </li>
                </ul>
            </div>
            <!-- /.navbar-collapse -->
        </nav>

        <div id="page-wrapper">

            <div class="container-fluid">

                <div class="row">
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
                                    echo '<li><a href="index.php?houseId=' . $row["house_id"] . '"> House ' . $row["house_id"] . '</a></li>';
                                    //echo "<h1 style='color: deeppink'><marquee scrollamount='20'>The humidity when last recorded was: " . $row['humidity_timestamp'] . "</marquee></h1>";
                                }
                            }

                            ?>
                            <!-- when clicked reload the page with graphs or text?? ask the team :) showing the average
                             humidity, temperature and water -->
                        </ul>
                    </div>
                    <div class="col-lg-12">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <h3 class="panel-title"><i class="fa fa-bar-chart-o fa-fw"></i> Relative Humidity (%)</h3>
                            </div>
                            <div class="panel-body">
                                <div id="humidityChart" style="height: 250px;"></div>
                            </div>
                        </div>
                    </div>
                </div>
                <!-- /.row -->
                <div class="row">
                    <div class="col-lg-12">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <h3 class="panel-title"><i class="fa fa-bar-chart-o fa-fw"></i> Temperature (&#8451;)</h3>
                            </div>
                            <div class="panel-body">
                                <div id="temperatureChart" style="height: 250px;"></div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="row">
                    <div class="col-lg-12">
                        <div class="panel panel-default">
                            <div class="panel-heading">
                                <h3 class="panel-title"><i class="fa fa-bar-chart-o fa-fw"></i> Water Usage</h3>
                            </div>
                            <div class="panel-body">
                                <div id="waterChart" style="height: 250px;"></div>
                            </div>
                        </div>
                    </div>
                </div>
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


    <?php
    echo "
        <script>
            new Morris.Line({
      // ID of the element in which to draw the chart.
      element: 'humidityChart',
      // Chart data records -- each entry in this array corresponds to a point on
      // the chart.
      data: [
           ";

        foreach($humidityFiltered as $time => $values)
        {
            $valuesCount = count($values);
            $valuesSum = array_sum($values);

            $newTime = date("Y-m-d H:i:s", substr($time, 0, 10));

            $averageValue = round($valuesSum / $valuesCount);
            echo"{ time: '". $newTime ."', value: " . $averageValue . " },";
        }
                echo "
      ],
      // The name of the data record attribute that contains x-values.
      xkey: 'time',
      // A list of names of data record attributes that contain y-values.
      ykeys: ['value'],
      // Labels for the ykeys -- will be displayed when you hover over the
      // chart.
      labels: ['Value']
    });
    </script>
    "
?>
// work out how many different mac addresses there are, this will give the number to divide by, compare the mac addresses againt the house though.
    // or maybe look up the house's mac addresses, then sort the data by mac address, arrays are probably your friend.
    <?php
    echo "
        <script>
            new Morris.Line({
      // ID of the element in which to draw the chart.
      element: 'temperatureChart',
      // Chart data records -- each entry in this array corresponds to a point on
      // the chart.
      data: [
           ";
    foreach($temperatureFiltered as $time => $values)
    {
        $valuesCount = count($values);
        $valuesSum = array_sum($values);

        $newTime = date("Y-m-d H:i:s", substr($time, 0, 10));

        $averageValue = round($valuesSum / $valuesCount);
        echo"{ time: '". $newTime ."', value: " . $averageValue . " },";
    }
    echo "
      ],
      // The name of the data record attribute that contains x-values.
      xkey: 'time',
      // A list of names of data record attributes that contain y-values.
      ykeys: ['value'],
      // Labels for the ykeys -- will be displayed when you hover over the
      // chart.
      labels: ['Value']
    });
    </script>
    "
    ?>
    <?php
    echo "
        <script>
            new Morris.Line({
      // ID of the element in which to draw the chart.
      element: 'waterChart',
      // Chart data records -- each entry in this array corresponds to a point on
      // the chart.
      data: [
           ";
    foreach($waterFiltered as $time => $values)
    {
        $valuesCount = count($values);
        $valuesSum = array_sum($values);

        $newTime = date("Y-m-d H:i:s", substr($time, 0, 10));

        $averageValue = $valuesSum / $valuesCount;
        echo"{ time: '". $newTime ."', value: " . $averageValue . " },";
    }
    echo "
      ],
      // The name of the data record attribute that contains x-values.
      xkey: 'time',
      // A list of names of data record attributes that contain y-values.
      ykeys: ['value'],
      // Labels for the ykeys -- will be displayed when you hover over the
      // chart.
      labels: ['Value']
    });
    </script>
    "
    ?>


</body>

</html>
