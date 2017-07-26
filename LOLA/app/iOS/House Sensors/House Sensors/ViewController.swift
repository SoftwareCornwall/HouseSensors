//
//  ViewController.swift
//  House Sensors
//
//  Created by Oli Cash on 26/07/2017.
//  Copyright © 2017 LOLA. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    //Our web service url
    let URL_GET_HUMIDITY:String = "http://10.160.50.154/json.php"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        //created NSURL
        let requestURL = NSURL(string: URL_GET_HUMIDITY)
        
        //creating NSMutableURLRequest
        let request = NSMutableURLRequest(url: requestURL! as URL)
        
        //setting the method to post
        request.httpMethod = "GET"
        
        //creating a task to send the post request
        let task = URLSession.shared.dataTask(with: request as URLRequest){
            data, response, error in
            
            //exiting if there is some error
            if error != nil{
                print("error")
                return;
            }
            
            //parsing the response
            do {
                //converting resonse to NSDictionary
                var humidityJSON: NSDictionary!
                humidityJSON = try JSONSerialization.jsonObject(with: data!, options: .mutableContainers) as? NSDictionary
                
                //getting the JSON array teams from the response
                let humidity: NSArray = humidityJSON["humidity"] as! NSArray
                
                //looping through all the json objects in the array teams
                for i in 0 ..< humidity.count{
                    
                    //getting the data at each index
                    let humidityId:Int = humidity[i]["id"] as! Int!
                    let humidityValue:Float = humidity[i]["humidity_value"] as! Float!
                    let humidityMACAdress:String = humidity[i]["mACAdress"] as! String!
                    
                    //displaying the data
                    print("id -> ", humidityId)
                    print("Humidity -> ", humidityValue)
                    print("Mac Address -> ", humidityMACAdress)
                    print("===================")
                    print("")
                    
                }
                    
            } catch {
                print(error)
            }
        }
            //executing the task
            task.resume()
        }
}

