from livereload import Server


server = Server()

server.watch('*.html')

server.serve()
