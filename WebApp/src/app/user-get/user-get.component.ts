import { Component, OnInit } from '@angular/core';
import User  from '../_models/User';  
import { UsersService } from '../_services/users.service'; 
@Component({
  selector: 'app-user-get',
  templateUrl: './user-get.component.html',
  styleUrls: ['./user-get.component.css']
})
export class UserGetComponent implements OnInit {
  users: User[];
  constructor(private us: UsersService) { }

  ngOnInit() {
  this.us  
      .getUsers()  
      .subscribe((data: User[]) => {  
        this.users = data; 
      });  
  }

  deleteUser(id) {  
    this.us.deleteUser(id).subscribe(res => {  
      this.users.splice(id, 1);  
    });  
  }  

}


 
