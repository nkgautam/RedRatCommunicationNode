import { Component, OnInit } from '@angular/core';  
import { FormGroup, FormBuilder, Validators } from '@angular/forms';  
import { ActivatedRoute, Router } from '@angular/router';  
import { UsersService } from '../_services/users.service'; 

@Component({
  selector: 'app-user-edit',
  templateUrl: './user-edit.component.html',
  styleUrls: ['./user-edit.component.css']
})
export class UserEditComponent implements OnInit {
  angForm: FormGroup;  
  user: any = {};  
  constructor(private route: ActivatedRoute, private router: Router, private us: UsersService, private fb: FormBuilder) { 
  this.createForm();
  }
  
  createForm() {  
    this.angForm = this.fb.group({  
      UserName: ['', Validators.required ],  
      UserEmail: ['', Validators.required ]  
    });  
  }  

  ngOnInit() {  
    this.route.params.subscribe(params => {  
        this.us.editUser(params['id']).subscribe(res => {  
          this.user = res;  
      });  
    });  
  }  

  updateUser(UserName, UserEmail, id) {  
    this.route.params.subscribe(params => {  
      this.us.updateUser(UserName, UserEmail, params.id);  
      this.router.navigate(['users']);  
    });  
  }  

}

