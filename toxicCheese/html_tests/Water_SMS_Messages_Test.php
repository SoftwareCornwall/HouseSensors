<?php

require_once '../html/water-spike-check.php';

$sentMessage = '';
function fakeSendSMS($message)
{
	global $sentMessage;
	$sentMessage = $message;
}


final class Water_Spike_SMS_Messages extends PHPUnit_Framework_TestCase
{
	
	public function test_start_large_water_usage_spike_sends_an_SMS_message()
	{
		global $sentMessage;

		$waterUsage = [1, 0.4];

		waterSpikeCheck($waterUsage, 'fakeSendSMS');

		$this->assertNotEquals('', $sentMessage);
	}

	public function test_start_small_water_usage_spike_sends_an_SMS_message()
	{
		global $sentMessage;

		$waterUsage = [0.5, 0.4];

		waterSpikeCheck($waterUsage, 'fakeSendSMS');

		$this->assertNotEquals('', $sentMessage);
	}


	public function test_normal_water_usage_does_not_send_an_SMS_message()
	{
		global $sentMessage;

		$waterUsage = [0.4, 0.1];

		waterSpikeCheck($waterUsage, 'fakeSendSMS');
			
		$this->assertEquals('', $sentMessage);		

	}

	public function test_water_usage_threshold_has_been_crossed_and_maintained_does_not_send_SMS_message() 
	{
		
		global $sentMessage;

		$waterUsage = [0.5, 0.5];

		waterSpikeCheck($waterUsage, 'fakeSendSMS');
			
		$this->assertEquals('', $sentMessage);		

	}


}
