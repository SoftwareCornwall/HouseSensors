Feature: Capture Water Usage Of Home
Save the waterusage with a time-stamp in a csv file
Have a summary line of data, with one hour time period, with one minute samples and have L as units.  


@story.3
Scenario: Water Usage 
given a water pump voltage is set at a 10 volts
when 10mins timout
then the summary graph shows previous 10 readings is 1 litre

