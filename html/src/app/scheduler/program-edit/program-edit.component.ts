import { Component, OnInit } from '@angular/core';
import { SchedulerService } from '../scheduler.service';

@Component({
  selector: 'app-program-edit',
  templateUrl: './program-edit.component.html',
  styleUrls: ['./program-edit.component.css']
})
export class ProgramEditComponent implements OnInit {

  prog: any;
  constructor(
    private schService: SchedulerService
  ) { }

  ngOnInit() {
    this.schService.getProgram("0").subscribe(prog => {
      this.prog = prog;
    });
  }

  save() {
    this.schService.setProgram("0", this.prog).subscribe(x => {
    });
  }

}
