# Hakkun Chime Specialist

Read license.txt. Some of the code copyright here is owned by Amazon Inc.


To learn how to compile this read setup.md


C++ CLI that plays audio files encoded in this specific format (pcm 48000 2 channels) use [`ffmpeg -i input.anything -f s16le -acodec pcm_s16le -ar 48000 -ac 2 output.pcm`] to transcode.



The program gets the following data as arguments: `attendee_id,audio_host_url,external_meeting_id, external_user_id,join_token,log_level,meeting_id,signaling_url` and immediatly connects to the aws chime room (Slack huddle). 

You can get these by using the `huddles.join` endpoint on the slack user api (see [join room.bru](../Bruno/huddle-requests/join%20room.bru)).


When it joins the Chime Room it will not play anything. Using stdin you can give it commands.

The following commands are currently implemented:
- `quit` exits the room and stops the program
- `start_test_video` starts the test video playback
- `play <path>` starts playback of the desired file, it must be encoded in the special format
- `stop` stops playback without quitting the program or exiting the room