import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { ReplaySubject, Observable } from 'rxjs';


@Injectable({
  providedIn: 'root'
})
export class SchedulerService {

  constructor(
    private http: HttpClient
  ) { }


  public getPrograms(): Observable<any> {
    return this.http.get<any>('/api/scheduler');
  }

  public getProgram(id): Observable<any> {
    return this.http.get<any>('/api/scheduler/'+ id);
  }

  public setProgram(id, prog): Observable<any> {
    return this.http.post<any>('/api/scheduler/'+ id, prog);
  }
}
