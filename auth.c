#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "contact.h"
#include "input.h"

static void readNewId(char *id)
{
	while (1)
	{
		readWord(id);
		if (strlen(id) != 7 || !isAllDigits(id))
			printf("[ERROR] You can use only 7 digits for ID\n");
		else if (findContact(id) != -1)
			printf("[ERROR] This ID is already registered\n");
		else
			return;
		printf("[Re-type] ID: ");
	}
}

void registration(void)
{
	Contact c;

	printf("[Registration]\n\n");
	if (contactCount >= MAX_CONTACTS)
	{
		printf("[ERROR] The system is full. Cannot register more users.\n\n");
		pauseScreen();
		return;
	}

	printf("Please enter the following information\n");
	printf("ID: ");
	readNewId(c.id);
	printf("First Name: ");
	readWord(c.first);
	printf("Last Name: ");
	readWord(c.last);
	printf("Phone Number: ");
	readValidPhone(c.phone);
	printf("Email: ");
	readValidEmail(c.email);
	printf("Password: ");
	readValidPassword(c.pass, "Confirmed Password: ");

	contacts[contactCount] = c;
	contactCount++;

	printf("\n-- End of the Registration Process --\n\n");
	printf("Congratulation!! %s,\n", c.first);
	printf("Now you can login to the ICT Contact Management System and start to\n");
	printf("search for ICT faculty staffs' and friends' information.\n\n");
	pauseScreen();
}

int login(void)
{
	char id[LEN], pass[LEN];
	int i;

	printf("[Login Page]\n\n");
	if (contactCount == 0)
	{
		printf("[ERROR] No users registered yet. Please register first.\n\n");
		pauseScreen();
		return 0;
	}

	printf("Please enter your ID: ");
	while (1)
	{
		readWord(id);
		printf("Please enter your Password: ");
		readWord(pass);
		i = findContact(id);
		if (i != -1 && strcmp(contacts[i].pass, pass) == 0)
			break;
		printf("[ERROR] Wrong ID or Password!!!\n");
		printf("[Re-Type] Please enter your ID: ");
	}

	strcpy(currentId, id);
	printf("\nNow you are logged in as %s in the system.\n", isAdminId(id) ? "an admin" : "a student");
	printf("You can start using the following functions.\n");
	return 1;
}
