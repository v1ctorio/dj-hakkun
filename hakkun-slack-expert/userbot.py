import requests
from requests_toolbelt.multipart.encoder import MultipartEncoder
from chime import HakkunChimeParams
def get_huddles_info(team_id,Cookie, XOXC):
    requests.post(
        url=f"https://edgeapi.slack.com/cache/{team_id}/huddles/info",
        headers={
            "":""
        }
)
    
def join_huddle(channel_id,Cookie,XOXC,workspace)->HakkunChimeParams:

    mp_encoder = MultipartEncoder(
        fields={
            "token": XOXC,
            "channel_id": channel_id,
            "regions": "",
            "multidevice": "true"
        }
    )
    req = requests.post(
        url=f"https://{workspace}.slack.com/api/rooms.join",
        headers={
            "Accept": "*/*",
            "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/139.0.0.0 Safari/537.36",
            "Content-Type": mp_encoder.content_type,
            "Cookie": Cookie
        },
        data=mp_encoder
    )
    j = req.json()
    if j["ok"] is False:
        raise Exception("Invalid auth")
    call = j["call"]
    free_willy = call["free_willy"]
    meeting = free_willy["meeting"]
    attendee = free_willy["attendee"]
    params: HakkunChimeParams = {
        "attendee_id": attendee["AttendeeId"],
        "audio_host_url": meeting["MediaPlacement"]["AudioHostUrl"],
        "external_meeting_id": meeting["ExternalMeetingId"],
        "external_user_id": attendee["ExternalUserId"],
        "join_token": attendee["JoinToken"],
        "log_level": "INFO",
        "meeting_id": meeting["MeetingId"],
        "signaling_urls": meeting["MediaPlacement"]["SignalingUrl"]
    }
    return params
    