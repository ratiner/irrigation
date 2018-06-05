import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'shared-side-menu',
  templateUrl: './side-menu.component.html',
  styleUrls: ['./side-menu.component.css']
})
export class SideMenuComponent implements OnInit {

  @Input("Links") links: Array<any>;
  
  constructor() { }

  ngOnInit() {
  }

}
