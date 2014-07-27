import urllib

def getWebData(urlPath):
        f = urllib.urlopen(urlPath)
        data = f.readlines()
        f.close()
        return data
