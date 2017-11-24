#include <stdio.h>
#include <string.h>
#include "contact.h"

Contact contacts[MAX_CONTACTS];
int contactCount = 0;
char currentId[LEN];

int findContact(const char *id)
{
	int i;
	for (i = 0; i < contactCount; i++)
		if (strcmp(contacts[i].id, id) == 0)
			return i;
	return -1;
}

int isAdminId(const char *id)
{
	return id[0] == '0' && id[1] == '0';
}

const char *roleOf(const char *id)
{
	return isAdminId(id) ? "Admin" : "Student";
}

void sortContacts(void)
{
	int i, j;
	Contact temp;
	for (i = 0; i < contactCount - 1; i++)
		for (j = 0; j < contactCount - 1 - i; j++)
			if (strcmp(contacts[j].id, contacts[j + 1].id) > 0)
			{
				temp = contacts[j];
				contacts[j] = contacts[j + 1];
				contacts[j + 1] = temp;
			}
}

void deleteContactAt(int index)
{
	int i;
	for (i = index; i < contactCount - 1; i++)
		contacts[i] = contacts[i + 1];
	contactCount--;
}

void printTableLine(void)
{
	printf("======================================================================================\n");
}

void printTableHeader(void)
{
	printf("%-8s %-12s %-12s %-8s %-13s %s\n", "ID", "FirstName", "LastName", "Role", "Phone Number", "Email");
	printTableLine();
}

void printTableRow(const Contact *c)
{
	printf("%-8s %-12s %-12s %-8s %-13s %s\n", c->id, c->first, c->last, roleOf(c->id), c->phone, c->email);
}
