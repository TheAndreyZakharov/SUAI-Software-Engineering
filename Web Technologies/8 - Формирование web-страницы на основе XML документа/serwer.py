# python3 /Users/andrey/Documents/SUAI/3.2/Web/8/serwer.py
# Ctrl + C / kill 


import os, sys
from http.server import HTTPServer, CGIHTTPRequestHandler

class MyCGIHTTPRequestHandler(CGIHTTPRequestHandler):
    def translate_path(self, path):
        if path.startswith('/cgi-bin/'):
            return '/Users/andrey/Documents/SUAI/3.2/Web/8' + path
        return CGIHTTPRequestHandler.translate_path(self, path)

webdir = '/Users/andrey/Documents/SUAI/3.2/Web/8'
port = 8099

os.chdir(webdir)
srvraddr = ("", port)
srvrobj = HTTPServer(srvraddr, MyCGIHTTPRequestHandler)
srvrobj.serve_forever()
