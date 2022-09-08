#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define OUT_DIR "/Users/trtp/Desktop/_screenshots"
#define	IN_DIR	"/Users/trtp/Desktop/"

using namespace std;

/**
 ** Execute and sort all screenshot... into _screenshot dir
 ** argv[1] path, argv[2] find, argv[3] destination
 ** ie: ./a.out . "screen" _screenshot
 **/

void	do_dir(char *in_dir, string find, char *out_dir)
{
		DIR				*dir;
		struct	dirent	*x;
		string			ptr;
		string			cmd;
		string			path;

		if ((dir = opendir(in_dir)) != NULL)
		{
				while ((x = readdir(dir)) != NULL)
				{
						ptr = (*x).d_name;
						if ((!ptr.compare(0, find.length(), find, 0, find.length())))
						{
								path = in_dir;
								path = path + "/" + ptr;
								cmd = "mv \"" + path + "\" " + out_dir;
								cout << "\033[32m->\033[0m " << cmd << endl;
								system(cmd.c_str());	
						}
				}
		}
		else
			cout << "\033[1;31mERROR \033[0m locating desktop dir );\n";
};

void	do_ac(int ac, char **av)
{
		char	cwd[256];
		char	outwd[256];
		
		//1//
		string	av1 = av[1];
		if (!av1.compare(0, 2, ".\0"))
				getcwd(cwd, sizeof(cwd));
		else
		{
				if (chdir(av[1]) < 0)
				{

						cout << "\033[1;31mERROR \033[0m\n";
						cout << "argv[1]: Dir path not found: " << av1 << " PLEASE navigate corretly or type . for current_Dir\n";
						return ;
				}
				else
				{
						getcwd(cwd, sizeof(cwd));
						cout << cwd << " ok\n";		
				}
		}
		//2//
		string av3 = av[3];
		if (!av3.compare(0, 2, ".\0"))
				getcwd(outwd, sizeof(outwd));
		else
		{
				if (chdir(av[3]) < 0)
				{
						cout << "argv[3]: Dir path not found: " << av[3] << endl;
						if (!mkdir(av[3], 0755))
						{
							if (chdir(av[3]) < 0)
					 		{
								cout << "\033[1;31mError Please Check (memory, sudo; problem with chdir)\033[0m\n";
								exit(101);
							}
							cout << "\033[32mCreating\033[0m " << av[3]  << " @ " << getcwd(outwd, sizeof(outwd)) << endl;
						}
				}
				else
					getcwd(outwd, sizeof(outwd));
		}
		do_dir(cwd, av[2], outwd);
};

int main(int ac, char **av)
{
		if (ac > 1)
				do_ac(ac, av);
		else
		{
				if (chdir((char *)OUT_DIR) < 0)
				{
						if (!mkdir(OUT_DIR, 0755))
							cout << "\033[32mCreating\033[0m " << OUT_DIR  << endl; 
						else
						{
								cout << "\033[1;31mERROR \033[0m Please check code MACRO 'OUT_DIR'\n";
								exit(1);
						}	
				}
				do_dir((char *)IN_DIR, "Screenshot", (char *)OUT_DIR);
		}

		cout << "#  \033[1;31mTITORRITO-PRODUCTIONS\033[0m CODE/FILM  #" << endl; 
		cout << "# --------------------------------- #" << endl; 
		cout << "# |           |        |    ___   | #" << endl; 
		cout << "# |___     ___|   []   |   |   |  | #" << endl;
		cout << "#     |   |            |   |___|  | #" << endl;
		cout << "#     |   |     _ _ ___|   _______| #" << endl;
		cout << "#     |   |     |  \\   |   |        #" << endl;
		cout << "#     |   |     |   \\  |   |  c++   #" << endl;
		cout << "#     |   |     |    \\ |   |  vim   #" << endl;
		cout << "#     |   |     |     \\]   |  awk   #" << endl;
		cout << "#    -----------------------        #" << endl;
		cout << "#    github.com/vctrubio 42lisboa   #" << endl;
		return (1);
};
