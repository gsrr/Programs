import urllib2
import urllib
import inspect


def write_req(headers):
    with open("req_header", "w") as fw:
        for line in headers:
            fw.write(line)
            fw.write("\n")


def write_resp(headers):
    with open("resp_header", "w") as fw:
        fw.write(str(headers))
     
def write_cont(content):
    with open("cont_html", "w") as fw:
        for line in content:
            print line.strip()
            fw.write(line.strip())
            fw.write("\n")
    

def main_manually():
    '''
    # send request to ift nas.
    #
    # set session manually
    '''
    req = urllib2.Request('http://172.27.113.111/status/mainFrame.jsp')
    req.add_header('Cookie', 'JSESSIONID=7DF21CFDCC1162164EE4146DA7D676C7')
    write_req(req.headers)
    print req.headers
    r = urllib2.urlopen(req)
    write_resp(r.info())
    data = r.readlines()
    write_cont(data)


def req_create(url, headers, values):
    data = urllib.urlencode(values)
    req = urllib2.Request(url)
    for key in headers:
        req.add_header(key, headers[key])
    req.add_data(data)
    return req 

def main_post():
    url = 'http://172.27.113.111/servlet/FileCreate'
    headers = {}
    headers['Cookie'] = 'JSESSIONID=7DF21CFDCC1162164EE4146DA7D676C7'
    values = {}
    values['foldername'] = 'test_python'
    values['path'] = '/Pool-1/UserHome/test1111'
    values['type'] = '1'

    req = req_create(url, headers, values)
    r = urllib2.urlopen(req)
    data = r.readlines()
    write_cont(data)
    print r.getcode()
    print type(r.info()), dict(r.info())
    r.close()
    '''
    print vars(r)
    for item in dir(r):
        print item, type(item)
    print r.code

    functions = inspect.getmembers(r, predicate=inspect.ismethod)
    for funct in functions:
        print funct
    '''

    url = 'http://172.27.113.111/servlet/FileDelete'
    values = {}
    values['name'] = 'test'
    values['path'] = '/Pool-1/UserHome/test1111/test'
    values['type'] = '1'
    req = req_create(url, headers, values)
    r = urllib2.urlopen(req)
    r.close()
     

if __name__ == "__main__":
    #main_manually()
    main_post()

