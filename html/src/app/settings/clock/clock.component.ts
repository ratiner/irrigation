import { Component, OnInit } from '@angular/core';
import { SettingsService } from '../settings.service';

@Component({
  selector: 'app-clock',
  templateUrl: './clock.component.html',
  styleUrls: ['./clock.component.css']
})
export class ClockComponent implements OnInit {

  current: Date;
  currentDate: String;
  currentTime: String;

  constructor(
    private settingsService: SettingsService
  ) { }

  ngOnInit() {
    this.settingsService.getClock().subscribe((result)=>
    {
      this.current = new Date(result.stamp);

      setInterval(()=> {
        this.current = new Date(this.getStamp().getTime() + 1000);
        this.showTime();
      }, 1000);
      this.showTime();
    });
  }
  
  showTime() {
    let str = this.current.toISOString();
    this.currentDate = str.split('T')[0];
    this.currentTime = str.split('T')[1].substr(0, 8);
  }

  getStamp() {
    return new Date(this.currentDate + "T" + this.currentTime + "Z");
  }

  save() {
    this.settingsService.setClock(this.getStamp()).subscribe((result) => {
      
    });
  }
}
