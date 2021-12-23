/*
University of California Davis ECS 150: Operating System
By: Suryakiran Santhosh
Project 1: Unix Utilities
April 2, 2021
*/

#include <fcntl.h>
//#include <stdlib.h>
//#include <sys/types.h>
//#include <sys/uio.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 
NOTES:
argc : the number of things entered into the command line when running the program 
argv: holds the string values of all that was typed into the command line when running the program
*/

string read_from_file(int);

int main(int argc, char* argv[]) {
    int fd = -1;
    string decompressed_str = "";

    if (argc == 1) {
        string error = "wunzip: file1 [file2 ...]\n";
        write(STDOUT_FILENO, error.c_str(), error.length());
        exit(1);
    } else {
        for (int file = 1; file < argc; file++) {
            fd = open(argv[file], O_RDONLY);

            if (fd < 0) {
                string error = "wunzip: cannot open file\n";
                write(STDOUT_FILENO, error.c_str(), error.length());
                exit(1);
            }

            decompressed_str += read_from_file(fd);
            close(fd);
        }

        write(STDOUT_FILENO, decompressed_str.c_str(), decompressed_str.size());
    }

    return 0;
}

string read_from_file(int file_descriptor) {
    const int SIZE = 5;
    char buffer[SIZE];
    int ret;

    string output = "";
    int decompressed_num;
    char letter;

    while ((ret = read(file_descriptor, buffer, SIZE)) > 0) {
        letter = buffer[SIZE - 1];
        strncpy((char*)&decompressed_num, buffer, SIZE - 1);

        for (int repetition = 0; repetition < decompressed_num; repetition++) {
            output += letter;
        }
    }

    return output;
}