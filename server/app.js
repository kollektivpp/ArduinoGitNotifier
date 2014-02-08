var express = require('express'),
    app = express(),
    bluetooth = require('./bluetooth');

// configure express
app.use(express.bodyParser());
app.use(function(req, res, next){
  console.log('%s %s', req.method, req.url);
  next();
});


// server
app.post('/', function(req, res) {
    var msg = 'A commit on branch ' + req.body.branch + ' in repository ' + req.body.repoName + ' happened!';

    bluetooth.writeString(msg);
    res.send(200, 'supi');
});
app.listen(8000);


// initialize bluetooth
bluetooth.connect();
