# coding: utf-8

from livereload import Server, shell

server = Server()


def compile_ts():
    output = 'js/app.js'
    files = ' '.join([
        'js/app.ts'
    ])

    shell('tsc --out %s %s -t ES5' % (output, files))()


def compile_scss():
    output = 'css/style.css'
    files = ' '.join([
        'scss/style.scss'
    ])

    shell('sass --scss %s %s' % (files, output))()


def compile_html_partials():
    output = 'js/partials/html.ts'

    shell('tss html *.html', output=output, cwd='./js/partials', shell=True)()


server.watch('./js/**/*.ts', compile_ts)
server.watch('./js/*.ts', compile_ts)
server.watch('./scss/**/*.scss', compile_scss)
server.watch('./js/partials/*.html', compile_html_partials)
server.watch('index.html')
server.watch('./**/*.css')

server.serve()
