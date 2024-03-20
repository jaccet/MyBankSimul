const express=require('express');
const router=express.Router();
const transaction=require('../models/transaction_model.js');

router.get('/',function(request, response){
    student.getAllTransaction(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:usern',function(request,response){
    student.getOneTransaction(request.params.usern, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    student.addTransaction(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
            //response.send(result[0].affectedRows)
        }
    });
});

router.put('/:usern', function(request, response){
    student.updateTransaction(request.params.usern, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:usern',function(request, response){
    student.deleteTransaction(request.params.usern, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;