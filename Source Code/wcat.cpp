/*
University of California Davis ECS 150: Operating System
By: Suryakiran Santhosh
Project 1: Unix Utilities
April 2, 2021
*/

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <sys/uio.h>
#include <unistd.h>

#include <iostream>
#include <string>

using namespace std;

/* 
NOTES:
argc : the number of things entered into the command line when running the program 
argv: holds the string values of all that was typed into the command line when running the program
*/

int main(int argc, char *argv[])
{
    int fd = 0;

    if (argc == 1)
    {
        // check if the user passed in an argument
        // argc == 1 => the one thing that the user inputted was just the executable prompt
        fd = STDIN_FILENO; // already open
    }
    else
    {
        // case in which only one file is passed in when invoking the program
        for (int i = 1; i < argc; i++)
        {
            fd = open(argv[i], O_RDONLY);
            if (fd == -1)
            {
                // the case in which program is not able to open the file
                //write(STDOUT_FILENO, "wcat: cannot open file\n", sizeof("wcat: cannot open file\n"));
                string error = "wcat: cannot open file\n";
                write(STDOUT_FILENO, error.c_str(), error.length());
                // char not_found_msg[] = "wcat: cannot open file\n";
                // write(STDOUT_FILENO, not_found_msg, 24);
                // NOTE FOR FUTURE: USE c.str()
                return 1;
            }
            else
            {
                // the case that the file was able to be opened successfully
                // read from the opened file and print to console
                const int SIZE = 4096;
                char buffer[SIZE];
                int ret = 0;
                while ((ret = read(fd, buffer, SIZE)) > 0)
                {
                    write(STDOUT_FILENO, buffer, ret);
                }
            }
            close(fd);
        }
    }

    return 0;
}

/*
g++ -o wcat wcat.cpp -Wall -Werror
./test-wcat.sh
*/