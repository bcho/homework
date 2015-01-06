# coding: utf-8

from livereload import Server, shell

server = Server()


def compile_ts():
    output = 'js/app.js'
    files = ' '.join([
        'ts/app.ts'
    ])

    shell('tsc --out %s %s -t ES5' % (output, files))()


def compile_scss():
    output = 'css/style.css'
    files = ' '.join([
        'scss/style.scss'
    ])

    print('here')
    shell('sass --scss %s %s' % (files, output))()


server.watch('./ts/*.ts', compile_ts)
server.watch('./scss/*.scss', compile_scss)
server.watch('index.html')
server.watch('./**/*.js')
server.watch('./**/*.css')

server.serve()
