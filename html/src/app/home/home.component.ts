import { Component, OnInit } from '@angular/core';
import { HomeService } from './home.service';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {

  active: boolean
  valve: boolean

  constructor(
    private homeService: HomeService
  ) { }

  ngOnInit() {
    this.homeService.getStatus().subscribe(x=> {
      this.active = x.active == "1";
      this.valve = this.active;
    });
  }

  forceStart() {
    this.homeService.forceStart().subscribe(x=>{
      
    });
    this.valve = true;
  }

  forceStop() {
    this.homeService.forceStop().subscribe(x=>{
    });
    this.valve = false;
  }

}
