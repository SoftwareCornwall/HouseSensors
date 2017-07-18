Feature: view humidity
show uncalibrated humidity level; in a browser window with value coming from humidity sensor locally

@story.1
Scerario: scenario
given sensor
when sensor senses humidity
then print humidity


