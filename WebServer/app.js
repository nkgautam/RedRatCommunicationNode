var express = require("express");
var mysql = require('mysql');
var mariadb = require('mariadb');
var app = express();
var port = 3000;

//var bodyParser = require('body-parser');
//app.use(bodyParser.json());
//app.use(bodyParser.urlencoded({ extended: true }));

//var mongoose = require("mongoose");
//mongoose.Promise = global.Promise;mongoose.connect("mongodb://localhost:27017/test");

//var nameSchema = new mongoose.Schema({
// firstName: String,
// lastNameName: String
//});

//var User = mongoose.model("User", nameSchema);

var pool = mariadb.createPool({
     host: 'localhost', 
     user:'root', 
     password: 'temp',
database: 'redratdb',
     connectionLimit: 5
});


app.post("/addname", (req, res) => {
	
	pool.getConnection()
    .then(conn => {
    
      res.send("conneted");
	conn.release();
        
    }).catch(err => {
      res.send("FAiled");
    });


 //var myData = new User(req.body);
 //myData.save()
 //.then(item => {
 //res.send("item saved to database");
 //})
 //.catch(err => {
 //res.status(400).send("unable to save to database");
 //});
});
 
app.use("/", (req, res) => {
 res.sendFile(__dirname + "/index.html");
});
 
app.listen(port, () => {
 console.log("Server listening on port " + port);
});