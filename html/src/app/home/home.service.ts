import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { ReplaySubject, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class HomeService {

  constructor(
    private http: HttpClient
  ) { }


  public getStatus(): Observable<any> {
    return this.http.get<any>('/api/status');
  }

  public forceStart(): Observable<any> {
    return this.http.get<any>('/api/1/on');
  }

  public forceStop(): Observable<any> {
    return this.http.get<any>('/api/1/off');
  }
}
