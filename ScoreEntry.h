#pragma once
#include <string>

struct ScoreEntry {
    std::string name;
    int score;

   
    ScoreEntry(std::string n, int s) : name(std::move(n)), score(s) {}

   
    ScoreEntry() : name("---"), score(0) {}
};
