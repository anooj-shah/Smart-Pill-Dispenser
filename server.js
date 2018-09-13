const express = require('express')
const bodyParser = require('body-parser')
const mongodb = require('mongodb')
const moment = require('moment')

var path = require('path');

const app = express( )
var MongoClient = require('mongodb').MongoClient 
var db

app.use(bodyParser.urlencoded({extended: true}))
app.set('view engine', 'ejs')

app.use('/res',express.static(path.join(__dirname, 'resources')));

var options = {
        server:{
            auto_reconnect: true
        }
    };


MongoClient.connect("mongodb://localhost:27017/exampleDb", options, function(err, database) {

	if(err) console.log(err)

	db = database
	const PORT = 80;
	app.listen(PORT)
	console.log("Listening on port "+PORT); 

})
app.post('/addMedicineInfo', function( req, res ) {

	  console.log('POST made')
	  //console.log(req.body)
	  req.body['datetime'] = new Date()
	  //req.body['test'] = 'Tim'
	  //req.body['patient_name'] = 'Snoop Dog'
	  console.log(req.body)
	  db.collection('medication').save(req.body, function (err, result) {
	    if (err) {
		res.end('error')
		return console.log(err)
		}
	    console.log('Saved to database')
	    res.send('Thank you for the medicine')
	    res.end()
	  })

})

app.get('/showMedicineInfo', function(req,res) {
var cursor = db.collection('medication').find().toArray(function(err,results) {
console.log(results)
})
res.send('medication updates shown in server log') 
})

app.get('/allMedicationEvents', function(req,res) {
	console.log('I got here!')
  db.collection('medication').find().toArray( function(err, result) {
    if (err) return console.log(err)
    res.render('index.ejs', {medication: result, moment: moment})
  })

})
