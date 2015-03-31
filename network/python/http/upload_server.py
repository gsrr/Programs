# Written by Vamei
# A messy HTTP server based on TCP socket 

import socket

# Address
HOST = ''
PORT = 8000

text_content = '''
HTTP/1.x 200 OK  
Content-Type: text/html

<html>
<head>
<meta http-equiv="Content-Type" content="text/html;charset=big5">
<meta http-equiv="PRAGMA" content="NO-CACHE">
<title>FileUpload</title>
</head>
<body>
<form name="UploadPage" method="post" enctype="multipart/form-data" action="uploadfile.php">
Choose File To Upload: <input type="file" name="File1"><br>
<input type="submit" value="Upload...">
</form>
</body>
</html> 
'''

f = open('test.jpg','rb')
pic_content = '''
HTTP/1.x 200 OK  
Content-Type: image/jpg

'''
pic_content = pic_content + f.read()

# Configure socket
s    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))

# Serve forever
while True:
    s.listen(3)
    conn, addr = s.accept()                    
    request    = conn.recv(1024)         # 1024 is the receiving buffer size
    method     = request.split(' ')[0]
    src        = request.split(' ')[1]

    print 'Connected by', addr
    print 'Request is:', request

    # if GET method request
    if method == 'GET':
        # if ULR is /test.jpg
        if src == '/test.jpg':
            content = pic_content
        else: content = text_content
        # send message
        conn.sendall(content)
    # if POST method request
    if method == 'POST':
        form = request.split('\r\n')
        idx = form.index('')             # Find the empty line
        entry = form[idx:]               # Main content of the request

        value = entry[-1].split('=')[-1]
        conn.sendall(text_content + '\n <p>' + value + '</p>')
        ######
        # More operations, such as put the form into database
        # ...
        ######
    # close connection
    conn.close()
