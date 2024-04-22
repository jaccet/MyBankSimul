const db=require('../database.js');

const transaction={
    getAllTransaction(callback){
        return db.query("SELECT * FROM transaction",callback);
    },
    getAllTransactionByIbanJoinCard(card_no,callback){
        return db.query("select transaction.idtransaction,transaction.type,transaction.date,transaction.amount from card c join account a on c.IBAN_no=a.IBAN_no join transaction on a.IBAN_no=transaction.IBAN_no where card_no=? order by idtransaction desc limit 5",[card_no],callback);
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
    },
    withdrawal(iban_no,withdrawalInfo,callback){
        return db.query("CALL withdrawal(?,?)",[iban_no,withdrawalInfo.amount],callback);
    }
}


    module.exports=transaction;