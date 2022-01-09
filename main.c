#include "dir.h"
#include "href.h"
#include "flink.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	selcFile("html"); // search file on exten 
	
	char path[5000];
	sprintf(path, "%s/%s", DIRLINKS, "test.txt");
	/*
	data_links dt = getLinksFromFile(path);
	
	char *links[] = {"https://stackoverflow.com/", "https://qwerty/text.txt/"};
	for (int i = 0; i < dt.len_links; ++i) {
		printf("%s", dt.links[i]);
	}
	*/
	//downloadLinks(getLinksFromFile(path));
}
