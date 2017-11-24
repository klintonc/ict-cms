#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "contact.h"
#include "input.h"

/* ---------- Edit ---------- */

static void editContact(int idx)
{
	Contact *c = &contacts[idx];
	int choice;

	printf("[%s] ID: %s\n\n", isAdminId(c->id) ? "ADMIN" : "STUDENT", c->id);
	printf("[1] First Name: %s\n", c->first);
	printf("[2] Last Name: %s\n", c->last);
	printf("[3] Phone Number: %s\n", c->phone);
	printf("[4] Email: %s\n", c->email);
	printf("[5] Password: ********\n");
	printf("Please enter the choice to edit: ");
	choice = readChoice();
	while (choice < 1 || choice > 5)
	{
		printf("[ERROR] Please choose 1-5\n");
		printf("[Re-type] Please enter the choice to edit: ");
		choice = readChoice();
	}
	printf("\n");

	switch (choice)
	{
	case 1:
		printf("[Re-Input] First Name: ");
		readWord(c->first);
		break;
	case 2:
		printf("[Re-Input] Last Name: ");
		readWord(c->last);
		break;
	case 3:
		printf("[Re-Input] Phone Number: ");
		readValidPhone(c->phone);
		break;
	case 4:
		printf("[Re-Input] Email: ");
		readValidEmail(c->email);
		break;
	case 5:
		printf("[Re-Input] Password: ");
		readValidPassword(c->pass, "[Re-Input] Confirmed Password: ");
		break;
	}
	printf("Record successfully updated!!\n\n");
	pauseScreen();
}

static void editMyContact(void)
{
	clearScreen();
	printf("[Edit My Contact Information]\n\n");
	editContact(findContact(currentId));
}

static void editUserContact(void)
{
	char id[LEN];
	int idx;

	clearScreen();
	printf("[Edit User's Contact]\n\n");
	printf("[ADMIN] ID: %s\n\n", currentId);
	printf("Please enter the id for editing: ");
	readWord(id);
	while ((idx = findContact(id)) == -1)
	{
		printf("[ERROR] There is no matched id in the system.\n");
		printf("[Re-Type] Please enter the id for editing: ");
		readWord(id);
	}
	printf("\n");
	editContact(idx);
}

/* ---------- Show all ---------- */

static void showAllContacts(void)
{
	int i;

	clearScreen();
	printf("[Show all Contacts]\n\n");
	printf("===============================\n");
	printf("All Contacts\n");
	printf("===============================\n\n");
	sortContacts();
	printTableHeader();
	for (i = 0; i < contactCount; i++)
		printTableRow(&contacts[i]);
	printTableLine();
	printf("\n");
	pauseScreen();
}

/* ---------- Search (partial, case-insensitive) ---------- */

static int containsIgnoreCase(const char *text, const char *word)
{
	int i, j;
	for (i = 0; text[i] != '\0'; i++)
	{
		j = 0;
		while (word[j] != '\0' && tolower((unsigned char)text[i + j]) == tolower((unsigned char)word[j]))
			j++;
		if (word[j] == '\0')
			return 1;
	}
	return 0;
}

static void searchContacts(void)
{
	char name[LEN];
	int i, found = 0;

	clearScreen();
	printf("[Search for a Contacts]\n\n");
	printf("===============================\n");
	printf("Contacts Information\n");
	printf("===============================\n\n");
	sortContacts();
	printf("Please input First Name for searching: ");
	while (1)
	{
		readWord(name);
		for (i = 0; i < contactCount; i++)
		{
			if (containsIgnoreCase(contacts[i].first, name))
			{
				if (found == 0)
				{
					printf("\n");
					printTableHeader();
				}
				printTableRow(&contacts[i]);
				found++;
			}
		}
		if (found > 0)
			break;
		printf("[ERROR] There is no person Name '%s' in the system.\n", name);
		printf("[Re-Type] Please input First Name for searching: ");
	}
	printTableLine();
	printf("\n");
	pauseScreen();
}

/* ---------- Delete (admin only) ---------- */

static void deleteUserContact(void)
{
	char id[LEN], answer[LEN];
	Contact *c;
	int idx;

	clearScreen();
	printf("[Delete User's Contact]\n\n");
	printf("[ADMIN] ID: %s\n\n", currentId);
	while (1)
	{
		printf("Please enter the id for deleting (0 to go back): ");
		readWord(id);
		if (strcmp(id, "0") == 0)
		{
			clearScreen();
			return;
		}
		idx = findContact(id);
		if (idx == -1)
		{
			printf("[ERROR] There is no matched id in the system.\n");
			continue;
		}
		if (strcmp(id, currentId) == 0)
		{
			printf("[ERROR] You cannot delete your own account.\n");
			continue;
		}

		c = &contacts[idx];
		printf("\n[%s]\n", isAdminId(c->id) ? "ADMIN" : "STUDENT");
		printf("ID: %s\n", c->id);
		printf("First Name: %s\n", c->first);
		printf("Last Name: %s\n", c->last);
		printf("Phone Number: %s\n", c->phone);
		printf("Email: %s\n\n", c->email);
		printf("Do you want to delete this contact information(Y/N)? ");
		while (1)
		{
			readWord(answer);
			if (strcmp(answer, "Y") == 0 || strcmp(answer, "y") == 0)
			{
				deleteContactAt(idx);
				printf("Record Successfully Deleted!!!\n\n");
				pauseScreen();
				return;
			}
			if (strcmp(answer, "N") == 0 || strcmp(answer, "n") == 0)
				break; /* ask for another id */
			printf("[ERROR] Please type Y or N: ");
		}
	}
}

/* ---------- Menus ---------- */

static void logout(void)
{
	clearScreen();
	printf("[Logout Page]\n\n");
	printf("Goodbye!!!\n\n");
	pauseScreen();
}

void studentMenu(void)
{
	while (1)
	{
		printf("\n[1] Edit My Contact Information\n");
		printf("[2] Show all Contacts\n");
		printf("[3] Search for a Contact\n");
		printf("[0] Logout\n");
		printf("Please enter the choice: ");
		switch (readChoice())
		{
		case 1:
			editMyContact();
			break;
		case 2:
			showAllContacts();
			break;
		case 3:
			searchContacts();
			break;
		case 0:
			logout();
			return;
		default:
			printf("Wrong Input....!!!\n");
			pauseScreen();
		}
	}
}

void adminMenu(void)
{
	while (1)
	{
		printf("\n[1] Edit User's Contact\n");
		printf("[2] Show all Contacts\n");
		printf("[3] Search for a Contact\n");
		printf("[4] Delete User's Contact\n");
		printf("[0] Logout\n");
		printf("Please enter the choice: ");
		switch (readChoice())
		{
		case 1:
			editUserContact();
			break;
		case 2:
			showAllContacts();
			break;
		case 3:
			searchContacts();
			break;
		case 4:
			deleteUserContact();
			break;
		case 0:
			logout();
			return;
		default:
			printf("Wrong Input....!!!\n");
			pauseScreen();
		}
	}
}
