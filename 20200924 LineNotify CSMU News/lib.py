from bs4 import BeautifulSoup
import requests
import re
import datetime

def lineNotify(token, msg):
    url = "https://notify-api.line.me/api/notify"
    headers = {
        "Authorization": "Bearer " + token, 
        "Content-Type" : "application/x-www-form-urlencoded"
    }
    
    payload = {'message': msg}
    r = requests.post(url, headers = headers, params = payload)
    return r.status_code
    
class CSMUNews():
    def MessageRegex(self, part):
        result = re.findall(r">(.+)<\/td>", str(part))
        result[0] = re.findall(r">(.+)<", result[0])[0]
        result[2] = re.findall(r"href=\"(.+)\">(.+)<", result[2])[0]
        return result


    def GenerateFormatTime(self):
        datetimeYesterday = datetime.date.today() + datetime.timedelta(days=-1)
        year = str(int(datetimeYesterday.strftime("%Y")) - 1911)
        date = year + datetimeYesterday.strftime("/%m/%d")
        return date

    def getMsg(self):
        url = "http://message.csmu.edu.tw/main2List.asp"
        baseurl = "https://message.csmu.edu.tw/"
            
        r = requests.get(url)

        if(r.status_code != 200):
            return "HTTP Error: " + str(r.status_code)

        soup = BeautifulSoup(r.content, 'html.parser')
        rr = soup.find_all("tr",class_="whitetablebg")

        date = self.GenerateFormatTime()

        msg = date+" 中山醫大校園公告 \n"
        haveNews = False

        for item in rr:
            if(date in str(item)):
                haveNews = True
                news = self.MessageRegex(item)
                msg += ("\n" + news[2][1]+"\n")
                msg += ("\n類別：" + news[0])
                msg += ("\n單位：" + news[3])
                msg += ("\n網址：" + baseurl + news[2][0])
                msg += "\n\n-------------------------------------\n"

        if(haveNews):
            return msg
        else:
            return False
