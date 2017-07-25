Feature: MultipleSensors
Read and display data from multiple humidity sensors
Sample data collected every 5 minutes from multiple sensors
Data displayed as mean average summary line


@Story_1
Scenario: Identify individual sensor
Given 2 sensors
When humidity at sensor 'X' is 10% and humidity at sensor 'Y' is 20%
Then data received by server from sensor 'X' is 10% and from sensor 'Y' is 20%

@Story_1
Scenario: Average of data
Given humidity at sensor 'X' is 10% and humidity at sensor 'Y' is 20%
When viewing data
Then value displayed is 15%

@Story_2
Scenario: Water sensor connected
Given flow sensor output of 275Hz
When vieing data
Then value displayed is 0.125L/min