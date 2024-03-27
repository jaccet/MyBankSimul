const express=require('express');
const router=express.Router();
const bcrypt = require('bcryptjs');
const login=require('../models/login_model');

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
                            response.send(true);
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

module.exports=router;