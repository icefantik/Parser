#include "dir.h"
#include "href.h"

void selcFile() 
{
	DIR *dir;
	struct dirent *ent;
	struct stat st;
	char cwd[MAXDIR];
	char* path = malloc(MAXDIR * sizeof(char));
	getcwd(cwd, MAXDIR);
	if ((dir = opendir(cwd)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			sprintf(path, "%s\\%s", cwd, ent->d_name);
			if (stat(path, &st) == 0) 
			{
				if (st.st_mode & S_IFREG) { //check is files
					if (strcmp(fexten(ent->d_name), "lmth") == 0) {
						rdHtmlFile(ent->d_name);
					}
				}
			} else {
				printf("cannot access path: %s\n", path);
			}
		}
	}
	closedir(dir);
}
