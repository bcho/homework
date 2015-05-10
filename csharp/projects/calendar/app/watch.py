from livereload import Server, shell

server = Server()


server.watch('./src/scss', shell('make compile-scss'))
server.watch('./src/js', shell('make compile-js'))
server.watch('./index.html')

server.serve()
