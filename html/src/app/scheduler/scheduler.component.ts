import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-scheduler',
  templateUrl: './scheduler.component.html',
  styleUrls: ['./scheduler.component.css']
})
export class SchedulerComponent implements OnInit {
  sidebar: Array<any> = [
    {title: "Network2", icon: "icon-cog", href: "/settings/network"},
    {title: " Tim2e", icon: "icon-calendar", href: "/settings/clock"}
  ];

  constructor() { }

  ngOnInit() {
  }

}
