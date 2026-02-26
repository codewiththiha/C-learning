#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// === STRUCTURES ===
typedef struct SnakeSegment {
  int x, y;
  struct SnakeSegment *next;
} SnakeSegment;

typedef struct {
  SnakeSegment *head;
  SnakeSegment *tail;
  int length;
  int direction; // 0=up, 1=right, 2=down, 3=left
} Snake;

typedef struct {
  int x, y, active;
} Food;

// === FUNCTION PROTOTYPES ===
SnakeSegment *create_segment(int x, int y);
Snake *create_snake(int start_x, int start_y, int length);
void free_snake(Snake *snake);
int move_snake(Snake *snake, Food *food, int width, int height);
void draw_snake(Snake *snake, WINDOW *win);
void draw_food(Food *food, WINDOW *win);
void spawn_food(Food *food, Snake *snake, int width, int height);
void draw_border(WINDOW *win);

// === MAIN GAME ===
int main() {
  // === Initialize ===
  srand(time(NULL)); // Seed random number generator
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  // === Colors ===
  if (has_colors()) {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Body
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Food
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Head
    init_pair(4, COLOR_WHITE, COLOR_BLACK);  // Border
    init_pair(5, COLOR_CYAN, COLOR_BLACK);   // UI
  }

  // === Get Terminal Size ===
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  // === Create Windows ===
  WINDOW *border = newwin(max_y - 1, max_x, 0, 0);
  WINDOW *board = newwin(max_y - 3, max_x - 2, 1, 1);
  WINDOW *score_win = newwin(3, 20, 0, max_x - 21);

  // === Game State ===
  Snake *snake = create_snake(max_x / 4, max_y / 2, 3);
  Food food = {0};
  int score = 0;
  int game_over = 0;
  int ch;
  char score_str[30];

  // === Spawn Initial Food ===
  spawn_food(&food, snake, max_x - 2, max_y - 3);

  // === Initial Draw ===
  draw_border(border);
  draw_snake(snake, board);
  draw_food(&food, board);

  mvwprintw(score_win, 1, 1, "Score: 0");
  mvwprintw(score_win, 2, 1, "Q=Quit ARROWS=Move");
  box(score_win, 0, 0);

  refresh();
  wrefresh(border);
  wrefresh(board);
  wrefresh(score_win);

  // === GAME LOOP ===
  while (!game_over) {
    // === Input Handling ===
    ch = getch();

    if (ch == 'q' || ch == 'Q') {
      break;
    }

    // Change direction (prevent 180-degree turns)
    switch (ch) {
    case KEY_UP:
    case 'w':
    case 'W':
      if (snake->direction != 2)
        snake->direction = 0;
      break;
    case KEY_DOWN:
    case 's':
    case 'S':
      if (snake->direction != 0)
        snake->direction = 2;
      break;
    case KEY_LEFT:
    case 'a':
    case 'A':
      if (snake->direction != 1)
        snake->direction = 3;
      break;
    case KEY_RIGHT:
    case 'd':
    case 'D':
      if (snake->direction != 3)
        snake->direction = 1;
      break;
    }

    // === Move Snake ===
    int result = move_snake(snake, &food, max_x - 2, max_y - 3);

    if (result == -1) {
      game_over = 1;
      break;
    }

    if (result == 1) {
      score += 10;
      spawn_food(&food, snake, max_x - 2, max_y - 3);
    }

    // === Clear and Redraw ===
    werase(board);
    draw_snake(snake, board);
    draw_food(&food, board);

    // === Update Score ===
    sprintf(score_str, "Score: %d", score);
    mvwprintw(score_win, 1, 1, "%s", score_str);
    wrefresh(score_win);

    // === Game Speed ===
    napms(100); // 10 FPS
  }

  // === Game Over Screen ===
  if (game_over) {
    mvwprintw(board, max_y / 2 - 1, max_x / 2 - 5, "GAME OVER!");
    mvwprintw(board, max_y / 2, max_x / 2 - 7, "Final Score: %d", score);
    mvwprintw(board, max_y / 2 + 1, max_x / 2 - 9, "Press Q to exit");
    wrefresh(board);

    // Wait for Q
    nodelay(stdscr, FALSE); // Blocking input
    while (1) {
      ch = getch();
      if (ch == 'q' || ch == 'Q')
        break;
    }
  }

  // === Cleanup ===
  free_snake(snake);
  delwin(border);
  delwin(board);
  delwin(score_win);
  endwin();

  return 0;
}

// === HELPER FUNCTIONS ===

SnakeSegment *create_segment(int x, int y) {
  SnakeSegment *seg = (SnakeSegment *)malloc(sizeof(SnakeSegment));
  if (seg == NULL)
    return NULL;
  seg->x = x;
  seg->y = y;
  seg->next = NULL;
  return seg;
}

Snake *create_snake(int start_x, int start_y, int length) {
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  if (snake == NULL)
    return NULL;

  snake->head = NULL;
  snake->tail = NULL;
  snake->length = 0;
  snake->direction = 1;

  for (int i = 0; i < length; i++) {
    SnakeSegment *seg = create_segment(start_x - i, start_y);
    if (seg == NULL) {
      free(snake);
      return NULL;
    }

    if (snake->head == NULL) {
      snake->head = seg;
      snake->tail = seg;
    } else {
      snake->tail->next = seg;
      snake->tail = seg;
    }
    snake->length++;
  }

  return snake;
}

void free_snake(Snake *snake) {
  if (snake == NULL)
    return;

  SnakeSegment *current = snake->head;
  while (current != NULL) {
    SnakeSegment *next = current->next;
    free(current);
    current = next;
  }

  free(snake);
}

void draw_border(WINDOW *win) {
  box(win, 0, 0);
  wattron(win, COLOR_PAIR(4));
  mvwprintw(win, 0, 2, " SNAKE GAME ");
  wattroff(win, COLOR_PAIR(4));
  wrefresh(win);
}

void draw_snake(Snake *snake, WINDOW *win) {
  if (snake == NULL)
    return;

  SnakeSegment *current = snake->head;
  int is_head = 1;

  while (current != NULL) {
    if (is_head) {
      wattron(win, COLOR_PAIR(3));
      mvwaddch(win, current->y, current->x, '@');
      wattroff(win, COLOR_PAIR(3));
      is_head = 0;
    } else {
      wattron(win, COLOR_PAIR(1));
      mvwaddch(win, current->y, current->x, 'O');
      wattroff(win, COLOR_PAIR(1));
    }
    current = current->next;
  }

  wrefresh(win);
}

void draw_food(Food *food, WINDOW *win) {
  if (food == NULL || !food->active)
    return;

  wattron(win, COLOR_PAIR(2));
  mvwaddch(win, food->y, food->x, '*');
  wattroff(win, COLOR_PAIR(2));

  wrefresh(win);
}

void spawn_food(Food *food, Snake *snake, int width, int height) {
  int valid = 0;

  while (!valid) {
    food->x = (rand() % (width - 2)) + 1;
    food->y = (rand() % (height - 2)) + 1;
    valid = 1;

    SnakeSegment *current = snake->head;
    while (current != NULL) {
      if (current->x == food->x && current->y == food->y) {
        valid = 0;
        break;
      }
      current = current->next;
    }
  }

  food->active = 1;
}

int move_snake(Snake *snake, Food *food, int width, int height) {
  if (snake == NULL || snake->head == NULL)
    return 0;

  int new_x = snake->head->x;
  int new_y = snake->head->y;

  switch (snake->direction) {
  case 0:
    new_y--;
    break;
  case 1:
    new_x++;
    break;
  case 2:
    new_y++;
    break;
  case 3:
    new_x--;
    break;
  }

  // Wall collision
  if (new_x < 1 || new_x >= width - 1 || new_y < 1 || new_y >= height - 1) {
    return -1;
  }

  // Self collision
  SnakeSegment *current = snake->head;
  while (current != NULL) {
    if (current->x == new_x && current->y == new_y) {
      return -1;
    }
    current = current->next;
  }

  // Food collision
  int ate_food = 0;
  if (food->active && new_x == food->x && new_y == food->y) {
    ate_food = 1;
    food->active = 0;
  }

  // New head
  SnakeSegment *new_head = create_segment(new_x, new_y);
  if (new_head == NULL)
    return -1;

  new_head->next = snake->head;
  snake->head = new_head;

  // Remove tail or grow
  if (!ate_food) {
    SnakeSegment *second_tail = snake->head;
    while (second_tail->next != snake->tail) {
      second_tail = second_tail->next;
    }
    free(snake->tail);
    snake->tail = second_tail;
    snake->tail->next = NULL;
  } else {
    snake->length++;
  }

  return ate_food;
}
