var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');
const cron = require('node-cron');
const moment = require('moment');
const fs = require('fs');
const spawn = require('child_process').spawn;
const dotenv = require('dotenv');


var usersRouter = require('./routes/users');
var cardRouter = require('./routes/card');
var transactionRouter = require('./routes/transaction');
var accountRouter = require('./routes/account');
var loginRouter = require('./routes/login');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

cron.schedule('10 * * * *', () => {
    // Use moment.js or any other way to dynamically generate file name
      const fileName = `${process.env.DB_NAME}_${moment().format('YYYY_MM_DD')}.sql`;
      const wstream = fs.createWriteStream(`./${fileName}`);
      console.log('---------------------');
      console.log('Running Database Backup Cron Job');
      const mysqldump = spawn('mysqldump', [ '-u', process.env.DB_USER, `-p`,process.env.DB_PASSWORD, process.env.DB_NAME ], {shell: true});
    
      mysqldump
        .stdout
        .pipe(wstream)
        .on('finish', () => {
          console.log('DB Backup Completed!');
        })
        .on('error', (err) => {
          console.log(err);
        });
    });

app.use('/login',loginRouter);
//app.use(authenticateToken);
app.use('/users', usersRouter);
app.use('/card',cardRouter);
app.use('/transaction', transactionRouter);
app.use('/account', accountRouter);

function authenticateToken(req,res,next){
    const authHeader = req.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    console.log("token = "+token);
    if (token == null) return res.sendStatus(401);

    jwt.verify(token,process.env.MY_TOKEN, function(err,card){
        if (err) return res.sendStatus(403);

        req.card = card;

        next();
    });
}

app.listen();
module.exports = app;
