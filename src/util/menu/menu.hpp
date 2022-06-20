#pragma once
#include <string>
#include <vector>
#include <ncurses.h>
#include <include/json.hpp>

using json = nlohmann::json;

namespace Menu {

  // returns the index of the option selected
  int Select(std::string _title, std::vector<std::string> _options);
  int EnterInt();

}
