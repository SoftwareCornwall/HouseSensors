Feature: HumidityReading
View raw data from a single sensor
Updates in browser every 5 minutes

@Story_1
Scenario: Value returned from sensor
Given 5 minutes has elapsed
When sensor is connected
Then check reading received

@Story_1
Scenario: Constant humidity
Given humidity constant at 10% for over 5 minutes
When receiving next reading
Then no change from previous reading

@Story_1
Scenario: Update reading
Given humidity changed from 10% to 20%
When 5 minutes has elapsed
Then check different reading from sensor
