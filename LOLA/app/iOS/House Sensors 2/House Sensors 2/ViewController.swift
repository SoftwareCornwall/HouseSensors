//
//  ViewController.swift
//  House Sensors 2
//
//  Created by Oli Cash on 27/07/2017.
//  Copyright © 2017 LOLA. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var humidity: UILabel!
    @IBOutlet weak var temperature: UILabel!
    @IBOutlet weak var water: UILabel!
    
    @IBOutlet weak var update: UIButton!
    
    var dataValues: NSDictionary!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        loadHumidityData()
        loadTemperatureData()
        loadWaterData()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    func loadHumidityData(){
        var url: NSURL = NSURL(string: "http://178.62.42.117/android_get_humidity_average.php")!
        let request:NSMutableURLRequest = NSMutableURLRequest(url:url as URL)
        var bodyData = "houseId=1"
        request.httpMethod = "POST"

        request.httpBody = bodyData.data(using: String.Encoding.utf8);
        NSURLConnection.sendAsynchronousRequest(request as URLRequest, queue: OperationQueue.main)
        {
            (response, data, error) in
            print(response)
            let responseData = String(data: data!, encoding: String.Encoding.utf8)
            print(responseData)
            
            self.dataValues = try! JSONSerialization.jsonObject(with: data! as Data, options: JSONSerialization.ReadingOptions.mutableContainers) as! NSDictionary
            let dataLine = self.dataValues.object(forKey: "user") as! NSDictionary
            let humidity = dataLine.value(forKey: "humidityAverage") as! Int64
            self.humidity.text = "\(humidity)"
        }
    }
    
    func loadTemperatureData(){
        var url: NSURL = NSURL(string: "http://178.62.42.117/android_get_temperature_average.php")!
        let request:NSMutableURLRequest = NSMutableURLRequest(url:url as URL)
        var bodyData = "houseId=1"
        request.httpMethod = "POST"
        
        request.httpBody = bodyData.data(using: String.Encoding.utf8);
        NSURLConnection.sendAsynchronousRequest(request as URLRequest, queue: OperationQueue.main)
        {
            (response, data, error) in
            print(response)
            let responseData = String(data: data!, encoding: String.Encoding.utf8)
            print(responseData)
            
            self.dataValues = try! JSONSerialization.jsonObject(with: data! as Data, options: JSONSerialization.ReadingOptions.mutableContainers) as! NSDictionary
            let dataLine = self.dataValues.object(forKey: "user") as! NSDictionary
            let temperature = dataLine.value(forKey: "temperatureAverage") as! Int64
            self.temperature.text = "\(temperature)"
        }
    }
    
    func loadWaterData(){
        var url: NSURL = NSURL(string: "http://178.62.42.117/android_get_water_usage.php")!
        let request:NSMutableURLRequest = NSMutableURLRequest(url:url as URL)
        var bodyData = "houseId=1"
        request.httpMethod = "POST"
        
        request.httpBody = bodyData.data(using: String.Encoding.utf8);
        NSURLConnection.sendAsynchronousRequest(request as URLRequest, queue: OperationQueue.main)
        {
            (response, data, error) in
            print(response)
            let responseData = String(data: data!, encoding: String.Encoding.utf8)
            print(responseData)
            
            self.dataValues = try! JSONSerialization.jsonObject(with: data! as Data, options: JSONSerialization.ReadingOptions.mutableContainers) as! NSDictionary
            let dataLine = self.dataValues.object(forKey: "user") as! NSDictionary
            let water = dataLine.value(forKey: "waterUsage") as! Int64
            self.water.text = "\(water)"
            self.water.textColor = UIColor.orange
            if water < 3000 {
                self.water.textColor = UIColor.green
            }
            if water > 6000 {
                self.water.textColor = UIColor.red
            }
        }
    }
    
    @IBAction func update(_ sender: Any) {
        loadHumidityData()
        loadTemperatureData()
        loadWaterData()
    }
}

