Feature: Occupant viewing their humidity
High > 60% >= Medium > 55% >= Low


Scenario : As an identified occupant I want to see my humidity for the past month

Given : An identified occupant

When : The summary page is displayed

Then : Show the average humidity for the past month


Scenario : As an occupant I want to check if my humidity is high

Given : An identified occupant with mean average humidity level in the past month of 61%

When : The summary page is displayed

Then : It will highlight the mean average humidity level for the past month in red


Scenario : As an occupant I want to check if my humidity is medium

Given : An identified occupant with mean average humidity level in the past month of 56%

When : The summary page is displayed

Then : It will highlight the mean average humidity level for the past month in amber


Scenario : As an occupant I want to check if my humidity is low

Given : An identified occupant with mean average humidity level in the past month of 54%

When : The summary page is displayed

Then : It will highlight the mean average humidity level for the past month in green
