const express=require('express');
const router=express.Router();
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');
const login=require('../models/login_model');

router.get('/:card_no',function(request,response){
    login.checkCard(request.params.card_no,function(err,result){
        console.log(result);
        if(err) {
            response.send(err);
        } else {
            if (result.length > 0) {
                response.send(true);
            } else {
                response.send(false);
            }
        }
    });
});

router.post('/',function(request,response){
    if(request.body.card_no && request.body.pin_no){
        const card_no = request.body.card_no;
        const pin_no = request.body.pin_no;

        login.loginEvent(card_no,function(err,result){
            if(err){
                response.json(err);
            } else {
                if(result.length > 0) {
                    bcrypt.compare(pin_no,result[0].pin_no, function(err,compareResult){
                        if (compareResult) {
                            console.log("successful");
                            const token = generateAccessToken({card_no: card_no});
                            response.send(token);
                        } else {
                            console.log("wrong password");
                            response.send(false);
                        }
                    });
                } else {
                    console.log("card not found");
                    response.send(false);
                }
            }
        });
    } else {
        console.log("missing card or pin number");
        response.send(false);
    }
});

function generateAccessToken(card_no) {
    dotenv.config();
    return jwt.sign(card_no,process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;