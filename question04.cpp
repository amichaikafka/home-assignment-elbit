//Question 4 - Filesystem & args

// Task: Implement the code as described in the main body, make sure to handle cases when the requested file is not found or the "files" directory doesn't exists and you have to create it
// Prefer modern solutions over classic C style solutions and keep in mind that this code should be able to run in other windows, linux and other platforms (hint: '/' and '\' in file paths)

/*Explanation:
* First i checked the amount of arguments (using argc) and iff is bigger then 1, if it bigger i checked if argv[1] is read or create.
* Iff those conditions took place:
* argv[1] =create:
*  i create/open the folder "files" and create/open the requested file ("argument2.txt") and write Hello from *argument3*.
* Note: i defined that if the user didnt pass the third or second argument i have created a file with no name (".txt")
* and if there is no argument3 i wrote ("Hello form" without name).
* Example:question04.exe create test1 : create "test1.text" with the content "Hello from".
* Example:question04.exe create : create ".text" with the content "Hello from"
* argv[1] =read:
* I checked if the file "files/argument2.txt" exsist if so i print to the console its content.
* Note:like in create if there is no argument2 the program will seek for "files/.txt" if exsist
* This program soppurt both linux and windows os.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <filesystem>
#if defined _WIN32
	#include <direct.h>
#else
	#include <bits/stdc++.h>
	#include <iostream>
	#include <sys/stat.h>
	#include <sys/types.h>
#endif
using namespace std;
using std::filesystem::exists;
using std::filesystem::is_directory;
int main(int argc, char** argv)
{
	string path;

	if (argc > 1)
	{

		char* read_or_create = argv[1];
		if (strcmp(read_or_create, "read") == 0)
		{
			path = argc > 2 ? argv[2] : "";
			path = "files/" + path + ".txt";
			if (!exists(path))
			{
				cout << "file does not exists\n";
				exit(0);
			}
			ifstream my_read_file(path);
			if (!my_read_file)
			{
				cout << my_read_file.exceptions();
			}
			string line;
			while (getline(my_read_file, line))
			{
				cout << line;
			}
			cout << endl;
			my_read_file.close();
		}
		else if (strcmp(read_or_create, "create") == 0)
		{
			// Creating a directory
#if defined _WIN32
			_mkdir("files");
#else

			mkdir("files", 0777);
#endif

			path = argc > 2 ? argv[2] : "";

			path = "files/" + path + ".txt";


			ofstream my_file(path);
			string hello = argc > 3 ? argv[3] : "";

			my_file << "Hello from " << hello;

			my_file.close();
		}
	}

	//If user passed "create" argument
	//		Create (or overwrite) a file named *argument2.txt*  with the text "Hello from *argument3*" in a folder named "files" under the current working directory
	//else if user passed "read" argument
	//		read a file named* argument2* from a folder named "files" under the current working directory and print it to the console

	//Execution example (assuming working directory c:\code): question04.exe create test1 Nir - should create the file c:\code\files\test1.txt with the content "Hello from Nir"
	//Execution example (assuming working directory c:\code): question04.exe read test1  - should print "Hello from Nir" in the console (assuming the previous command was executed)

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}