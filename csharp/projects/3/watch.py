from livereload import Server


server = Server()

server.watch('index.html')

server.serve()
