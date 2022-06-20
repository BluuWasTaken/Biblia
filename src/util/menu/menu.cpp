#include "menu.hpp"
#include <util/curses.hpp>

int Menu::Select(std::string _title, std::vector<std::string> _options) {
  // selected option
  int s = 0;

  // previously selected option
  int prev = s;

  //
  bool rerender = false;

  Curses::Print(_title, false, 4);

  // The first option is selected by default, so print it with standout/highlighting
  Curses::Print(_options[0], true, 4 + 2);

  // Print the rest of the options
  for (int i = 1; i < _options.size(); i++) {
    Curses::Print(_options[i], false, 4 + 2 + i);
  }

  refresh();

  while (true) {
    int c = getch();

    switch (c) {
      case '\n':
      case KEY_ENTER:
        clear();
        return s;
        break;

      case KEY_UP:
        prev = s;
        s = s - 1 < 0 ? _options.size() - 1 : s - 1;
        rerender = true;
        break;

      case KEY_DOWN:
        prev = s;
        s = s + 1 > _options.size() - 1 ? 0 : s + 1;
        rerender = true;
        break;
    }

    if (rerender) {
      // first, reprint the previously selected option - but without highlighting/standout
      Curses::Print(_options[prev], false, 4 + 2 + prev);

      // then, reprint the option selected - but with highlighting/standout
      Curses::Print(_options[s], true, 4 + 2 + s);

      rerender = false;
    }
  }

  return 0;
}

int Menu::EnterInt() {
  echo();
  while (true) {
    getch();
  }
  noecho();
}
