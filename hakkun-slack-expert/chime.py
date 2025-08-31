import subprocess
from typing import TypedDict
import os
from time import sleep
class HakkunChimeParams(TypedDict):
    attendee_id: str
    audio_host_url: str
    external_meeting_id: str
    external_user_id: str
    join_token: str
    log_level: str
    meeting_id: str
    signaling_urls: str

def start_proc(path,attendee_id,audio_host_url,external_meeting_id,external_user_id,join_token,log_level,meeting_id,signaling_url):
    command = [
        path,
        '--attendee_id', attendee_id,
        '--audio_host_url', audio_host_url,
        '--external_meeting_id', external_meeting_id,
        '--external_user_id', external_user_id,
        '--join_token', join_token,
        '--log_level', log_level,
        '--meeting_id', meeting_id,
        '--signaling_url', signaling_url
    ]
    print(" ".join(command))
    logfilepath = os.getenv("STDERR_HCS_FILE")
    errfile = None
    if logfilepath is not None:
        errfile = open(logfilepath,'+a')
    sleep(1)
    p = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        stdout=open("./hcsout.log",'+a'),#subprocess.PIPE,
        stderr=errfile,
        text=True,
        bufsize=0,
        shell=False
    )
    sleep(1)
    return p

def play_chime(pro: subprocess.Popen):
    filename = "/home/vic/Dev/dj-hakkun/hakkun-slack-expert/colg-ttc.pcm"
    stdin_cmd = "play {}\n".format(filename)
    print(f"Sending to stdin: ´{stdin_cmd}´")
    pro.stdin.write(stdin_cmd)
    pro.stdin.flush()

def stop_chime(pro: subprocess.Popen):
    pro.stdin.write("stop\n")
    pro.stdin.flush()
    pro.terminate()