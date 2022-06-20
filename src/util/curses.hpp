#pragma once

// Curses::Print will print in the centre of the screen if it is called with (row = ROW_CENTRE) or (col = COL_CENTRE)
#define ROW_COL_CENTRE -1


#include <string>
#include <vector>
#include <ncurses.h>

namespace Curses {
  // Initialises ncurses
  void Init();

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Prints a string to the ncurses console                                                                            //
  // std::(w)string msg = The string to print                                                                          //
  // bool standout = If true, enable "A_STANDOUT", otherwise - print regular text                                      //
  // int row = The row (Y value) to print the text on. If set to ROW_COL_CENTRE - it prints the text on the centre row //
  // int col = The column (X value) to print the text on. If set to ROW_COL_CENTRE - it centres the text column-wise   //
  // WINDOW* win = The window to print the text on. Defaults to stdscr                                                 //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Print(std::string msg, bool standout = false, int row = ROW_COL_CENTRE, int col = ROW_COL_CENTRE, WINDOW* win = stdscr);
  void Print(std::wstring msg, bool standout = false, int row = ROW_COL_CENTRE, int col = ROW_COL_CENTRE, WINDOW* win = stdscr);

  /////////////////////////////////////////////////////////////////////////////////////
  // Creates a menu which allows the user to select from a list of options           //
  // std::string title = The title of the menu                                       //
  // std::Vector<std::string> options = The list of options the user can choose from //
  /////////////////////////////////////////////////////////////////////////////////////
  unsigned int SelectMenu(std::string title, std::vector<std::string> options);
}
