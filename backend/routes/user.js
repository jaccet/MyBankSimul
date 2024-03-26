var express = require('express');
var router = express.Router();
const user=require('../models/user_model.js');

router.get('/', function(request, response) {
  user.getAllUsers(function(err,result){
    if(err){
        console.log(err);
        response.json(err.errno);
    }
    else{
        console.log(result);
        response.json(result);
    }
  });
});

router.get('/:username', function(request,response){
    user.GetOneUser(request.params.username, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.post('/',function(request,response){
    user.addUser(request.body, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            response.json(result);
        }
    });
});

router.put('/:username', function(request,response){
    user.updateUser(request.body, request.params.username, function(err, result){
        if(err){
            console.log(err);
            response.json(err.errno);
        }
        else{
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:username',function(request,response){
    user.deleteUser(request.params.username, function(err,result){
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
