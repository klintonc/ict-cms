#include <stdio.h>
#include "contact.h"
#include "input.h"
#include "auth.h"
#include "menu.h"

int main(void)
{
	while (1)
	{
		printf("===============================\n");
		printf("ICT Contact Management Systems\n");
		printf("===============================\n");
		printf("[1] User Registration\n");
		printf("[2] Login\n");
		printf("[0] Exit\n");
		printf("-----------------------\n");
		printf("Enter the choice: ");
		switch (readChoice())
		{
		case 1:
			clearScreen();
			registration();
			break;
		case 2:
			clearScreen();
			if (login())
			{
				if (isAdminId(currentId))
					adminMenu();
				else
					studentMenu();
			}
			break;
		case 0:
			return 0;
		default:
			printf("Wrong Input....!!!\n");
			pauseScreen();
		}
	}
}
