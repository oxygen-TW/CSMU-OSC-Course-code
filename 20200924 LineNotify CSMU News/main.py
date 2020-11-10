from lib import CSMUNews, lineNotify

if __name__ == "__main__":
    news = CSMUNews()
    token = "YOUR_TOKEN"

    if(news.getMsg() != False):
        lineNotify(token, news.getMsg())