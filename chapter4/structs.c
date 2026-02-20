#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} Position;

typedef struct SnakeSegment {
  Position pos;
  struct SnakeSegment *next;
} SnakeSegment;

typedef struct {
  Position pos;
  int value;
  int is_active;
} Food;

typedef struct {
  SnakeSegment *head;
  SnakeSegment *tail;
  int length;
  int score;
  int direction;
  int game_over;
  int width;
  int height;
} GameState;

typedef struct {
  char name[50];
  int high_score;
  Position last_position;
} PlayerProfile;

SnakeSegment *create_segment(int x, int y) {
  SnakeSegment *segment = (SnakeSegment *)malloc(sizeof(SnakeSegment));
  if (segment == NULL) {
    printf("ERROR: Memory allocation failed!\n");
    return NULL;
  }
  segment->pos.x = x;
  segment->pos.y = y;
  segment->next = NULL;

  return segment;
}

Food create_food(int x, int y, int value) {
  Food food;
  food.pos.x = x;
  food.pos.y = y;
  food.value = value;
  food.is_active = 1;
  return food;
}

GameState *create_game(int width, int height) {
  GameState *game = (GameState *)calloc(1, sizeof(GameState));

  if (game == NULL) {
    return NULL;
  }

  game->width = width;
  game->height = height;
  game->score = 0;
  game->length = 0;
  game->direction = 1; // Start moving right
  game->game_over = 0;
  game->head = NULL;
  game->tail = NULL;

  return game;
}

void print_position(Position pos) {
  printf("Position: (%d, %d)\n", pos.x, pos.y);
}

void print_segment(SnakeSegment *seg) {
  if (seg == NULL) {
    printf("NULL segment\n");
    return;
  }
  printf("Segment at (%d, %d) → next: %p\n", seg->pos.x, seg->pos.y,
         (void *)seg->next);
}

void print_game_state(GameState *game) {
  if (game == NULL) {
    printf("NULL game state\n");
    return;
  }

  printf("=== Game State ===\n");
  printf("Board: %d x %d\n", game->width, game->height);
  printf("Score: %d\n", game->score);
  printf("Length: %d\n", game->length);
  printf("Direction: %d\n", game->direction);
  printf("Game Over: %s\n", game->game_over ? "YES" : "NO");
  printf("Head: %p\n", (void *)game->head);
  printf("Tail: %p\n\n", (void *)game->tail);
}

int main() {

  // struct initizlization style1
  Position pos1 = {.x = 5, .y = 10};
  Position pos2 = {.x = 15, .y = 20};

  printf("Position Examples:\n");
  print_position(pos1);
  print_position(pos2);
  printf("\n");

  // struct initizlization style 2 tho style 1 is much more cleaner
  SnakeSegment *seg1 = create_segment(5, 10);
  SnakeSegment *seg2 = create_segment(6, 10);
  SnakeSegment *seg3 = create_segment(7, 10);

  // Link them together
  seg1->next = seg2;
  seg2->next = seg3;

  print_segment(seg1);
  print_segment(seg1->next);
  print_segment(seg1->next->next);
  printf("\n");

  // === CREATE FOOD ===
  printf("Food Examples:\n");
  Food food1 = create_food(10, 10, 10);
  Food food2 = {.pos = {15, 15}, .value = 20, .is_active = 1};

  printf("Food 1: (%d, %d) value=%d active=%d\n", food1.pos.x, food1.pos.y,
         food1.value, food1.is_active);
  printf("Food 2: (%d, %d) value=%d active=%d\n\n", food2.pos.x, food2.pos.y,
         food2.value, food2.is_active);

  // === CREATE GAME STATE ===
  printf("Game State:\n");
  GameState *game = create_game(40, 20);
  game->head = seg1;
  game->tail = seg3;
  game->length = 3;

  print_game_state(game);

  // === NESTED STRUCT ===
  printf("Player Profile:\n");
  PlayerProfile player;
  strcpy(player.name, "Player1");
  player.high_score = 1000;
  player.last_position = pos1;

  printf("Name: %s\n", player.name);
  printf("High Score: %d\n", player.high_score);
  print_position(player.last_position);
  printf("\n");

  // === CLEANUP ===
  printf("Cleaning up memory...\n");
  free(seg1);
  free(seg2);
  free(seg3);
  free(game);
  printf("Done!\n");

  return 0;
}
