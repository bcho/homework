var gulp = require('gulp'),
    watch = require('gulp-watch'),
    livereload = require('gulp-livereload'),
    typescript = require('gulp-tsc');


var config = {
    dir: {
        server: './',
        html: './',
        typescript: './ts',
        javascript: './js',
    }
};

gulp.task('server', function (next) {
    var connect = require('connect'),
        serveStatic = require('serve-static'),
        server = connect();

    server.use(serveStatic(config.dir.server))
        .listen(process.env.PORT || 8080, next);
});

gulp.task('compile-typescript', function () {
    gulp.src([config.dir.typescript + '/**/*.ts'])
        .pipe(typescript({ emitError: false }))
        .pipe(gulp.dest(config.dir.javascript))
        .pipe(livereload());
});

gulp.task('html', function () {
    gulp.src([config.dir.html + '/**/*.html'])
        .pipe(livereload());
});

gulp.task('watch', ['server'], function () {
    livereload.listen();

    gulp.watch(config.dir.typescript + '/**/*.ts', ['compile-typescript']);
    gulp.watch(config.dir.html + '/**/*.html', ['html']);
});

gulp.task('default', ['compile-typescript']);
