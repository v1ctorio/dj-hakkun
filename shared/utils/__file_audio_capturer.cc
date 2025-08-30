#include "webrtc/modules/audio_device/include/test_audio_device.h"
#include <fstream>
#include <vector>

class FileAudioCapturer : public webrtc::TestAudioDeviceModule::Capturer {
 public:
  FileAudioCapturer(const std::string& filename, int sample_rate, int channels)
      : sample_rate_(sample_rate), channels_(channels), file_(filename, std::ios::binary) {
    frame_size_ = sample_rate_ * channels_ / 100;
  }

  int SamplingFrequency() const override { return sample_rate_; }
  int NumChannels() const override { return channels_; }

  bool Capture(rtc::BufferT<int16_t>* buffer) override {
    buffer->SetSize(frame_size_);
    if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
      file_.clear();
      file_.seekg(0, std::ios::beg);
      if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
        return false; // No more data
      }
    }
    return true;
  }

 private:
  int sample_rate_;
  int channels_;
  int frame_size_;
  std::ifstream file_;
};