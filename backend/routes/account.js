var express = require('express');
var router = express.Router();
const account=require('../models/account_model.js');
  
router.get('/',function(request, response){
    account.getAllAccounts(function(err,result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:iban',function(request, response){
    account.getOneAccount(request.params.iban, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.get('/:card_no',function(request,response){
    account.getAccountInfoByCard(request.params.card_no,function(err,result){
        if(err){
            response.send(err);
        } else {
            request.json(result);
        }
    });
});

router.post('/',function(request, response){
    account.addAccount(request.body, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/upAccount/:iban',function(request, response){
    account.updateAccountDetails(request.body, request.params.iban, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/fullUpdate/:iban',function(request, response){
    account.updateAccount(request.body, request.params.iban, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.delete('/:iban',function(request,response){
    account.deleteAccount(request.params.iban, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});


module.exports=router;