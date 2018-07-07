var fs = require('fs');
fs.rename('dist/irrigation-gui/index.html', 'dist/irrigation-gui/index.htm', function(err) {
    if ( err ) console.log('ERROR: ' + err);
});

fs.rename('dist/irrigation-gui/polyfills.js', 'dist/irrigation-gui/poly.js', function(err) {
    if ( err ) console.log('ERROR: ' + err);
});


fs.readFile("dist/irrigation-gui/index.htm", 'utf8', function (err,data) {
  if (err) {
    return console.log(err);
  }
  var result = data.replace("polyfills.js", 'poly.js');

  fs.writeFile("dist/irrigation-gui/index.htm", result, 'utf8', function (err) {
     if (err) return console.log(err);
  });
});