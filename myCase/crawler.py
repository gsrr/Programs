import urllib
import re

web_site = "http://finviz.com/"
needFile = {'current':'script/maps/sec/current.js', 'area':'script/maps/sec/area.js'}

def getWebData(urlPath):
        f = urllib.urlopen(urlPath)
        data = f.readlines()
        f.close()
        return data


def getJsUrl(line):
        tmp_path = re.search("\".+\"",line.split()[1]).group()
        urlPath = web_site + tmp_path[1:-1]
        return urlPath


def getJsFile(data):
        jsFiles = {}
        for line in data:
                line = line.strip()
                if needFile['current'] in line:
                        jsFiles['current'] = getJsUrl(line)
                if needFile['area'] in line:
                        jsFiles['area'] = getJsUrl(line)
        return jsFiles

def getObjByKey(key, data):
        for line in data:
                line = line.strip()
                if "areaTicker_t" in line:
                        return line

def getListFromObj(obj):
        data = re.search(r'\(.+\)', obj)
        return data.group()[1:-1].split(",")


def getAreaData(path):
        data = getWebData(path)
        areaObj = getObjByKey("areaTicker_t", data)
        return getListFromObj(areaObj)

def getNumData(path):
        data = getWebData(path)
        ret = {}
        for line in data:
                line = line.strip()
                if "tickerQuote_l" in line:
                        ret ["tickerQuote_l"] = line
                elif "tickerQuote_c" in line:
                        ret ["tickerQuote_c"] = line
        return ret

def getChangePct(ticketList_l, ticketList_c):
        changePct = []
        for i in range(len(ticketList_l)):
                temp = 0
                change =  float(ticketList_l[i]) - float(ticketList_c[i])
                if change != 0:
                        temp = ((float(ticketList_l[i]) / change) - 1.0) * 100
                
                changePct.append(temp)
        return changePct

def writeResult(areaList, changePct):
        with open("arranged_data", "w") as f:
                for i in range(len(areaList)):
                        f.write(areaList[i] + "\t" + str(changePct[i]) + "\n")


if __name__ == "__main__":
        data = getWebData("http://finviz.com/map.ashx")
        print '1 - start web processing...'
        jsFiles = getJsFile(data)
        areaList = getAreaData(jsFiles['area'])
        numData = getNumData(jsFiles['current'])
        print '2 - dealing with raw data...'
        ticketList_l = getListFromObj(numData['tickerQuote_l'])
        ticketList_c = getListFromObj(numData['tickerQuote_c'])
        changePct = getChangePct(ticketList_l, ticketList_c)
        print '3 - write data to file...'
        writeResult(areaList, changePct)
        print '4 - complete...'




