const db=require('../database.js');

const transaction={
    getAllTransaction(callback){
        return db.query("SELECT * FROM transaction",callback);
    },
    getOneTransaction(idtransaction, callback){
        return db.query("SELECT * FROM transaction WHERE idtransaction=?",[idtransaction],callback);
    },
    addTransaction(newTransaction, iban_n, callback){
        return db.query("INSERT INTO transaction (idtransaction, type, date, amount, IBAN_no) VALUES(?,?,?,?,?)",[newTransaction.idtransaction,newTransaction.type,newTransaction.date, newTransaction.amount, iban_n],callback);
    },
    updateTransaction(updateData, callback){
        return db.query("UPDATE transaction SET type=?, date=?, amount=? WHERE idtransaction=?",[updateData.type, updateData.date, updateData.amount, updateData.idtransaction],callback);
    },
    deleteTransaction(idtransaction, callback){
        return db.query("DELETE FROM transaction WHERE idtransaction=?",[idtransaction],callback);
    }
}


    module.exports=transaction;