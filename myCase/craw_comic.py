# -*- coding: utf8 -*-
import mylib_url
import re


def getComicInfo(message):
      try:
              msg = re.match(r".+/HTML/(.+)/\"(.+)>(.+)</a>\[(.+)\]</li>", message)
              print msg.group(1), ":" , msg.group(3) , ":" , msg.group(4)
      except:
              print message
      #print msg.group(1) , ":" , msg.group(2), ":", msg.group(3)


def getWeeklyUpdate():
        data = mylib_url.getWebData("http://comic.sfacg.com/")
        '''
        with open("./comic.txt", "r") as f:
                data = f.readlines()
        '''
                
        index = 0
        state = 0
        while index < len(data):
                #print data[index].strip()
                if "最新更新漫画" in data[index]:
                        index = index + 1
                        while "WeeklyUpdate" not in data[index]:
                                message = re.match("<li>.+</li>", data[index].strip())
                                if message:
                                        getComicInfo(message.group(0))
                                index = index + 1

                        index = len(data)
                index = index + 1


def getComicPic():
        data = mylib_url.getWebData("")
        for line in data:
                print line.strip()

if __name__ == '__main__':
        getWeeklyUpdate()
       # getComicPic()

                        
