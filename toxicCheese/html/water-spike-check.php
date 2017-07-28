<?php

function waterSpikeCheck($waterUsage, $sendSMS) 
{

	if ($waterUsage[1] < 0.5 && $waterUsage[0] >= 0.5) 
	{
		call_user_func($sendSMS, "ALERT! Your water usage is extremely high.");		
	}
}
