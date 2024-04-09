const express=require('express');
const router=express.Router();
const transaction=require('../models/transaction_model.js');

router.get('/',function(request, response){
    transaction.getAllTransaction(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:card_no',function(request, response){
    transaction.getAllTransactionByIbanJoinCard(request.params.card_no,function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:idtransaction',function(request,response){
    transaction.getOneTransaction(request.params.idtransaction, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});

router.post('/:iban_n',function(request, response){
    transaction.addTransaction(request.body, request.params.iban_n, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/', function(request, response){
    transaction.updateTransaction(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:idtransaction',function(request, response){
    transaction.deleteTransaction(request.params.idtransaction, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;