from livereload import Server, shell

server = Server()


server.watch('./*.html', shell('make'))
server.watch('./*.coffee', shell('make'))

server.serve()
