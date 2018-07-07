import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { ReplaySubject, Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class SettingsService {

  constructor(
    private http: HttpClient
  ) { }

  private _network: ReplaySubject<any>;

  public getNetwork(): Observable<any> {
    if (!this._network) {
      this._network = new ReplaySubject<any>(1);

      this.http.get<any>('/api/settings/network').subscribe(resp => {
        this._network.next(resp as any);
      }, error => this._network.error(error));
    }
    return this._network.asObservable();
  }

  public setNetwork(networkConfig): Observable<any> {
      return this.http.post<any>('/api/settings/network', networkConfig);
  }

  public scanNetworks(): Observable<any> {
      return this.http.get<any>('/api/settings/network/scan');
  }

  public getClock(): Observable<any> {
    return this.http.get<any>('/api/settings/clock');
  }

  public setClock(dateTime: Date): Observable<any> {
    return this.http.post<any>('/api/settings/clock', dateTime.toISOString() + dateTime.getDay());
  }

}
