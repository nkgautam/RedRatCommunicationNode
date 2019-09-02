import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { User } from '../_models/User';
@Injectable({
  providedIn: 'root'
})
export class UsersService {

  uri = 'http://localhost:4000/users';
  constructor(private http: HttpClient) { }
  register(user: User) {

    console.log(user);
    this.http.post(`${this.uri}/register`, user)
      .subscribe(res => console.log('Done'));
  }
  addUser(fistName, lastName, username, password) {
    const obj = {
      fistName,
      lastName,
      username,
      password
    };
    console.log(obj);
    this.http.post(`${this.uri}/add`, obj)
      .subscribe(res => console.log('Done'));
  }

  getUsers() {
    return this
      .http
      .get(`${this.uri}`);
  }

  editUser(id) {
    return this
      .http
      .get(`${this.uri}/edit/${id}`);
  }

  updateUser(fistName, lastName, username, id) {
    const obj = {
      fistName,
      lastName,
      username
    };
    this
      .http
      .post(`${this.uri}/update/${id}`, obj)
      .subscribe(res => console.log('Done'));
  }

  deleteUser(id) {
    return this
      .http
      .get(`${this.uri}/delete/${id}`);
  }
}
