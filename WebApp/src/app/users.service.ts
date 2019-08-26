import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';  

@Injectable({
  providedIn: 'root'
})
export class UsersService {

  uri = 'http://localhost:4000/users';  
  constructor(private http: HttpClient) { }  
  addUser(UserName, UserEmail, UserPassword) {  
    const obj = {  
      UserName,  
      UserEmail,  
      UserPassword  
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
  
  updateUser(UserName, UserEmail, id) {  
    const obj = {  
      UserName,  
      UserEmail 
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
