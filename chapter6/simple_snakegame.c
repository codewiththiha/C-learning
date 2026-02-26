#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct SnakeSegment {
  int x, y;
  struct SnakeSegment *next;
} SnakeSegment;

typedef struct {
  SnakeSegment *head;
  int direction; // 0: Up, 1: Right, 2: Down, 3: Left
} Snake;

typedef struct {
  int x, y, active;
} Food;

// Helper to create segments
SnakeSegment *new_seg(int x, int y) {
  SnakeSegment *s = malloc(sizeof(SnakeSegment));
  s->x = x;
  s->y = y;
  s->next = NULL;
  return s;
}

void spawn_food(Food *f, Snake *s, int w, int h) {
  int valid = 0;
  while (!valid) {
    f->x = rand() % w;
    f->y = rand() % h;
    valid = 1;

    // Use 's' to check if food spawned on snake
    SnakeSegment *curr = s->head;
    while (curr) {
      if (curr->x == f->x && curr->y == f->y) {
        valid = 0; // Collision found, try again
        break;
      }
      curr = curr->next;
    }
  }
  f->active = 1;
}

int update(Snake *s, Food *f, int w, int h) {
  int nx = s->head->x, ny = s->head->y;
  if (s->direction == 0)
    ny--;
  else if (s->direction == 1)
    nx++;
  else if (s->direction == 2)
    ny++;
  else if (s->direction == 3)
    nx--;

  // Collision: Walls
  if (nx < 0 || nx >= w || ny < 0 || ny >= h)
    return -1;

  // Collision: Self
  SnakeSegment *curr = s->head;
  while (curr) {
    if (curr->x == nx && curr->y == ny)
      return -1;
    curr = curr->next;
  }

  // Move: Add new head
  SnakeSegment *nh = new_seg(nx, ny);
  nh->next = s->head;
  s->head = nh;

  // Food logic
  if (f->active && nx == f->x && ny == f->y) {
    f->active = 0;
    return 1; // Ate food, don't remove tail
  } else {
    // Remove tail
    curr = s->head;
    while (curr->next && curr->next->next)
      curr = curr->next;
    free(curr->next);
    curr->next = NULL;
    return 0;
  }
}

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  srand(time(NULL));

  int my, mx;
  getmaxyx(stdscr, my, mx);
  int bw = 40, bh = 20;
  WINDOW *win = newwin(bh, bw, (my - bh) / 2, (mx - bw) / 2);

  Snake snake = {new_seg(10, 10), 1};
  snake.head->next = new_seg(9, 10); // Start with length 2
  Food food = {0};
  spawn_food(&food, &snake, bw - 2, bh - 2);

  int score = 0;
  while (1) {
    int ch = getch();
    if (ch != ERR) {
      // Handle WASD (both cases) and Arrows
      if ((ch == 'w' || ch == 'W' || ch == KEY_UP) && snake.direction != 2)
        snake.direction = 0;
      else if ((ch == 'd' || ch == 'D' || ch == KEY_RIGHT) &&
               snake.direction != 3)
        snake.direction = 1;
      else if ((ch == 's' || ch == 'S' || ch == KEY_DOWN) &&
               snake.direction != 0)
        snake.direction = 2;
      else if ((ch == 'a' || ch == 'A' || ch == KEY_LEFT) &&
               snake.direction != 1)
        snake.direction = 3;
      else if (ch == 'q' || ch == 'Q')
        break;
    }

    int res = update(&snake, &food, bw - 2, bh - 2);
    if (res == -1)
      break;
    if (res == 1) {
      score += 10;
      spawn_food(&food, &snake, bw - 2, bh - 2);
    }

    werase(win);
    box(win, 0, 0);
    mvwaddch(win, food.y + 1, food.x + 1, '*' | A_BOLD);
    for (SnakeSegment *p = snake.head; p != NULL; p = p->next)
      mvwaddch(win, p->y + 1, p->x + 1, (p == snake.head ? '@' : 'o'));

    mvwprintw(win, 0, 2, " Score: %d ", score);
    wrefresh(win);
    napms(200);
  }

  endwin();
  printf("Game Over! Score: %d\n", score);
  return 0;
}
