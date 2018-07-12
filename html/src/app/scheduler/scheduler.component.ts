import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-scheduler',
  templateUrl: './scheduler.component.html',
  styleUrls: ['./scheduler.component.css']
})
export class SchedulerComponent implements OnInit {
  sidebar: Array<any> = [
    {title: "Program 1", icon: "icon-calendar", href: "/scheduler/1"},
    {title: " Program 2", icon: "icon-calendar", href: "/scheduler/2"},
    {title: " Program 3", icon: "icon-calendar", href: "/scheduler/3"},
    {title: " Program 4", icon: "icon-calendar", href: "/scheduler/4"}
  ];

  constructor() { }

  ngOnInit() {
  }

}
