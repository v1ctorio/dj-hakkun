
attendee_id=$(echo "$response" | jq -r '.JoinInfo.Attendee.Attendee.AttendeeId')
audio_host_url=$(echo "$response" | jq -r '.JoinInfo.Meeting.Meeting.MediaPlacement.AudioHostUrl')
external_meeting_id=$(echo "$response" | jq -r '.JoinInfo.Meeting.Meeting.ExternalMeetingId')
external_user_id=$(echo "$response" | jq -r '.JoinInfo.Attendee.Attendee.ExternalUserId')
join_token=$(echo "$response" | jq -r '.JoinInfo.Attendee.Attendee.JoinToken')
meeting_id=$(echo "$response" | jq -r '.JoinInfo.Meeting.Meeting.MeetingId')
signaling_url=$(echo "$response" | jq -r '.JoinInfo.Meeting.Meeting.MediaPlacement.SignalingUrl')

my_cli --attendee_id "$attendee_id" \
             --audio_host_url "$audio_host_url" \
             --external_meeting_id "$external_meeting_id" \
             --external_user_id "$external_user_id" \
             --join_token "$join_token" \
             --log_level "$LOG_LEVEL" \
             --meeting_id "$meeting_id" \
             --signaling_url "$signaling_url"