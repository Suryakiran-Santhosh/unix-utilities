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

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 
NOTES:
argc : the number of things entered into the command line when running the program 
argv: holds the string values of all that was typed into the command line when running the program
*/

void write_to_file(std::vector<string>, string);

int main(int argc, char* argv[]) {
    int fd;
    std::string search_term;

    // the edge case in which only the file name is passed
    if (argc == 1) {
        std::cout << "wgrep: searchterm [file ...]" << std::endl;
        exit(1);
    } else if (argc > 1) {
        search_term = string(argv[1]);
    }

    // the edge case in which only the executable name and search word are passed in
    if (argv[2] == NULL) {
        const int stdin_SIZE = 4096;
        char stdin_buffer[stdin_SIZE] = {};

        std::vector<std::string> std_lines;
        std::string std_line;

        int ret;

        // ask for user input
        while ((ret = (read(STDIN_FILENO, stdin_buffer, stdin_SIZE))) > 0) {
            for (int l = 0; l < stdin_SIZE; l++) {
                auto tmp = stdin_buffer[l];
                if (tmp != '\0') {
                    if (tmp != '\n') {
                        std_line.push_back(tmp);
                    } else {
                        std_line.push_back(tmp);
                        std_lines.push_back(std_line);
                        std_line.clear();
                        //std::cout << std_line << std::endl;
                    }
                } else {
                    break;
                }
            }
        }

        // edge case
        if (search_term == "" || search_term == " ") {
            return 0;
        }

        write_to_file(std_lines, search_term);
        /*
        // iterate through each line in lines and check if search_term is in the element
        for (string line : std_lines){

            // returns the first index of the first element of the matching substring 
            int position = line.find(search_term);
            
            // validate and output to console loop 
            if ((position != -1) && (search_term == line.substr(position, search_term.length()))){
                write(STDOUT_FILENO, line.c_str(), line.length());
            }            
        }
        */
        return 0;
    }

    // iterate through all the commands passed in
    for (int commands = 2; commands < argc; commands++) {
        // try to open the files that has been passed in
        fd = open(argv[commands], O_RDONLY);  // we are not going to write to this file

        // the case that the file cannot be opened
        if (fd == -1) {
            string error = "wgrep: cannot open file\n";
            write(STDOUT_FILENO, error.c_str(), error.size());
            exit(1);
        } else {
            // the case in which the file does exist and can be opened
            vector<string> lines;
            string line_in_file;

            const int SIZE = 1;
            char buffer[SIZE];
            int ret;

            // append all the lines in the file to vector
            while ((ret = read(fd, buffer, SIZE)) > 0) {
                for (int l = 0; l < SIZE; l++) {
                    if (buffer[l] != '\n') {
                        line_in_file.push_back(buffer[l]);
                    } else {
                        line_in_file.push_back(buffer[l]);
                        lines.push_back(line_in_file);
                        line_in_file.clear();
                    }
                }
            }

            write_to_file(lines, search_term);
        }
        close(fd);
    }

    return 0;
}

void write_to_file(std::vector<string> lines, string search_term) {
    // iterate through each line in lines and check if search_term is in the element
    for (string line : lines) {
        // returns the first index of the first element of the matching substring
        int position = line.find(search_term);

        // validate and output to console loop
        if ((position != -1) && (search_term == line.substr(position, search_term.length()))) {
            write(STDOUT_FILENO, line.c_str(), line.length());
        }
    }
}

/*
g++ -o wgrep wgrep.cpp -Wall -Werror
./test-wgrep.sh
./wgrep this ./in1.txt
cat tests/4.in | ./wgrep words
*/
