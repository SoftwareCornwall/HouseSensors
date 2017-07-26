Feature: Occupant Viewing Utility Usage
Hardcoded limits
3 tier (High > 6000L >= Moderate > 3000L >= Low)
Mobile



@Story_3_1
Scenario: High Water Usage
Given water usage for the last month is 6001,
When the data is checked on a mobile device,
Then the water usage indicator is red.

@Story_3_1
Scenario: Moderate Water Usage
Given water usage for the last month is 4500,
When the data is checked on a mobile device,
Then the water usage indicator is amber.

@Story_3_1
Scenario: Low Water Usage
Given water usage for the last month is 1500,
When the data is checked on a mobile device,
Then the water usage indicator is green.



@Story_3_3
Scenario: Checking Data Outside Sensor's LAN
Given you are outside the sensor's LAN,
When checking data,
Then data can be viewed.



@Story_3_4
Scenario: Alert Above High Water Threshold
Given water usage for the last hour is 10L,
When logged into app on mobile device,
Then a notification is received regarding the alert. 
