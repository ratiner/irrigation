import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Routes, RouterModule } from '@angular/router';

import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { SettingsComponent } from './settings/settings.component';
import { SchedulerComponent } from './scheduler/scheduler.component';
import { ErrorComponent } from './error/error.component';
import { LoginComponent } from './login/login.component';
import { SideMenuComponent } from './shared/side-menu/side-menu.component';
import { NetworkComponent } from './settings/network/network.component';
import { ClockComponent } from './settings/clock/clock.component';
import { HttpClientModule } from '@angular/common/http';
import { IoComponent } from './settings/io/io.component';
import { ProgramEditComponent } from './scheduler/program-edit/program-edit.component';


const routes: Routes = [
  { path: '', redirectTo: '/home', pathMatch: 'full' },
  { path: 'home', component: HomeComponent },
  { path: 'error/:code', component: ErrorComponent },
  { path: 'login', component: LoginComponent },
  {
    path: 'settings', component: SettingsComponent, children: [
      { path: 'network', component: NetworkComponent },
      { path: 'clock', component: ClockComponent },
      { path: 'io', component: IoComponent }
    ]
  },
  {
    path: 'scheduler', component: SchedulerComponent, children: [
      { path: ':id', component: ProgramEditComponent },
    ]
  },
  { path: '**', redirectTo: '/error/not-found' }
];

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    SettingsComponent,
    SchedulerComponent,
    ErrorComponent,
    LoginComponent,
    SideMenuComponent,
    NetworkComponent,
    ClockComponent,
    IoComponent,
    ProgramEditComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    RouterModule.forRoot(routes),
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }