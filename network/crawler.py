import urllib
import re


def getAreaData(path):
        f = urllib.urlopen(path)
        lines = f.readlines()
        f.close()
        for line in lines:
                line = line.strip()
                if "areaTicker_t" in line:
                        f.close()
                        return line

def getNumData(path):
        ret = {}
        f = urllib.urlopen(path)
        lines = f.readlines()
        f.close()
        for line in lines:
                line = line.strip()
                if "tickerQuote_l" in line:
                        ret ["tickerQuote_l"] = line
                elif "tickerQuote_c" in line:
                        ret ["tickerQuote_c"] = line
        f.close()                
        return ret

web_site = "http://finviz.com/"
needFile = ['script/maps/sec/current.js', 'script/maps/sec/area.js']
realFileUrl = []
f = urllib.urlopen("http://finviz.com/map.ashx")
lines = f.readlines()
f.close()
for line in lines:
        print line
        line = line.strip()
        for js_file in needFile:
                if js_file in line:
                        urlPath = web_site + js_file
                        realFileUrl.append(urlPath)
areaData = getAreaData(realFileUrl[1])
areaObj = re.search(r'\(.+\)', areaData)
area_list = areaObj.group()[1:-1].split(",")
numData = getNumData(realFileUrl[0])
ticketObj_l = re.search(r'\(.+\)', numData['tickerQuote_l'])
ticketList_l = ticketObj_l.group()[1:-1].split(",")
print ticketList_l
ticketObj_c = re.search(r'\(.+\)', numData['tickerQuote_c'])
ticketList_c = ticketObj_c.group()[1:-1].split(",")
print ticketList_c

changePct = []
for i in range(len(ticketList_l)):
        temp = 0
        change =  float(ticketList_l[i]) - float(ticketList_c[i])
        if change != 0:
                temp = ((float(ticketList_l[i]) / change) - 1.0) * 100
        
        changePct.append(temp)

for i in range(5):
        print area_list[i] , ":" , changePct[i]

print numData                        




