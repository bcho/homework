# coding: utf-8

from livereload import Server, shell

server = Server()


def compile_ts():
    shell('python build.py *.html', cwd='./ts/partials')()
    shell('tsc --out js/app.js ts/app.ts ts/partials/html.ts -t ES5')()

server.watch('ts/*.ts', compile_ts)
server.watch('./**/*.html')
server.watch('./**/*.js')

server.serve()
