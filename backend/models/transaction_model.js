const db=require('../database.js');

const transaction={
    getAllTransaction(callback){
        return db.query("SELECT * FROM transaction",callback);
    },
    getOneTransaction(transact, callback){
        return db.query("SELECT * FROM transaction WHERE idtransaction=?",[transact],callback);
    },
    addTransaction(newTransaction, callback){
        return db.query("INSERT INTO transaction VALUES(?,?,?,?,?)",[newTransaction.idtransaction,newTransaction.type,newTransaction.date, newTransaction.amount,newTransaction.IBAN_no],callback);
    },
    updateTransaction(transact,updateData, callback){
        return db.query("UPDATE transaction SET idtransaction=?, type=?,date=?,amount=?,IBAN_no=? WHERE transact=?",[updateData.idtransaction, updateData.type, updateData.date, updateData.amount, updateData.IBAN_no, transact],callback);
    },
    deleteTransaction(transact, callback){
        return db.query("DELETE FROM transaction WHERE transact=?",[transact],callback);
    }
}


    module.exports=transaction;