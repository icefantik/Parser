#ifndef __FLINKS__
#define __FLINKS__

#include <stdio.h>
#include <string.h>
#define ROWLINKS 100
#define COLUMLINKS 100
#define DIRLINKS "Links"

typedef struct
{
	char links[ROWLINKS][COLUMLINKS];
	int len_links;
} data_links;

data_links getLinksFromFile(char*);

#endif
