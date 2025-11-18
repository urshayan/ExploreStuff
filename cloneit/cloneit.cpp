#include <iostream>
#include <fcntl.h>
#include <unistd.h>



int main(int argc , char *argv[]){

  ////// Should take only 3 arguements!!!
    if (argc != 3){
      std::cout << "USAGE: ./cloneit {src} {dest} \n";
      return 1;
    }
      // fd for src  
    int src = open(argv[1] , O_RDONLY);
    
    // error handling!
    if (src < 0){
      std::cout << "Error Opening SOURCE File! \n";
      return 1;
    }
  
    // fd for dest 
    int dest = open(argv[2] , O_WRONLY | O_CREAT | O_TRUNC , 0664);

    // error handling 
    if (dest < 0){
      std::cout << "Error Opening DEST File! \n";
      return 1;
    }

    //// 1MB enough space  for a fikleeee
    char buffer[1024];
    int bytesRead;

    // loop -> reads from source and writes to dest ... > 0 is bcs at 0 it indicates EOF 
    while((bytesRead = read(src,buffer,sizeof(buffer))) > 0){
      write(dest, buffer , bytesRead);
    }


    // respectively close file!!
    //
    close(src);
    close(dest);

  return 0;
}


