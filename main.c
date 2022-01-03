#include "dir.h"
#include "href.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	//perror("Error");
	selcFile("html");
	char *links[] = {"https://stackoverflow.com/", "https://qwerty/text.txt/"}; 
	downloadLinks(links, 2);
}
