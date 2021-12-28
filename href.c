#include "href.h"

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadLinks() 
{
	CURL *curl;
   	FILE *fp;
    	CURLcode res;
	char path[5000];
    	char *url = "https://stackoverflow.com/";
    	char outfilename[FILENAME_MAX] = "C:\\bbb.txt";
    	curl = curl_easy_init();
    	//for (int i = 0; i < ; ++i) {
		sprintf(path, "%s/%s", DOWNDIR, outfilename);
        	fp = fopen(path,"wb");
        	curl_easy_setopt(curl, CURLOPT_URL, url);
        	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        	res = curl_easy_perform(curl);
        	
        	curl_easy_cleanup(curl);
        	fclose(fp);
	//}
}


int strHrefIndex(char* strFromHTML, char* href)
{
	int i, j, k, length;
	int tmp = strlen(href) - 1;
	for (i = 0; strFromHTML[i] != '\0'; ++i) 
	{
		for (j = i, k = 0, length = strlen(href)-1; k <= length && strFromHTML[j] == href[k]; ++j, ++k) {
			if (k > 0 && k == tmp) {
				return j + (strlen(TAGHREF) - 1);
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
		if (strstr(strFromHTML, TAGHREF) != NULL) {
			int hrefStartIndex = strHrefIndex(strFromHTML, TAGHREF), indexLink = 0;
			char link[MAXLINK];
			while (strFromHTML[hrefStartIndex] != '\"') {
				link[indexLink++] = strFromHTML[hrefStartIndex++];
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
