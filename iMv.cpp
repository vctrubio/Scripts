#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

string	validateStr(string str)
{
		if (str[str.length()-1] == '/')
				str = str.substr(0, str.length()-1);
		return (str);
}

void	cpy_file(string src, string dst, DIR *checker)
{
	string		cat;

	cat = dst + src;
	if (access(cat.c_str(), F_OK) != 0) //can't get the bloody thing to work if it exist.
	{
		filesystem::copy(src, dst);
		cout << "\x1b[32m" << "cpy: " << "\x1b[0m" << src << endl;
	}
	else
		cout << "File existed: " << src << endl;
}
void	itr_dir(string dir_in, string dir_out)
{
	struct dirent	*dir;
	DIR				*ptr;
	DIR				*dir_check;

	ptr = opendir(dir_in.c_str());
	dir_check = opendir(dir_out.c_str());
	if (ptr)
	{
		cout << "ITR: " << dir_in << endl;
		while ( (dir = readdir(ptr)) != NULL)
		{
			string path = "";
			if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
					continue;
			if (dir->d_type == DT_DIR)
			{
				dir_in = validateStr(dir_in);
				string strPath = dir_in + "/" + dir->d_name;
				itr_dir(strPath, dir_out);
			}
			else
			{
				dir_in = validateStr(dir_in);
				string strPath = dir_in + "/" + dir->d_name;
				cpy_file(strPath, dir_out, dir_check);	
			}
		}
		closedir(ptr);
	}
	closedir(dir_check);
}


int main(int ac, char **av)
{
	DIR	*dir;

	if (ac != 3)
	{
			cout << "./pg in_dir out_dir\n";
			return (1);
	}
	dir = opendir(av[2]);
	if (!dir)
			const int dir_err = mkdir(av[2], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	else
			closedir(dir);
	itr_dir(av[1], av[2]);
	cout << "COMPLETED.\n";

	return (22);

}
