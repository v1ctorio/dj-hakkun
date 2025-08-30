#ifndef CHIME_KEYPRESS_CONTROLLER_H_
#define CHIME_KEYPRESS_CONTROLLER_H_

#include <map>

#include "controllers/meeting_controller.h"

class KeypressController final {
 public:
  KeypressController(std::shared_ptr<MeetingController> meeting_controller);

  int Exec();

 private:
  bool OnCommand(const std::string& line);

  std::shared_ptr<MeetingController> controller_;
};

#endif  // CHIME_KEYPRESS_CONTROLLER_H_
