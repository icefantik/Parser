#include "dir.h"
#include "href.h"
#include "flink.h"
#define CWDDIR 255
#define MAXPATH 901

void selcFile(char *file_exten) 
{
	DIR *dir;
	struct dirent *ent;
	struct stat st;
	char cwd[MAXDIR];
	char *links_dir = (char*)malloc(MAXDIR * sizeof(char));
	char *path = (char*)malloc(MAXDIR * sizeof(char));
	getcwd(cwd, MAXDIR);
	sprintf(links_dir, "%s/%s", cwd, DIRLINKS);
	if ((dir = opendir(links_dir)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			sprintf(path, "%s/%s", links_dir, ent->d_name);
			if (stat(path, &st) == 0)	
			{
				if (st.st_mode & S_IFREG) { //check is files
					if (strcmp(fexten(ent->d_name), file_exten) == 0) {
						rdHtmlFile(path);
					}
				}
			} else {
				printf("cannot access path: %s\n", path);
			}
			
			
		}
	}
	closedir(dir);
}
