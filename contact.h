#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define LEN 64 /* size of every text field (input.c reads at most LEN-1 chars) */

typedef struct
{
	char id[LEN];
	char first[LEN];
	char last[LEN];
	char phone[LEN];
	char email[LEN];
	char pass[LEN];
} Contact;

extern Contact contacts[MAX_CONTACTS];
extern int contactCount;
extern char currentId[LEN]; /* ID of the logged-in user */

int findContact(const char *id); /* index, or -1 if not found */
int isAdminId(const char *id);   /* ID starts with "00" */
const char *roleOf(const char *id);
void sortContacts(void);         /* sort by ID (extra feature) */
void deleteContactAt(int index);

void printTableHeader(void);
void printTableRow(const Contact *c);
void printTableLine(void);

#endif
