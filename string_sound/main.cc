#include <stdio.h>
#include <vector>
#include <windows.h>

#include "StringBase.h"

void TestSingleInstruString(const InstruString& string);
void GenerateStrings(std::vector<InstruString>& strings, int count);
void AdjustStrings(std::vector<InstruString>& strings);
void SortStrings(std::vector<InstruString>& strings);
void PickStrings(const std::vector<InstruString>& inputs,
                 std::vector<InstruString>& outputs);
void TestStrings(const std::vector<InstruString>& strings);
void PlayMusicWithStrings(const std::string& music,
                          const std::vector<InstruString>& strings,
                          int delay_base = 500);

int main() {
  std::vector<InstruString> strings;
  std::vector<InstruString> strings_to_play;
  GenerateStrings(strings, 12);
  AdjustStrings(strings);
  SortStrings(strings);
  PickStrings(strings, strings_to_play);

  printf("Test all 12 strings.\n================================\n");
  TestStrings(strings);
  printf("Test 7 common strings.\n================================\n");
  TestStrings(strings_to_play);

  std::string track_1 = "04 51 31 32 41 21 22 11 21 31 41 51 51 52 51 31 32 "
      "41 21 22 11 31 51 51 33 01 21 21 21 21 21 31 42 31 31 31 31 31 41 52 "
      "51 31 32 41 21 22 11 31 51 51 13 01 ";
  std::string track_2 = "04 63 51 32 22 15 01 62-33 21 12 62-55-03 53-61-52-"
      "62-13 21 32 52 63 51 31 21 12 25 03 63 51 32 22 15 01 62-33 21 12 62-"
      "55-03 53-61-52-62-13 21 32 52 63 51 31 21 12 15 03 ";
  std::string track_3 = "04 62-11 31 22 11 71-62-12 72-51-01 62-11 31 22 11 "
      "21 31 31 31 21 33 01 21 31 62 51 61 52 21 11 21 61 51 31 22 11 21 52 "
      "51-61-72-61-51-61-11 71-51-63-01 ";
  std::string track_4 = "04 53-11 13 31 63 31 53 51 53 61 53 31 43 31 23 21 "
      "63-21 23 41 73 71 63 51 43 41 33 21 63-61-73-11 28 24 ";
  printf("Now play the track 001.\n");
  PlayMusicWithStrings(track_1, strings_to_play, 250);
  printf("Now play the track 002.\n");
  PlayMusicWithStrings(track_2, strings_to_play, 250);
  printf("Now play the track 003.\n");
  PlayMusicWithStrings(track_3, strings_to_play, 250);
  printf("Now play the track 004.\n");
  PlayMusicWithStrings(track_4, strings_to_play, 200);
  printf("Thank you!\n");

  return 0;
}

void TestSingleInstruString(const InstruString& string) {
  printf("%16s %16.2lf units length %16.2lf HZ\n",
         string.name().c_str(),
         string.length(),
         string.frequence());
  string.SimplePlay();
}

void GenerateStrings(std::vector<InstruString>& strings, int count) {
  const char* names[] = {
      "Gong %3d", "Zhi %3d", "Shang %3d", "Yu %3d", "jue %3d"};
  const int names_count = 5;
  const char no_name[] = "(empty) %3d";
  strings.clear();
  for (size_t i = 0; i < (unsigned int)count; i++) {
    InstruString string;
    if (i > 0 && i % 2) {
      string = GenerateStringByFall(strings[i - 1]);
    } else if (i > 0 && !(i % 2)) {
      string = GenerateStringByRise(strings[i - 1]);
    }
    char string_name[32] = {0};
    if (i < names_count) {
      sprintf_s(string_name, 32, names[i], i);
    } else {
      sprintf_s(string_name, 32, no_name, i);
    }
    string.set_name(string_name);
    strings.push_back(string);
  }
}

void AdjustStrings(std::vector<InstruString>& strings) {
  for (size_t i = 0; i < strings.size(); i++) {
    InstruString& string = strings[i];
    while (string.length() < 0.48) {
      string.set_length(string.length() * 2.0);
      string.set_name(std::string("*") + string.name());
    }
  }
}

void SortStrings(std::vector<InstruString>& strings) {
  for (size_t i = 1; i < strings.size(); i++) {
    for (size_t k = 0; k < strings.size() - i; k++) {
      if (strings[k].frequence() > strings[k + 1].frequence()) {
        InstruString temp = strings[k];
        strings[k] = strings[k + 1];
        strings[k + 1] = temp;
      }
    }
  }
}

void PickStrings(const std::vector<InstruString>& inputs,
                 std::vector<InstruString>& outputs) {
  outputs.clear();
  for (size_t i = 0; i < inputs.size(); i++) {
    if (i == 0 || i == 2 || i == 4 || i == 5 ||
        i == 7 || i == 9 || i == 11) {
      outputs.push_back(inputs[i]);
    }
  }
}

void TestStrings(const std::vector<InstruString>& strings) {
  for (size_t i = 0; i < strings.size(); i++) {
    TestSingleInstruString(strings[i]);
  }
  printf("\n");
}

void PlayMusicWithStrings(const std::string& music,
                          const std::vector<InstruString>& strings,
                          int delay_base) {
  for (size_t i = 0; i < music.length() / 3; i++) {
    int string_idx = music[i * 3] - '1';
    int delay = music[i * 3 + 1] - '0';
    char level = music[i * 3 + 2];
    if (string_idx < 0) {
      string_idx = -1;
    }
    if (level == '+')
      printf("H");
    else if (level == '-')
      printf("L");
    printf("%d ", string_idx + 1);
    for (int k = 1; k < delay; k++) {
      printf("- ");
    }
    if (string_idx < 0 || string_idx >= (int)strings.size()) {
      Sleep(delay_base * delay);
    } else {
      InstruString to_play = strings[string_idx];
      if (level == '-') {
        to_play = LevelDownString(to_play);
      } else if (level == '+') {
        to_play = LevelUpString(to_play);
      }
      to_play.SimplePlay(delay_base * delay);
    }
  }
  printf("\n");
}
