import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css']
})
export class SettingsComponent implements OnInit {

  sidebar: Array<any> = [
      {title: "Network", icon: "icon-signal", href: "/settings/network"},
      {title: "I/O Setup", icon: "icon-plug", href: "/settings/io"},
      {title: "Date and Time", icon: "icon-clock", href: "/settings/clock"}
  ];
  constructor() { }

  ngOnInit() {
  }

}
