const db=require('../database');
const bcrypt=require('bcryptjs');

const card={
    getAllCard(callback){
        return db.query("SELECT * FROM card",callback);
    },
    getOneCard(cardnumber,callback){
        return db.query("SELECT * FROM card where card_no=?",[cardnumber],callback);
    },
    addCard(newCard, callback){
        bcrypt.hash(newCard.pin_no,10,function(err,hashedPin){
            return db.query("INSERT INTO card VALUES(?,?,?,?,?,?)",[newCard.card_no,newCard.expiration_date,newCard.state,hashedPin,newCard.CVV,newCard.IBAN_no],callback);
        });
    },
    updateCard(cardnumber,updateData, callback){
        bcrypt.hash(updateData.pin_no,10,function(err,hashedPin){
            return db.query("UPDATE card SET card_no=?, expiration_date=?, state=?, pin_no=?, CVV=?, IBAN_no=? WHERE card_no=?",[updateData.card_no, updateData.expiration_date, updateData.state, hashedPin, updateData.CVV, updateData.IBAN_no,cardnumber],callback);
        });
    },
    updateCardParam(cardnumber,updateData, callback){
        if(updateData.card_no) {
            db.query("UPDATE card SET card_no=? WHERE card_no=?",[updateData.card_no,cardnumber]);
        }
        if(updateData.expiration_date) {
            return db.query("UPDATE card SET expiration_date=? WHERE card_no=?",[updateData.expiration_date,cardnumber],callback);
        }
        if(updateData.state) {
            return db.query("UPDATE card SET state=? WHERE card_no=?",[updateData.state,cardnumber],callback);
        }
        if(updateData.pin_no) {
            bcrypt.hash(updateData.pin_no,10,function(err,hashedPin){
                return db.query("UPDATE card SET pin_no=? WHERE card_no=?",[updateData.pin_no,cardnumber],callback);
            });
        }
        if(updateData.CVV) {
            return db.query("UPDATE card SET CVV=? WHERE card_no=?",[updateData.CVV,cardnumber],callback);
        }
    },
    deleteCard(cardnumber, callback){
        return db.query("DELETE FROM card WHERE card_no=?",[cardnumber],callback);
    }
}

module.exports=card;