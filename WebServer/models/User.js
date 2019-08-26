const mongoose = require('mongoose');  
const Schema = mongoose.Schema;  
// Define collection and schema for User  
let User = new Schema({  
  UserName: {  
    type: String  
  },  
  UserEmail: {  
    type: String  
  },  
  UserPassword: {  
    type: String  
  }  
},{  
    collection: 'User'  
});  
module.exports = mongoose.model('User', User);  