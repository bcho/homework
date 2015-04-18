var NwBuilder = require('node-webkit-builder');

var nw = new NwBuilder({
    files: [
        './package.json',
        './index.html',
        './app.css',
        './app.js',
        './rsa.js',
        './node_modules/jquery/**',
        './node_modules/underscore/**'
    ],
    platforms: ['win', 'osx']
});

nw.on('log', console.log);

nw.build().then(function() {
    console.log('build done');
}).catch(function(err) {
    console.error(err);
});
