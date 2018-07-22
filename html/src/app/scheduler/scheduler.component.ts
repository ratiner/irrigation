import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-scheduler',
  templateUrl: './scheduler.component.html',
  styleUrls: ['./scheduler.component.css']
})
export class SchedulerComponent implements OnInit {
  sidebar: Array<any> = [
    {title: "Program 1", icon: "icon-calendar", href: "/scheduler/1"}
  ];

  constructor() { }

  ngOnInit() {
      
  }

}
