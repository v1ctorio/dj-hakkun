// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.

#include "keypress_controller.h"

#include <iostream>

KeypressController::KeypressController(std::shared_ptr<MeetingController> controller) : controller_(std::move(controller)) {}

int KeypressController::Exec() {
  std::cout << "[[HAKKUN]] STARTED" << std::endl;

  std::string line;
  while (std::getline(std::cin,line)) {
    if (line.empty()) continue;
    bool quit = OnCommand(line);
    if (quit) break;
  };

  return 0;
}

bool KeypressController::OnCommand(const std::string& line){
  std::istringstream stream(line);
  std::string str;
  std::vector<std::string> args;
  std::string command;

  while (stream >> str) {
    args.push_back(str);
  }
  command = args[0];

  if (!controller_) return false;

  if (command == "quit") {
    controller_->Stop();
    std::cout << "[HAKKUN] quitting" << std::endl;
    return true;
  }

  if (command == "start_test_video"){
    controller_->StartLocalVideo();
    std::cout << "[HAKKUN] startingvideo" << std::endl;
    return false;
  }

  if (command == "play") {
    if (args.size() > 1) {

      controller_->PlayAudioFile(args[1]);
      std::cout << "[HAKKUN] playing" << std::endl;
    } else {
      std::cout << "[HAKKUN] missing file argument" << std::endl;
    }
    return false;
  }

  if (command == "stop") {
    controller_->PlayAudioFile("");
    std::cout << "[HAKKUN] stopped" << std::endl;
    return false;
  }
  return false;
}

