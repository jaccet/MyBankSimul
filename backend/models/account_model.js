const db=require('../database.js');

const account={
    
    getAllAccounts(callback){
        return db.query('SELECT * FROM account',
        callback);
    },
    
    getOneAccount(iban,callback){
        return db.query('SELECT * FROM account WHERE IBAN_no=?',
        [iban],callback);
    },

    addAccount(newAcData,callback){
        return db.query("INSERT INTO account (IBAN_no, BIC, interest, balance, type, credit_limit) VALUES (?,?,?,?,?,?)",
        [newAcData.IBAN_no, newAcData.BIC, newAcData.interest, newAcData.balance, newAcData.type, newAcData.credit_limit],callback);
    },

    updateAccountDetails(updateAcData,iban,callback){
        if(updateAcData.credit_limit){
            return db.query('UPDATE account SET credit_limit=? WHERE IBAN_no=?',
            [updateAcData.credit_limit, iban],callback);
        }
        if(updateAcData.balance){
            return db.query('UPDATE account SET balance=? WHERE IBAN_no=?',
            [updateAcData.balance, iban],callback);
        }
        if(updateAcData.interest){
            return db.query('UPDATE account SET interest=? WHERE IBAN_no=?',
            [updateAcData.interest, iban],callback);
        }
    },

    updateAccount(fullUpdate,iban,callback){
        return db.query('UPDATE account SET BIC=?, interest=?, balance=?, type=?, credit_limit=? WHERE IBAN_no=?',
        [fullUpdate.BIC, fullUpdate.interest, fullUpdate.balance, fullUpdate.type, fullUpdate.credit_limit, iban],callback);
    },

    deleteAccount(iban,callback){
        return db.query("DELETE FROM account WHERE IBAN_no=?",
        [iban],callback);
    }
}

module.exports=account;