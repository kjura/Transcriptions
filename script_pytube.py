import yt_dlp
from yt_dlp.utils import download_range_func
import sys

def download_audio(link):
  with yt_dlp.YoutubeDL({'extract_audio': True, 'format': 'bestaudio', 'outtmpl': '%(title)s.mp3'}) as video:
    info_dict = video.extract_info(link, download = True)
    video_title = info_dict['title']
    print(video_title)
    video.download(link)    

if len(sys.argv) != 2:
  raise ValueError(f"script_pytube.py must take exactly one argument YT_LINK, but were provided {sys.argv[1:]}")

YT_LINK = sys.argv[1]
download_audio(YT_LINK)