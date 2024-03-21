const mysql = require('mysql2');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'bankAdmin',
  password: 'putin1234',
  database: 'bankSimul'
});
module.exports = connection;