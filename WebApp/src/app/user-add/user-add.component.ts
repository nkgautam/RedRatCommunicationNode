import { Component, OnInit } from '@angular/core';
import { FormGroup,  FormBuilder,  Validators } from '@angular/forms';  
import { UsersService } from '../_services/users.service';  

@Component({
  selector: 'app-user-add',
  templateUrl: './user-add.component.html',
  styleUrls: ['./user-add.component.css']
})
export class UserAddComponent implements OnInit {
  angForm: FormGroup;  
  constructor(private fb: FormBuilder, private us: UsersService) { 
  this.createForm();  
  }
	
  createForm() {  
    this.angForm = this.fb.group({  
      UserName: ['', Validators.required ],  
      UserEmail: ['', Validators.required ],  
      UserPassword: ['', Validators.required ]  
    });  
  }  
  
   addProduct(UserName, UserEmail, UserPassword) {  
    this.us.addUser(UserName, UserEmail, UserPassword);  
  }  

  ngOnInit() {
  }

}
