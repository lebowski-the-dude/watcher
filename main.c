#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "users.h"
#include "telegram.h"

int
main (int argc, char **argv)
{
  int logged_in_users_allowed = atoi(argv[1]);
  char token[47]; strncpy(token, argv[2], 47);
  char chat_id[11]; strncpy(chat_id, argv[3], 11);

  int users_amount = getAmountOfLoggedInUsers();
  if (users_amount == 0)
	return 0;
  if (users_amount <= logged_in_users_allowed)
	return 0;

  struct User users[users_amount];
  fillUsers(users, users_amount);

  char report[(users_amount * 80 * 4) + 26 + 26];
  fillReport(report, users, users_amount);

  char url[sizeof(token) + sizeof(chat_id) + sizeof(report)];
  fillUrl(url, token, chat_id, report);

  sendMessage(url);

  return 0;
}
