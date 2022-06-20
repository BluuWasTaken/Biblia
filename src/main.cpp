#include "util/curses.hpp"
#include "util/menu/menu.hpp"

#include <include/json.hpp>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <thread>

using json = nlohmann::json;

int main() {
  
  Curses::Init();

  json bible;
  json bible_structure;

  Curses::Print("Loading Bible Data......", true);
  refresh();
  std::this_thread::sleep_for (std::chrono::seconds(1));

  std::ifstream bible_file("app/bible/hb/hebrew.json", std::ios::in);
  bible_file >> bible;
  bible_file.close();

  std::ifstream bible_structure_file("app/bible/hb/structure.json", std::ios::in);
  bible_structure_file >> bible_structure;
  bible_structure_file.close();

  clear();
  Curses::Print("Data Loaded!", true);
  refresh();

  std::this_thread::sleep_for (std::chrono::seconds(1));
  clear();

  /*
  for (auto it : bible.items()) {
    std::cout << it.key() << "\n";
  }
  */

  std::vector<std::string> testaments = {"OT", "NT"};

  int t = Menu::Select("Select Testament", {"The Old Testament", "The New Testament"});
  std::string testament = testaments[t];
  int grouping = Menu::Select("Select Grouping", bible_structure[testament]["Grouping_Names"]);

  int book_index = Menu::Select("Select Book", bible_structure[testament]["Grouping"][grouping]);
  std::string book = bible_structure[testament]["Grouping"][grouping][book_index];


  int chapter = 1;
  int verse = 1;

  while (true) {
    json verseJson = bible[book][chapter][verse];
    std::string verse = "";

    for (auto a : verseJson) {
      verse += a[0];
      Curses::Print(verse, true);
      refresh();
      getch();
      clear();
    }

    Curses::Print(verse, true, 2);
    
    refresh();
    getch();

    /*
    std::string verse = "";

    for (auto word : verseJson.items()) {
      std::string werd = word.value()[0];
      verse += werd;
    }

    Curses::Print(book + " 1:1", true, 2, ROW_COL_CENTRE);
    //Curses::Print(verse, false, 4, ROW_COL_CENTRE);
    std::cout << verse;
    getch();
    */

    refresh();

  }

  getch();
  endwin();

  return 0;
}
