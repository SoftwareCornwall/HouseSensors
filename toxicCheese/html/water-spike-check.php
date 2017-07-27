<?php

function waterSpikeCheck($waterUsage, $sendSMS) 
{

	if ($waterUsage[1] < 15 && $waterUsage[0] >= 15) 
	{
		call_user_func($sendSMS, "ALERT! Your water usage is extremely high.");		
	}
}
