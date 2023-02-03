#include <iostream>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

void	listFiles(const char *dirname)
{	
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(dirname);
	if (dir == NULL)
	{
		cerr << "ERROR in opening DIR " << dirname << endl;
		return ;
	}
	entity = readdir(dir);
	while (entity != NULL)
	{
	   if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0) {
			entity = readdir(dir);
            continue;
        }

			printf("-> %hhd - %s\n", entity->d_type, entity->d_name);
			if (entity->d_type == DT_DIR)
			{
				char path[100] = {0};
				strcat(path, dirname);
				strcat(path, "/");
				strcat(path, entity->d_name);
			//	printf("LISTING :%s\n", path);
				listFiles(path);
			}
			entity = readdir(dir);
	}
}


int main(int ac, char **av)
{
	DIR	*dir;
	DIR	*ptr_main;
	DIR	*ptr_prev;

	if (ac != 3)
	{
			cout << "./pg in_dir out_dir\n";
			return (1);
	}
	listFiles(av[1]);




	closedir(dir);
}
