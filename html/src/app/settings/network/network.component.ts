import { Component, OnInit } from '@angular/core';
import { SettingsService } from '../settings.service';

@Component({
  selector: 'app-network',
  templateUrl: './network.component.html',
  styleUrls: ['./network.component.css']
})
export class NetworkComponent implements OnInit {

  networks: Array<any>;
  config: any;
  current: any;
  setup: String;
  
  constructor(
    private settingsService: SettingsService
  ) { }

  ngOnInit() {

    //original Data
   // this.settingsService.getNetwork().subscribe(network=> {
   //   this.setCurrentData(network);
  //  });


  this.config = {
      ap_ip: "172.168.0.1",
      ap_network: "Controller",
      ap_password: "password",
      wifi_network: "Ratiner",
      wifi_password: "123",
      wifi_enabled: true,
      RSSI: -55,
      ip: "10.20.10.1"
    };

  
    this.setCurrentData();
    this.scanNetworks();
  }

  scanNetworks() {
    this.networks = [
      {
        SSID: "network1",
        RSSI: -40,
        SECURED: true
      },
      {
        SSID: "network3",
        RSSI: -65,
        SECURED: true
      },
      {
        SSID: "network2",
        RSSI: -55,
        SECURED: false
      },
    
      {
        SSID: "network4",
        RSSI: -75,
        SECURED: true
      }
    ];
  }

  setCurrentData() {
    let net = this.config;
    this.current = {
      "SSID": "Controller",
      "RSSI": this.dbTolevel(net.RSSI),
      "IP": net.ip,
      "SECURED": net.wifi_enabled && net.wifi_password.length > 0 || !net.wifi_enabled && net.ap_password.length > 0,
      "MODE": net.wifi_enabled ? "Normal" : "Access Point",
      "KEY": net.wifi_enabled ? "" : net.ap_password
    };
  }

  dbTolevel(db) {
    if (db > -50)
      return 4;
    else if (db > -60)
      return 3;
    else if (db > -70)
      return 2;
    else
      return 1;
  }

}
