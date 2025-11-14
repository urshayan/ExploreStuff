#include <iostream>
#include <fcntl.h>
#include <unistd.h>

// ANSI COLORS!
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


// >0 ---> Number Of Bytes Actually Read!
// 0  ---> END OF File
// -1 ---> ERROR!



int main(int argc , char *argv[])
{
      //system(""); ------>  Enable for Windows!!!
      
      char buffer[1024]; // DATA/BUFFER! --- 1024 bytes --big enough!
      int bytesRead;

    /// If no arguement is given prints out the usage of the programme!
    /// 2 in the write(2,....) is for stderr!
      if (argc < 2){
        std::cout << RED << "USAGE: " << RESET << GREEN << "./meow {filename}" << RESET << "\n";
        exit(1);
      }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1){
      std::cout << RED << "Error Opening File!" << RESET << "\n";
      exit(1);
    } // Erroor Opening File!!!
    

    while ((bytesRead = read(fd ,buffer, sizeof(buffer))) > 0){
      // write to stdout  
      write(1, buffer,bytesRead); 
    }

    if (bytesRead == -1){
          std::cout << RED << "Error Reading File!" << RESET << "\n";
    }
  

    close(fd);
    return 0;
}
