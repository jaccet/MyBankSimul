var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');

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

app.use('/login',loginRouter);
app.use(authenticateToken);
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

module.exports = app;
