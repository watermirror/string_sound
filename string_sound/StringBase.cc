#include "StringBase.h"

#include <windows.h>

const double kStringLengthOfGong = 1.0;
const double kFrequenceOfGong = 262.0;

InstruString::InstruString()
    : length_(kStringLengthOfGong),
      frequence_(kFrequenceOfGong) {
}

InstruString::InstruString(const std::string& name)
    : InstruString() {
  name_ = name;
}

InstruString::~InstruString() {
}

std::string InstruString::name() const {
  return name_;
}

void InstruString::set_name(const std::string& name) {
  name_ = name;
}

double InstruString::length() const {
  return length_;
}

bool InstruString::set_length(double length) {
  if (length <= 0.0) {
    return false;
  }
  length_ = length;
  frequence_ = kFrequenceOfGong * kStringLengthOfGong / length;
  return true;
}

double InstruString::frequence() const {
  return frequence_;
}

void InstruString::SimplePlay(int period_in_ms) const {
  Beep((unsigned int)frequence_, period_in_ms);
}

InstruString GenerateStringByFall(const InstruString& source) {
  InstruString new_string;
  new_string.set_length(source.length() * 2 / 3);
  return new_string;
}

InstruString GenerateStringByRise(const InstruString& source) {
  InstruString new_string;
  new_string.set_length(source.length() * 4 / 3);
  return new_string;
}

InstruString LevelUpString(const InstruString& source) {
  InstruString new_string;
  new_string.set_length(source.length() / 2);
  return new_string;
}

InstruString LevelDownString(const InstruString& source) {
  InstruString new_string;
  new_string.set_length(source.length() * 2);
  return new_string;
}
