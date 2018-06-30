import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-scheduler',
  templateUrl: './scheduler.component.html',
  styleUrls: ['./scheduler.component.css']
})
export class SchedulerComponent implements OnInit {
  sidebar: Array<any> = [
    {title: "Program 1", icon: "icon-calendar", href: "/settings/network"},
    {title: " Program 2", icon: "icon-calendar", href: "/settings/clock"},
    {title: " Program 3", icon: "icon-calendar", href: "/settings/clock"},
    {title: " Program 4", icon: "icon-calendar", href: "/settings/clock"}
  ];

  constructor() { }

  ngOnInit() {
  }

}
