# coding: utf-8

from livereload import Server

server = Server()

server.watch('ts/*.ts', 'tsc --out js/app.js ts/app.ts')
server.watch('./**/*.html')

server.serve()
