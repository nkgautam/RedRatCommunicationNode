var express = require('express');
var app = express();
var bodyParser = require('body-parser');
//var mysql = require('mysql');
var mariadb = require('mariadb');
  
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
    extended: true
}));
  
  
// default route
//app.get('/', function (req, res) {
//    return res.send({ error: true, message: 'hello' })
//});

app.use("/", (req, res) => {
 res.sendFile(__dirname + "/index.html");
});

// connection configurations
//var dbConn = mysql.createConnection({
//    host: 'localhost',
//    user: 'root',
//    password: '',
//    database: 'node_js_api'
//});
  
// connect to database
//dbConn.connect(); 

var pool = mariadb.createPool({
     host: 'localhost', 
     user:'root', 
     password: 'temp',
	database: 'redratdb',
     connectionLimit: 5
}); 

app.post('/addname', (req, res) => {
	pool.getConnection()
	.then(conn => {
	    
	      res.send("conneted");
	        conn.release();
	    }).catch(err => {
	      res.send("FAiled");
  	    });
});


// Retrieve all users 
app.get('/users', function (req, res) {
console.log("/users called ");
pool.getConnection()
    .then(conn => {
      conn.query('SELECT * FROM tblUsers', function (error, results, fields) {
	console.log("/users query called ");
        if (error) throw error;
        return res.send({ error: false, data: results, message: 'users list.' });
       });
      conn.release(); //release to pool
    })
    .catch(err => {
      console.log("not connected due to error: " + err);
    });

    
});
 
 
// Retrieve user with id 
app.get('/user/:id', function (req, res) {
  
    let user_id = req.params.id;
  
    if (!user_id) {
        return res.status(400).send({ error: true, message: 'Please provide user_id' });
    }
  	
    pool.getConnection()
    .then(conn => {
      conn.query('SELECT * FROM tblUsers where id=?', user_id, function (error, results, fields) {
        if (error) throw error;
        return res.send({ error: false, data: results[0], message: 'users list.' });
      });
      conn.release(); //release to pool
    })
    .catch(err => {
      console.log("not connected due to error: " + err);
    });

    
    
  
});
 
 
// Add a new user  
app.post('/user', function (req, res) {
  
    let user = req.body.user;
  
    if (!user) {
        return res.status(400).send({ error:true, message: 'Please provide user' });
    }
	
    pool.getConnection()
    .then(conn => {
      conn.query("INSERT INTO tblUsers SET ? ", { user: user }, function (error, results, fields) {
        if (error) throw error;
        return res.send({ error: false, data: results, message: 'New user has been created successfully.' });
      });
      conn.release(); //release to pool
    })
    .catch(err => {
      console.log("not connected due to error: " + err);
    });
  
    
    
});
 
 
//  Update user with id
app.put('/user', function (req, res) {
  
    let user_id = req.body.user_id;
    let user = req.body.user;
  
    if (!user_id || !user) {
        return res.status(400).send({ error: user, message: 'Please provide user and user_id' });
    }
  
    pool.getConnection()
    .then(conn => {
      conn.query("UPDATE tblUsers SET user = ? WHERE id = ?", [user, user_id], function (error, results, fields) {
        if (error) throw error;
        return res.send({ error: false, data: results, message: 'user has been updated successfully.' });
      });
      conn.release(); //release to pool
    })
    .catch(err => {
      console.log("not connected due to error: " + err);
    });

    
    
});
 
 
//  Delete user
app.delete('/user', function (req, res) {
  
    let user_id = req.body.user_id;
  
    if (!user_id) {
        return res.status(400).send({ error: true, message: 'Please provide user_id' });
    }
     
    pool.getConnection()
    .then(conn => {
      conn.query('DELETE FROM tblUsers WHERE id = ?', [user_id], function (error, results, fields) {
        if (error) throw error;
        return res.send({ error: false, data: results, message: 'User has been updated successfully.' });
      });
      conn.release(); //release to pool
    })
    .catch(err => {
      console.log("not connected due to error: " + err);
    });
    
    
    
}); 
 
// set port
app.listen(3000, function () {
    console.log('Node app is running on port 3000');
});
 
module.exports = app;