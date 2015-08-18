#pragma once
#include <string>

class InstruString {
 public:
  InstruString();
  InstruString(const std::string& name);
  virtual ~InstruString();

  std::string name() const;
  void set_name(const std::string& name);

  double length() const;
  bool set_length(double length);

  double frequence() const;

  void SimplePlay(int period_in_ms = 500) const;

 private:
  std::string name_;
  double length_;
  double frequence_;
};

InstruString GenerateStringByFall(const InstruString& source);
InstruString GenerateStringByRise(const InstruString& source);
InstruString LevelUpString(const InstruString& source);
InstruString LevelDownString(const InstruString& source);
