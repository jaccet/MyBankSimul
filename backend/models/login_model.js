const db=require('../database');
const bcrypt=require('bcryptjs');

const login = {
    loginEvent(cardnumber,callback){
        db.query("SELECT pin_no FROM card WHERE card_no=?",[cardnumber],callback);
    }
}

module.exports=login;