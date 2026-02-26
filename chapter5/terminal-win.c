#include <ncurses.h>

int main() {
  initscr();
  // refresh();

  // === Create a new window ===
  // Parameters: lines, columns, start_y, start_x
  WINDOW *win = newwin(10, 40, 5, 10); // 10 rows, 40 cols, at position (5,

  // === Draw on the window ===
  box(win, 0, 0); // Draw border (0 = default characters)
  mvwprintw(win, 1, 1, "This is a custom window!"); // mv = move, w = window
  mvwprintw(win, 2, 1, "Position: (5, 10)");
  mvwprintw(win, 3, 1, "Size: 10x40");

  // === Refresh the specific window ===
  // wrefresh(win); // Note: wrefresh for custom windows, refresh for stdscr

  // === Wait for input ===
  // getch();
  wgetch(win);
  // === Clean up window ===
  delwin(win); // Delete window (free memory)
  endwin();

  return 0;
}
