# coding: utf-8

from livereload import Server, shell

server = Server()


def compile_ts():
    output = 'js/app.js'
    files = ' '.join([
        'ts/app.ts'
    ])

    shell('tsc --out %s %s -t ES5' % (output, files))()


server.watch('ts/*.ts', compile_ts)
server.watch('./**/*.html')
server.watch('./**/*.js')

server.serve()
