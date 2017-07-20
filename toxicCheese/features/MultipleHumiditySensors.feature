Feature: View Multiple Humidity Sensors
Summary line of data, one hour default time period for the graph, take 5 minute samples. Also show mean average of past hour. No faking! Data precision is integer.

@story.1
Scenario:  
given two sensors
when sensors senses humidity
then print humidity of two sensors as an average