var static_dir = process.argv[2] // Arg 2 is first non-node arg

var fs = require('fs')
var express = require('express');
var app = express();

// Make sure static dir exists
if (!fs.existsSync(static_dir))
{
  console.log('Static dir doesn\'t exist: ' + static_dir);
  process.exit();
}

var dt = require('./file_utils');

app.use(express.static(static_dir));

function getImageString() {
  var file_array = dt.GetFilesInDirectory(static_dir)
  var return_string = '<h1>Observations</h1>';

  file_array.forEach(add_to_html);
  function add_to_html(value, index, array) {
    return_string += '<a href="' + value + '">' + value + '</a><br></br>';
  }
  return return_string;
}

app.get('/', function (req, res) {
   res.send('Hello World');
})

app.get('/image', function (req, res) {
  res.send(getImageString())
})

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port

   console.log("Example app listening at http://%s:%s", host, port)
})
