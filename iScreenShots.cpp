#include "Headers.hpp"

#define OUT_DIR "/Users/trtp/Desktop/_screenshots"
#define	IN_DIR	"/Users/trtp/Desktop/"

using namespace std;


/**
 ** Execute and sort all screenshot... into _screenshot dir
**/


int main()
{
	DIR				*dir;
	struct	dirent	*x;
	string			ptr;
	string			cmd;
	string			path;

	if ((dir = opendir(IN_DIR)) != NULL)
	{
			//cout << "HI\n";
			while ((x = readdir(dir)) != NULL)
			{
				ptr = (*x).d_name;
				if ((!ptr.compare(0,9,"Screenshot", 0, 9)))
				{
						//cout << "YES\n";
						//cout << ptr << endl;
						path = IN_DIR + ptr;
						cmd = "mv \"" + path + "\" " + OUT_DIR;
						cout << cmd << endl;
						system(cmd.c_str());	
				}
			}
	};
};
