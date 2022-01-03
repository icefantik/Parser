#include "flink.h"

data_links getLinksFromFile(char *path_file)
{
	data_links dt_links;
	FILE *file = fopen(path_file, "r");
	for (dt_links.len_links = 0; fgets(dt_links.links[dt_links.len_links], sizeof(dt_links.links[dt_links.len_links]), file); ++dt_links.len_links);
	return dt_links;
}
