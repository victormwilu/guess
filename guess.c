#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define DATAFILE "/var/guess.data"
const int INF = 1e9 + 5;

struct user {
  int uid;
  int credits;
  int highscore;
  char name[100];
  int (*current_game)();
};

struct user player;

// functions
int get_player_data();
void register_new_player();

int main() {
  int choice, last_game = INF;
  srand(time(0));

  if (get_player_data() == -1) {
    register_new_player();
  }

  while (choice != 7) {
    printf("1. Play the Pick a Number Game.\n");
    printf("2. Play the No Match Dealer Game.\n");
    printf("3. Play the Find the Ace Game.\n");
    printf("4. View the current highscore.\n");
    printf("5. Change your username.\n");
    printf("6. Reset your account to 100 credits.\n");
    printf("7. Quit!\n");
    scanf("%d", &choice);
  }
}
