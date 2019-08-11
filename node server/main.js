var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var jwt = require('jsonwebtoken');

app.use(bodyParser.urlencoded({extended : true}));
var MongoClient = require('mongodb').MongoClient;
const uri = "mongodb+srv://ganesh:mmmmmmmm@cluster0-1pjm1.mongodb.net/test?retryWrites=true&w=majority";
const client = new MongoClient(uri,{useNewUrlParser:true});

function userExists(username){
    client.connect(err=>{
        const loginCredentialsCol = client.db("expressDemo").collection("loginCredentials");
        loginCredentialsCol.findOne({"username":username}).limit(1).toArray(function(err,res){
            if(err) console.log(err);
            else{
                if(res.length == 0)
                    return false;
                else 
                    return true;
            }
        });
    });
}


app.get('/',function(req,res){
    res.setHeader('Content-Type','application/json');
    res.end(JSON.stringify({message:"Hey sup"},null,3));
});

app.post('/api/v1/create',function(req,res){
    const user = req.body;
    console.log(user);
    client.connect(err=>{
        const collection = client.db("expressDemo").collection("loginCredentials");
        collection.insertOne(user,function(err,res){
                if(err)
                    console.log(`Error occured inserting ${user.username} credentials`);
                else
                    console.log(`Successfully inserted ${user.username} credentials`);
        });
    });
    res.setHeader('Content-Type','application/json');
    res.end('Successful in creating account');
});
app.post('/api/v1/login',(req,result)=>{
    const user = req.body;
    let promise = new Promise((resolve,reject)=>{
        client.connect(err=>{
            client.db('expressDemo').collection('loginCredentials').find({username:user.username}).limit(1).toArray((err,res)=>{
                if(err) {
                    reject(err);
                } else {
                    if (res.length == 0){
                        reject(`User ${user.username} Doesnt Exist`);
                    } else {
                        if(res.password == user.password){
                            resolve(`Login ${user.username} Successful`);
                        } else {
                            reject(`Wrong ${user.username} Password`);
                        }
                    }
                }
            });
        });
    });

    promise.then((message)=>{
        console.log(message);
        jwt.sign({user}, "secretkey",(err,token)=>{
            if(err) {
                result.sendStatus(403);
                console.log(err);
            } else {
                client.connect(err=>{
                    const tokenCol = client.db('expressDemo').collection('tokenCol');
                    const tokenData = {
                        username : user.username,
                        token : token
                    }
                    tokenCol.insertOne(tokenData,(err)=>{
                        if(err) {
                            result.sendStatus(403);
                            console.log(err);
                        } else {
                            console.log(token + "inserted into database");
                        }
                    });
                });
                result.end(token.toString());
            }
        });
    }).catch((message)=>{
        console.log(message);
        res.end(message);
        res.sendStatus(403);
    });
});

app.post('/api/v1/sendMessage',verifyToken,function(req,result){
    const verified = false;
    jwt.verify(req.token,'secretkey',(err,authData)=>{
        if(err) {
            res.sendStatus(403);
        } else {
            verified = true;
        }
    });
    if(verified === true)
    {const content = req.body;
    console.log(content);
    // console.log(`Sender: ${content.sender} Message:${content.message} Reciever: ${content.reciever}`);
    client.connect(err=>{
        var over = false;
        let promise = new Promise((resolve,reject)=>{
            client.db("expressDemo").collection("loginCredentials").find({"username":"kumar"}).limit(1).toArray(function(er,res){
                if(er) 
                    reject(er);
                else{
                    if(res.length == 0)
                        resolve(false);
                    else 
                        resolve(true);
                }
            });
        });

        promise.then((message) => {
            if(message === true){
                console.log("Reciever Exists");
                var timestamp = new Date().toUTCString();
                const senderData = {
                    message:content.message,
                    reciever:content.reciever,
                    timestamp:timestamp
                }
                const recieverData = {
                    message:content.message,
                    sender:content.sender,
                    timestamp:timestamp
                }
                client.db(content.sender).collection("sent").insertOne(senderData,function(err){
                    if(err)
                        console.log(`Error inserting message into -s ${content.sender}`);
                    else    
                        console.log("Message -s saved ");
                });
                client.db(content.reciever).collection("recieved").insertOne(recieverData,function(err){
                    if(err)
                        console.log(`Error inseting message into -r ${content.reciever}`);
                    else    
                        console.log("Message -r saved");
                });

                result.end('Message Sent Successfully');
            }
            else {
                console.log("Reciever doesnt exist");
                result.end('Message Sent Unsuccessful, Reciever doesnt Exist');
            }
        }).catch((message) => {
            console.log(message);
        });
    });}
});

function verifyToken(req,res,next){
    const  bearer = req.headers['authorization'];
    if(typeof bearer !== 'undefined'){
        const bearerToken = bearer.split(' ')[1];
        req.token = bearerToken;
        next();
    } else {
        res.sendStatus(403);
    }
}
app.listen(3000,function(err){
    if(err) console.log(err);
    else console.log("Listening at 3000");
})