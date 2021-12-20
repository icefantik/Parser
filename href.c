#include "href.h"

/*
boolean downloadLink(char* url) 
{
	CURL *curl;
	CURLcode 		
}
*/

int strHrefIndex(char* strFromHTML, char* href)
{
	int i, j, k, length;
	int tmp = strlen(href) - 1;
	for (i = 0; strFromHTML[i] != '\0'; ++i) 
	{
		for (j = i, k = 0, length = strlen(href)-1; k <= length && strFromHTML[j] == href[k]; ++j, ++k) {
			if (k > 0 && k == tmp) {
				return j + 3;
			}
		}
	}
	return -1;
}

void rdHtmlFile(char* htmlName)
{
	setlocale(LC_ALL, "Rus");
	FILE *file = fopen(htmlName, "r");
	char strFromHTML[LENHTML];
	while(fgets(strFromHTML, sizeof(strFromHTML), file))
	{
		if (strstr(strFromHTML, "href") != NULL) {
			int tmp = strHrefIndex(strFromHTML, "href"), indexLink = 0;
			char link[MAXLINK];
			while (strFromHTML[tmp] != '\"') {
				link[indexLink++] = strFromHTML[tmp++];
			}
			printf("%s\n", link);
		}
	}
	fclose(file);
}

char* fexten(char* nameFile)
{
	char* fext = malloc((HTLEXT + 1) * sizeof(char));
	for (int i = strlen(nameFile) - 1, j = 0; nameFile[i] != '.' && i >= 0; --i, ++j) {
		fext[j] = nameFile[i];
	}
	return fext;
}