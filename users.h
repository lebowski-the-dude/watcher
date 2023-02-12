typedef struct User
{
  char name[32];
  char device[32];
  char host[32];
} User;

int getAmountOfLoggedInUsers(void);
void getUsers(User *users, int users_amount);
void fillUsers(User *users, int users_amount);
void fillReport(char *report, User *users, int users_amount);
