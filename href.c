#include "href.h"
#define FEXTEN 101
#define FNAME 101

void reverse(char*, int);
char* getNameFileLink(char*, int);
char* getExtenFromLink(char*, int);

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadLinks(data_links dt_links)
{
	printf("1.\n");
	//printf("%d\n%s\n", dt_links.len_links, dt_links.links[0]);
	CURL *curl;
   	FILE *fp;
    	CURLcode res;
	char path[5000];
	char *exten_file, *name_file;
	curl = curl_easy_init();
	for (int i = 0, len_url; i < dt_links.len_links; ++i) {
		len_url = strlen(dt_links.links[i]);
		
		exten_file = getExtenFromLink(dt_links.links[i], len_url);
		/*
		//if (strcmp(exten_file, "html") != 0)
		//	reverse(exten_file, strlen(exten_file));
		
		name_file = getNameFileLink(dt_links.links[i], len_url);
		sprintf(path, "%s/%s.%s", DOWNDIR, name_file, exten_file);
	
		fp = fopen(path,"wb");
		curl_easy_setopt(curl, CURLOPT_URL, dt_links.links[i]);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        	res = curl_easy_perform(curl);	
		fclose(fp);
		*/		
	}
	curl_easy_cleanup(curl);
}

char* getNameFileLink(char* url, int len_url)
{
	int index_name_file = 0;
	char* name_file = (char*)malloc(sizeof(char) * FNAME);
	for (int index_url = strchr(url, '/') - url + 2; url[index_url] != '/' && index_url >= 0; ++index_url, ++index_name_file)
	{
		name_file[index_name_file] = url[index_url];
	}
	name_file[index_name_file++] = '\0';
	return name_file;
}


void reverse(char* str, int len)
{
	char tmp;
	for (int start_index = 0, end_index = len - 1; start_index  < end_index; ++start_index, --end_index) {
		tmp = str[start_index];
		str[start_index] = str[end_index];
		str[end_index] = tmp;
	}
}

char* getExtenFromLink(char* url, int len_url)
{
	printf("%s\n", url);
	int index_exten = 0;
	char* file_exten = (char*)malloc(sizeof(char) * FEXTEN * 2);
	for (int index_url = len_url - 1; url[index_url] != '.' && index_url >= 0; --index_url) 
	{
		//printf("%d %c\n", index_url, url[index_url]);
		if (url[index_url] == '/') {
			free(file_exten);
			return "html";	
		}
		file_exten[index_exten++] = url[index_url];
	}
	file_exten[index_exten] = '\0';
	reverse(file_exten, index_exten);
	printf(": %s\n", file_exten);
	return file_exten;
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
	FILE *file = fopen(htmlName, "r");
	char strFromHTML[LENHTML];
	data_links dt_links;
	dt_links.len_links = 0;
	//dt_links.links = (char**)malloc(ROWLINKS * COLUMLINKS * sizeof(char*));
	while(fgets(strFromHTML, sizeof(strFromHTML), file))
	{
		if (strstr(strFromHTML, TAGHREF) != NULL) {
			int hrefStartIndex = strHrefIndex(strFromHTML, TAGHREF), indexLink = 0;
			char link[MAXLINK];
			while (strFromHTML[hrefStartIndex] != '\"') {
				link[indexLink++] = strFromHTML[hrefStartIndex++];
			}
			strcpy(dt_links.links[dt_links.len_links++], link);
			printf("%s\n", link);
		}
	}
	fclose(file);
	downloadLinks(dt_links);
}

char* fexten(char* nameFile)
{
	int index_fexten = 0;
	char* fext = malloc((HTLEXT + 1) * sizeof(char));
	for (int i = strlen(nameFile) - 1; nameFile[i] != '.' && i >= 0; --i, ++index_fexten) {
		fext[index_fexten] = nameFile[i];
	}
	fext[index_fexten++] = '\0';
	reverse(fext, strlen(fext));
	return fext;
}
