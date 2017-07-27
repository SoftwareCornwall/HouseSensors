//
//  ViewController.swift
//  House Sensors
//
//  Created by Oli Cash on 26/07/2017.
//  Copyright © 2017 LOLA. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, HumidityGetProtocol {
    
    var feedItems: NSArray = NSArray()
    var selectedHumidity : HumidityStore = HumidityStore()
    @IBOutlet weak var listTableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        //set delegates and initialize homeModel
        
        self.listTableView.delegate = self
        self.listTableView.dataSource = self
        
        let humidityGet = HumidityGet()
        humidityGet.delegate = self
        humidityGet.downloadItems()
        
    }
    
    func itemsDownloaded(items: NSArray) {
        
        feedItems = items
        self.listTableView.reloadData()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // Return the number of feed items
        return feedItems.count
        
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        // Retrieve cell
        let cellIdentifier: String = "BasicCell"
        let myCell: UITableViewCell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier)!
        // Get the location to be shown
        let item: HumidityStore = feedItems[indexPath.row] as! HumidityStore
        // Get references to labels of cell
        myCell.textLabel!.text = item.humidity_value
        
        return myCell
    }
}

