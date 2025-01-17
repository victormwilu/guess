#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

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
int pick_a_number();
int no_match_dealer();
int find_the_ace();
void play_the_game();
void show_highscore();
void input_name();
void update_player_data();

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

    if (choice < 1 || choice > 7) {
      printf("\nError: %d is an invalid choice. Please try again.\n", choice);
    }

    else if (choice < 4) {
      if (choice != last_game) {
        if (choice == 1)
          player.current_game = pick_a_number;
        if (choice == 2)
          player.current_game = no_match_dealer;
        if (choice == 3)
          player.current_game = find_the_ace;
        last_game = choice;
      }
      play_the_game();
    }

    else if (choice == 4) {
      show_highscore();
    }

    else if (choice == 5) {
      printf("\nChange your Username.\n");
      printf("Enter your Name: ");
      input_name();
      printf("\nYour Username has been successfully changed.\n");
    }

    else if (choice == 6) {
      printf("\nYour account has been reset to 100 credits.\n");
      player.credits = 100;
    }

    update_player_data();
    printf("\nThanks for Playing! Adios.\n");
  }
}

int get_player_data() {
  int uid, fd, read_bytes;
  struct user entry;

  uid = getuid();
  fd = open(DATAFILE, O_RDONLY);

  if (fd == -1)
    return -1;

  read_bytes = read(fd, &entry, sizeof(struct user));
  while (entry.uid != uid && read_bytes > 0)
    read_bytes = read(fd, &entry, sizeof(struct user));
  close(fd);

  if (read_bytes < sizeof(struct user))
    return -1;
  else
    player = entry;

  return 1;
}
