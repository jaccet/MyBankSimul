var mysql = require('mysql2');
var connection = mysql.createConnection({
  host: "localhost",
  user: "bankAdmin",
  password: "putin1234",
  database: 'banksimul'
});

module.exports = connection;