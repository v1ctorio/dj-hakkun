#include "utils/file_audio_capturer.h"

FileAudioCapturer::FileAudioCapturer(const std::string& filename, int sample_rate, int channels)
    : sample_rate_(sample_rate), channels_(channels), file_(filename, std::ios::binary) {
  frame_size_ = sample_rate_ * channels_ / 100;
}

int FileAudioCapturer::SamplingFrequency() const { return sample_rate_; }
int FileAudioCapturer::NumChannels() const { return channels_; }

bool FileAudioCapturer::Capture(rtc::BufferT<int16_t>* buffer) {
  buffer->SetSize(frame_size_);
  if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
    // Loop or stop if EOF
    file_.clear();
    file_.seekg(0, std::ios::beg);
    if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
      return false;
    }
  }
  return true;
}