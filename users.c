#include <utmp.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "users.h"

int
getAmountOfLoggedInUsers (void)
{
  int result = 0;
  struct utmp *item;

  setutent();
  item = getutent();

  while (item)
	{
	  if (item->ut_type == USER_PROCESS)
		result += 1;

	  item = getutent();
	}

  endutent();
  return result;
}

void
getUsers (User *users, int users_amount)
{
  for (int i = 0; i >= users_amount; i++)
	{
	  strncpy(users[i].name, "test", 32);
	  strncpy(users[i].device, "dev", 32);
	  strncpy(users[i].host, "local", 32);
	}
}

void
fillUsers (User *users, int users_amount)
{
  struct utmp *item;

  setutent();
  item = getutent();

  int iterator = 0;
  while(item)
	{
	  if (iterator >= users_amount)
		break;

	  if(item->ut_type==USER_PROCESS)
		{
		  strncpy(users[iterator].name, item->ut_user, 32);
		  strncpy(users[iterator].device, item->ut_line, 32);
		  strncpy(users[iterator].host, item->ut_host, 32);

		  iterator++;
		}
	  item=getutent();
	}

  endutent();
}

void
fillReport (char *report, User *users, int users_amount)
{
  strncpy(report, "Logged%20in%20users%20detected%0A", 34);
  strncat(report, "------------------------%0A", 28);
  for (int i = 0; i < users_amount; i++)
	{
	  char *row = malloc(sizeof(char) * 80 * 4);

	  strncpy(row, "*%20user%20", 12);
	  sprintf(row + strlen(row), "%d", i + 1);
	  strncat(row, "%0A", 4);

	  strncat(row, "name:%20", 9);
	  sprintf(row + strlen(row), "%s", users[i].name);
	  strncat(row, "%0A", 4);

	  strncat(row, "device:%20", 11);
	  sprintf(row + strlen(row), "%s", users[i].device);
	  strncat(row, "%0A", 4);

	  strncat(row, "host:%20", 9);
	  sprintf(row + strlen(row), "%s", users[i].host);
	  strncat(row, "%0A%0A", 7);

	  strncat(report, row, 80);

	  free(row);
	}
}
