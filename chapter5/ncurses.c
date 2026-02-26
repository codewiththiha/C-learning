#include <ncurses.h>

int main() {
  initscr();

  printw("Hello World\n");
  printw("Press any key to exit");

  refresh();
  getch();
  endwin();
  return 0;
}
