#ifndef INPUT_H
#define INPUT_H

void readWord(char *buf); /* buf must hold LEN chars */
int readChoice(void);     /* returns -1 on non-number */
int isAllDigits(const char *s);
void clearScreen(void);
void pauseScreen(void);   /* wait for Enter, then clear */

/* read + validate, re-asking until valid (caller prints the first prompt) */
void readValidPhone(char *phone);
void readValidEmail(char *email);
void readValidPassword(char *pass, const char *confirmPrompt);

#endif
