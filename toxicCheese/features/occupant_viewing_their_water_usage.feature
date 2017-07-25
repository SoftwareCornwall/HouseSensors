Feature: Occupant viewing their water usage
High > 1000L >= Medium > 500L >= Low


Scenario : As an identified occupant I want to see my water usage for the past month

Given : An identified occupant

When : The summary page is displayed

Then : Show the total water usage for the past month


Scenario : As an occupant I want to check if my water usage is high

Given : An identified occupant with water usage in the past month of 1001L

When : The summary page is displayed

Then : It will highlight the total water usage for the past month in red


Scenario : As an occupant I want to check if my water usage is decent

Given : An identified occupant with water usage in the past month of  501L
    
When : The summary page is displayed

Then : It will highlight the total water usage for the past month in amber



Scenario : As an occupant I want to check if my water usage is efficient

Given : An identified occupant with water usage in the past month of 500L
    
When : The summary page is displayed

Then : It will highlight the total water usage for the past month in green





