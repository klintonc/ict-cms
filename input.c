#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

static void flushLine(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

void readWord(char *buf)
{
	if (scanf("%63s", buf) != 1) /* 63 = LEN - 1 */
	{
		printf("\nNo more input. Goodbye!\n");
		exit(0);
	}
	flushLine();
}

int isAllDigits(const char *s)
{
	if (*s == '\0')
		return 0;
	for (; *s; s++)
		if (!isdigit((unsigned char)*s))
			return 0;
	return 1;
}

int readChoice(void)
{
	char buf[64];
	readWord(buf);
	if (!isAllDigits(buf) || strlen(buf) > 3)
		return -1;
	return atoi(buf);
}

void clearScreen(void)
{
#ifdef _WIN32
	system("cls");
#else
	printf("\033[2J\033[H");
#endif
}

void pauseScreen(void)
{
	printf("Press Enter to continue...");
	flushLine();
	clearScreen();
}

void readValidPhone(char *phone)
{
	readWord(phone);
	while (strlen(phone) != 10 || !isAllDigits(phone))
	{
		printf("[ERROR] You must use only 10 digit numbers for phone number\n");
		printf("[Re-type] Phone Number: ");
		readWord(phone);
	}
}

void readValidEmail(char *email)
{
	readWord(email);
	while (strchr(email, '@') == NULL)
	{
		printf("[ERROR] You must contain character @\n");
		printf("[Re-type] Email: ");
		readWord(email);
	}
}

void readValidPassword(char *pass, const char *confirmPrompt)
{
	char confirm[64];

	readWord(pass);
	while (strlen(pass) < 8)
	{
		printf("[ERROR] You must use at least 8 characters for password\n");
		printf("[Re-type] Password: ");
		readWord(pass);
	}

	printf("%s", confirmPrompt);
	readWord(confirm);
	while (strcmp(pass, confirm) != 0)
	{
		printf("[ERROR] These passwords don't match\n");
		printf("[Re-type] Confirmed Password: ");
		readWord(confirm);
	}
}
