#include "utils/file_audio_capturer.h"

FileAudioCapturer::FileAudioCapturer(const std::string& filename, int sample_rate, int channels)
    : sample_rate_(sample_rate), channels_(channels) {
  frame_size_ = sample_rate_ * channels_ / 100;
  SetFile(filename);
}

int FileAudioCapturer::SamplingFrequency() const { return sample_rate_; }
int FileAudioCapturer::NumChannels() const { return channels_; }

bool FileAudioCapturer::Capture(rtc::BufferT<int16_t>* buffer) {
  std::lock_guard<std::mutex> lock(file_mutex_);

  buffer->SetSize(frame_size_);

  if (silent_) {
    std::fill(buffer->data(),buffer->data()+frame_size_,0);
    return true;
  }

  if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
    // Loop if EOF
    file_.clear();
    file_.seekg(0, std::ios::beg);
    if (!file_.read(reinterpret_cast<char*>(buffer->data()), frame_size_ * sizeof(int16_t))) {
      std::fill(buffer->data(), buffer->data() + frame_size_, 0);
    }
  }
  return true;
}

void FileAudioCapturer::SetFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(file_mutex_);
    if (file_.is_open()) file_.close();

    if (filename.empty()) {
      silent_ = true;
      return;
    }

    file_.open(filename, std::ios::binary);
    silent_ = false;
}