import os
from dotenv import load_dotenv

from slack_bolt import App
from urllib.parse import urlparse
from slack_bolt.adapter.socket_mode import SocketModeHandler
import chime
import userbot
proc = None

load_dotenv()

hakkun_chime_specialist_path = os.getenv("HAKKUN_CHIME_SPECIALIST_PATH") or "./hakkun-chime-specialist"
USERBOT_COOKIE=os.getenv("USERBOT_COOKIE")
USERBOT_XOXC=os.getenv("USERBOT_XOXC")
WORKSPACE=os.getenv("WORKSPACE") or "hackclub"

app = App(token=os.getenv("SLACK_BOT_TOKEN"))

@app.command("/djoin")
def join(ack, respond, command):
    global proc
    ack()
    if proc is not None:
        respond("Already in another call, use /dleave first")
        return
    target_c_id = command["channel_id"]
    print(command)
    join_data = userbot.join_huddle(channel_id=target_c_id,Cookie=USERBOT_COOKIE,workspace=WORKSPACE,XOXC=USERBOT_XOXC)

    proc = chime.start_proc(
        path=hakkun_chime_specialist_path,
        attendee_id=join_data.get("attendee_id"),
        audio_host_url=join_data.get("audio_host_url"),
        external_meeting_id=join_data.get("external_meeting_id"),
        join_token=join_data.get("join_token"),
        external_user_id=join_data.get("external_user_id"),
        meeting_id=join_data.get("meeting_id"),
        signaling_url=join_data.get("signaling_urls"),
        log_level="INFO",
        )
    print(f"process alive: {proc.poll()}")
    if join_data["attendee_id"] is not None:
        respond("Successfully joined the channel huddle")
    
@app.command("/djleave")
def join(ack, respond, command):
    global proc
    ack()
    if proc is None:
        respond("Can't leave since I'm not even in a call yet")
        return
    chime.stop_chime(proc)
    proc = None
    respond("Succesfully stopped and left the channel")

@app.command("/djplay")
def play(ack, respond, command):
    global proc
    ack()
    url = urlparse(command["text"])
    if url is None:
        respond("Invalid url provided")
        return
    if url.hostname != "youtube.com":
        respond("Url must be from youtube")
        return

    if proc is None:
        respond("Can't play right now since I'm not connected to any channel. Use /djoin first.")
        return
    
    file_path = ""
    chime.play_chime(proc, )
    respond("Started playing audio")
    
def main():
    SocketModeHandler(app, os.getenv("SLACK_APP_TOKEN")).start()
    print("Hello from hakkun-slack-expert!")


if __name__ == "__main__":
    main()
