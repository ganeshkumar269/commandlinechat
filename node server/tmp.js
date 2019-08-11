var express = require('express');
var app = express();

app.get('/',(req,res)=>{
    console.log("Connection recived");
    res.end("This is the new messag1");
});

app.listen(8008,(err)=>{
    if(err) throw err;
    else    
        console.log("Started at 8008");
});