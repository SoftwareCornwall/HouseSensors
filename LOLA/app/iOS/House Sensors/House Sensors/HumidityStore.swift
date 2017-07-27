//
//  humidity.swift
//  House Sensors
//
//  Created by Oli Cash on 26/07/2017.
//  Copyright © 2017 LOLA. All rights reserved.
//

import Foundation

class HumidityStore: NSObject {
    
    //properties
    
    var humidity_value: String?
    
    //empty constructor
    
    override init()
    {
        
    }
    
    //construct with @name, @address, @latitude, and @longitude parameters
    
    init(id: String, humidity_value: String, humidity_timestamp: String, mac_address: String) {
        
        self.humidity_value = humidity_value
        
    }
    
    //prints object's current state
    
    override var description: String {
        return "Humidity: \(humidity_value)"
        
    }

}
