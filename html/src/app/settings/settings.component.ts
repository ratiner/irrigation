import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css']
})
export class SettingsComponent implements OnInit {

  sidebar: Array<any> = [
      {title: "Network", icon: "icon-cog", href: "/settings/network"},
      {title: "Date and Time", icon: "icon-calendar", href: "/settings/clock"}
  ];
  constructor() { }

  ngOnInit() {
  }

}
