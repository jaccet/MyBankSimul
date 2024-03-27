const express=require('express');
const router=express.Router();
const card=require('../models/card_model');

router.get('/',function(request,response){
    card.getAllCard(function(err,result){
        if(err){
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

router.get('/:card_no',function(request,response){
    card.getOneCard(request.params.card_no,function(err,result){
        if(err){
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

router.post('/',function(request,response){
    card.addCard(request.body,function(err,result){
        if(err){
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

router.put('/:card_no',function(request,response){
    card.updateCard(request.params.card_no,request.body,function(err, result){
        if(err) {
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

router.put('/singleparam/:card_no',function(request,response){
    card.updateCardParam(request.params.card_no,request.body,function(err, result){
        if(err) {
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

router.delete('/:card_no',function(request,response){
    card.deleteCard(request.params.card_no,function(err,result){
        if(err){
            response.send(err);
        } else {
            response.json(result);
        }
    });
});

module.exports=router;