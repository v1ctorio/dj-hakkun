# DJ-Hakkun
Slack bot to play audio and video in huddles.

Work's with two components
- **hakkun-chime-specialist** - CLI written in C++ that uses the AWS Chime C++ Signaling SDK to play audio and video no huddles as an userbot.
- **hakkun-slack-expert** - Python program that handles all the logic and spawns the C++ binary.

There are binary release of the C++ binary because it's a pita to build


Please read [each](./hakkun-chime-specialist/readme.md) [component](./hakkun-slack-expert/README.md)'s respective readme.