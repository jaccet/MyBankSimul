const db=require('../database');
const bcrypt=require('bcryptjs');

const login = {
    checkCard(cardnumber,callback){
        db.query("SELECT card_no FROM card WHERE card_no=?",[cardnumber],callback);
    },
    loginEvent(cardnumber,callback){
        db.query("SELECT pin_no FROM card WHERE card_no=?",[cardnumber],callback);
    }
}

module.exports=login;