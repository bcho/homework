# coding: utf-8

from livereload import Server, shell

server = Server()


def compile_ts():
    shell('python build.py', cwd='./ts/partials')()

    output = 'js/app.js'
    files = ' '.join([
        'ts/app.ts',
        'ts/partials/html.ts',
        'ts/partials/sqlQuery.ts'
    ])

    shell('tsc --out %s %s -t ES5' % (output, files))()

server.watch('ts/*.ts', compile_ts)
server.watch('ts/partials/*.sql', compile_ts)
server.watch('ts/partials/*.html', compile_ts)
server.watch('./**/*.html')
server.watch('./**/*.js')

server.serve()
