<?php
    // Simple SMS send function
    function sendSMS($username, $password, $to, $message, $originator) {
        $URL = 'https://api.textmarketer.co.uk/gateway/'."?username=$username&password=$password&option=xml";
        $URL .= "&to=$to&message=".urlencode($message).'&orig='.urlencode($originator);
        // $fp = fopen($URL, 'r');
        // return fread($fp, 1024);
	return $URL;
    }
    // Example of use
    // $response = sendSMS('2eaTYE', 'DvBGcA', '44', 'ALERT! Your water usage for the last hour is extremely high.', '44');
