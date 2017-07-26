//
//  humidityGet.swift
//  House Sensors
//
//  Created by Oli Cash on 26/07/2017.
//  Copyright © 2017 LOLA. All rights reserved.
//

import Foundation

protocol HumidityGetProtocol: class {
    func itemsDownloaded(items: NSArray)
}


class HumidityGet: NSObject, URLSessionDataDelegate {
    
    //properties
    
    weak var delegate: HumidityGetProtocol!
    
    var data = Data()
    
    let urlPath: String = "http://10.160.50.154/service.php"
    
    func downloadItems() {
        
        let url: URL = URL(string: urlPath)!
        let defaultSession = Foundation.URLSession(configuration: URLSessionConfiguration.default)
        
        let task = defaultSession.dataTask(with: url) { (data, response, error) in
            
            if error != nil {
                print("Failed to download data")
            }else {
                print("Data downloaded")
                self.parseJSON(data!)
            }
            
        }
        
        task.resume()
    }
    
    func parseJSON(_ data:Data) {
        
        var jsonResult = NSArray()
        
        do{
            jsonResult = try JSONSerialization.jsonObject(with: data, options:JSONSerialization.ReadingOptions.allowFragments) as! NSArray
            
        } catch let error as NSError {
            print(error)
            
        }
        
        var jsonElement = NSDictionary()
        let humidities = NSMutableArray()
        
        for i in 0 ..< jsonResult.count
        {
            
            jsonElement = jsonResult[i] as! NSDictionary
            
            let humidity = HumidityStore()
            
            //the following ensures none of the JsonElement values are nil through optional binding
            if let id = jsonElement["id"] as? String,
                let humidity_value = jsonElement["humidity_value"] as? String,
                let humidity_timestamp = jsonElement["humidity_timestamp"] as? String,
                let mac_address = jsonElement["mac_address"] as? String
            {
                
                humidity.id = id
                humidity.humidity_value = humidity_value
                humidity.humidity_timestamp = humidity_timestamp
                humidity.mac_address = mac_address
                
            }
            
            humidities.add(humidity)
            
        }
        
        DispatchQueue.main.async(execute: { () -> Void in
            
            self.delegate.itemsDownloaded(items: humidities)
            
        })
    }
}
