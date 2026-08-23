import yt_dlp
from yt_dlp.utils import download_range_func


def download_audio(link):
  with yt_dlp.YoutubeDL({'extract_audio': True, 'format': 'bestaudio', 'outtmpl': '%(title)s.mp3'}) as video:
    info_dict = video.extract_info(link, download = True)
    video_title = info_dict['title']
    print(video_title)
    video.download(link)    

YT_LINK = "https://www.youtube.com/watch?v=29L01vKrAzA"
download_audio(YT_LINK)