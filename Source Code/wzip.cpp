/*
University of California Davis ECS 150: Operating System
By: Suryakiran Santhosh
Project 1: Unix Utilities
April 2, 2021
*/

#include <fcntl.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/uio.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <bitset>

using namespace std;


int main(int argc, char* argv[]){
    int fd;
    //const int SIZE = 1;
    //const int BITS = 32;

    // edge case in which only executable is given
    if (argc == 1){
        cout << "wzip: file1 [file2 ...]" << endl;
        exit(1);
    }

    string line;

    // only other edge case is when the file passed in cannot be opened 
    for (int i = 1; i < argc; i++){
        
        // try to open file
        fd = open(argv[i], O_RDONLY);
        
        // file cannot be opened
        if (fd == -1){
            cout << "wzip: cannot open file" << endl;
            exit(1);
        }

        // file is open read from file

        char buffer[1];
        int ret;

        while((ret = read(fd, buffer, 1)) > 0){
            //line.push_back(buffer[0]);
            line += buffer[0];
        }

        close(fd);
    }
    
    //cout << endl << line << endl << endl;
    
    // go through each l in lines and differentiate to get the occurrences
    // iterate through each letter in line
    for (int j = 0; j < int(line.length()); j++){                
        int occurrences = 1; // iterate and increment until I dont see the same letter

        // check if that j is 2 less than the last element in each_line
        // if j is within 2 of the end of each_line then there we will not be able to check if the last element is the same 
        // also will have to check if the current and next element is the same letter
        while((j < int(line.length() - 1)) && (line[j]  == line[j + 1])){                    
            occurrences++; // same letter

            // increment the for loop so that when the while loop breaks the next iteration of
            // the for loop will start from the next different letter
            j++; 
        }
        
        write(STDOUT_FILENO, &occurrences, 4);
        write(STDOUT_FILENO, &line[j], 1);
        
    }
    
    return 0;
}
