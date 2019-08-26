const express = require('express');  
const app = express();  
const userRoutes = express.Router();  
// Require Product model in our routes module  
let User = require('../models/User');  
// Defined store route  
userRoutes.route('/add').post(function (req, res) {  
  console.log('userRoutes/add');
  let user = new User(req.body);  
  user.save()  
    .then(user => {  
      res.status(200).json({'Product': 'Product has been added successfully'});  
    })  
    .catch(err => {  
    res.status(400).send("unable to save to database");  
    });  
});  
// Defined get data(index or listing) route  
userRoutes.route('/').get(function (req, res) {  
  console.log('userRoutes/index');
  User.find(function (err, products){  
    if(err){  
      console.log(err);  
    }  
    else {  
      res.json(products);  
    }  
  });  
});  
// Defined edit route  
userRoutes.route('/edit/:id').get(function (req, res) {  
  console.log('userRoutes/edit');
  let id = req.params.id;  
  User.findById(id, function (err, product){  
      res.json(product);  
  });  
});  
//  Defined update route  
userRoutes.route('/update/:id').post(function (req, res) {  
  console.log('userRoutes/update');
  User.findById(req.params.id, function(err, user) {  
    if (!user)  
      res.status(404).send("Record not found");  
    else {  
      user.UserName = req.body.UserName;  
      user.UserEmail = req.body.UserEmail;  
      user.UserPassword = req.body.UserPassword;  
 user.save().then(product => {  
          res.json('Update complete');  
      })  
      .catch(err => {  
            res.status(400).send("unable to update the database");  
      });  
    }  
  });  
});  
// Defined delete | remove | destroy route  
userRoutes.route('/delete/:id').get(function (req, res) {  
    console.log('userRoutes/delete');
    User.findByIdAndRemove({_id: req.params.id}, function(err, user){  
        if(err) res.json(err);  
        else res.json('Successfully removed');  
    });  
});  
module.exports = userRoutes; 