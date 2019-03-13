#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX 10000
#define MAXWORDS 400000
char *words[MAXWORDS];
char *wclass[MAXWORDS];
char *wexp[MAXWORDS];
int nwords = 0;

int read_line(FILE *fp, char str[], int limit) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
		if (i<limit - 1)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

void read()
{
	char filename[MAX];
	scanf("%s", filename);
	FILE *fp = fopen(filename, "r");

	char str[MAX];
	char delim[] = "()";
	while (!feof(fp)) {
		read_line(fp, str, MAX);
		if (strcmp(str, "\0")) {
			char *token = strtok(str, delim);
			words[nwords] = strdup(token);
			words[nwords][strlen(words[nwords]) - 1] = '\0';
			token = strtok(NULL, delim);
			wclass[nwords] = strdup(token);
			token = strtok(NULL, delim);
			wexp[nwords] = strdup(token);
			nwords++;
		}
	}
	fclose(fp);
}
void count()
{
	printf("%d\n", nwords);
}
int findIndex(char word[], int start, int end)
{
	if (start > end) return start - 1;
	int middle = (start + end) / 2;

	if (strcmp(word, words[middle]) == 0) return middle;
	else if (strcmp(word, words[middle]) < 0) return findIndex(word, start, middle - 1);
	else return findIndex(word, middle + 1, end);

}
void findWords(char word[], int index) {
	if (index == -1) {
		printf("Not found-1.\n");
		printf("- - -\n");
		printf("%s (%s)\n", words[0], wclass[0]);
	}
	else if (strcmp(words[index], word) != 0) {     //찾는 단어 존재x
		printf("Not found.\n");
		printf("%s (%s)\n", words[index], wclass[index]);
		printf("- - -\n");
		if (index<nwords - 1)
			printf("%s (%s)\n", words[index + 1], wclass[index + 1]);

	}
	else {   //찾는 단어 존재
		int upcount = -1, downcount = -1, i = index, j = index;
		while (i >= 0 && strcmp(words[i--], word) == 0) {
			downcount++;
		}
		while (j<nwords && strcmp(words[j++], word) == 0) {
			upcount++;
		}
		printf("Found %d items.\n", upcount + downcount + 1);
		for (int i = index - downcount; i < index; i++) {
			printf("%s (%s)%s\n", words[i], wclass[i], wexp[i]);
		}
		printf("%s (%s)%s\n", words[index], wclass[index], wexp[index]);
		for (int j = index + 1; j <= index + upcount; j++) {
			printf("%s (%s)%s\n", words[j], wclass[j], wexp[j]);
		}
	}
}

int main() {
	char command[MAX];
	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "exit") == 0)break;
		else if (strcmp(command, "read") == 0) read();
		else if (strcmp(command, "size") == 0) count();
		else if (strcmp(command, "find") == 0) {
			char word[MAX];
			scanf("%s", word);
			word[0] = word[0] - 32;
			int index = findIndex(word, 0, nwords - 1);
			findWords(word, index);
		}
		else printf("Invalid command\n");
	}

	getch();
	return 0;
}