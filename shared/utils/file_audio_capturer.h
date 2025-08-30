#pragma once

#include "webrtc/modules/audio_device/include/test_audio_device.h"
#include <string>
#include <fstream>
#include <mutex>

class FileAudioCapturer : public webrtc::TestAudioDeviceModule::Capturer {
 public:
  FileAudioCapturer(const std::string& filename, int sample_rate, int channels);
  int SamplingFrequency() const override;
  int NumChannels() const override;
  bool Capture(rtc::BufferT<int16_t>* buffer) override;

  void SetFile(const std::string& filename);
 private:
  int sample_rate_;
  int channels_;
  int frame_size_;
  std::ifstream file_;
  std::mutex file_mutex_;
};