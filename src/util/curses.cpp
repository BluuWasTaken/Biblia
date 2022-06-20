#include "curses.hpp"

#include <sstream>

void Curses::Init() {
  // Set locale so ncurses can print wide (unicode) characters
  setlocale(LC_ALL, "");

  // Initialise screen
  initscr();

  // Allow input
  keypad(stdscr, TRUE);

  // Don't echo keys
  noecho();

  // Hide cursor
  curs_set(0);
}

void Curses::Print(std::string msg, bool standout, int row, int col, WINDOW* win) {
  unsigned int target_row = row;
  unsigned int target_col = col;

  // TODO error check on getmaxy and getmaxx in these if statements
  if (row == ROW_COL_CENTRE)
    target_row = getmaxy(win) / 2;
  // TODO error check on getmaxy and getmaxx in these if statements
  if (col == ROW_COL_CENTRE)
    target_col = (getmaxx(win) - msg.length()) / 2;

  if (standout) {
    attron(A_STANDOUT);
    mvwprintw(win, target_row, target_col, msg.c_str());
    attroff(A_STANDOUT);
  }

  else {
    mvwprintw(win, target_row, target_col, msg.c_str());
  }
}

// std::wstring.length() includes nikkud/diacritics in the length - which results in uncentred text, so use this function to find length for wstrings
unsigned int CountWideLen(std::wstring s) {
  unsigned int len = 0;
  for (int i = 0; i < s.length(); i++) {
    wchar_t c = s[i];

    // 0x05D0 - 0x05EA are the hebrew consonants
    if ((c >= 0x05D0 && c <= 0x05EA) || c == L' ' || c == ',' || c == 0x05BE || c == 0x05C0 || c == 0x05C3) {
      len++;
    }

    // 0x0000 - 0x007F are all the latin characters
    if ((c >= 0x0000 && c <= 0x007F)) {
      len++;
    }
  }

  return len;
}

void Curses::Print(std::wstring msg, bool standout, int row, int col, WINDOW* win) {
  unsigned int target_row = row;
  unsigned int target_col = col;

  // TODO error check on getmaxy and getmaxx in these if statements
  if (row == ROW_COL_CENTRE)
    target_row = getmaxy(win) / 2;
  // TODO error check on getmaxy and getmaxx in these if statements
  if (col == ROW_COL_CENTRE)
    target_col = (getmaxx(win) - CountWideLen(msg)) / 2;

  if (standout) {
    attron(A_STANDOUT);
    mvwaddwstr(win, target_row, target_col, msg.c_str());
    attroff(A_STANDOUT);
  }

  else {
    mvwaddwstr(win, target_row, target_col, msg.c_str());
  }
}
