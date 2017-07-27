#!/bin/bash

#sudo apt-get -y update
#sudo apt-get -y install apache2
#sudo apt-get -y install mysql-server
#sudo apt-get -y install php libapache2-mod-php php-mcrypt php-mysql

mysql -u root < sql/sensor_data_humidity.sql
mysql -u root < sql/sensor_data_sensor_location.sql
mysql -u root < sql/sensor_data_temperature.sql
mysql -u root < sql/sensor_data_users.sql
mysql -u root < sql/sensor_data_water.sql

mysql -u root < sql/create_users.sql

echo Copying website files...

rm -R /var/www/html
cp -R ../html /var/www/html

