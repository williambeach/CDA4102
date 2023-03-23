/*
*
William Beach 
CDA4102 - Project 2 - Pipelining
03/20/2023
*
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>


int main() {
  
  //declare and initialize 2 pipes
  int pipe1[2];
  int pipe2[2];
  pipe(pipe1);
  pipe(pipe2);

  //declare for loop counter and file input/output pointers
  int i;
  FILE *inptr, *outptr;
  
  
  //create child 1
  int pid1 = fork();
  //if we are in first child process
  if (pid1 == 0){
    char buffer[500];
    
    
    //close pipeline terminals not in use
    close(pipe1[1]);
    close(pipe2[0]);
    
    
    //read from pipeline 1 line of input from parent and then close pipeline terminal
    read(pipe1[0], buffer, sizeof(buffer));
    close(pipe1[0]);
    
    //capitalize lowercase chars and lowercase uppercase chars
    for (i=0;i<strlen(buffer);i++){
      if (isupper(buffer[i])){
        buffer[i] = tolower(buffer[i]);
      } else{
        buffer[i] = toupper(buffer[i]);
      }
    }
    
    //child 1 process writes to pipeline 2 write terminal and then closes it
    write(pipe2[1], buffer, strlen(buffer));
    close(pipe2[1]);

    
  } else {
  //create child 2
  int pid2 = fork();
  //if we are in second child process
  if (pid2 == 0){
    char buffer[500];
    
    //close pipeline terminals not in use
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
    
    //read from pipeline 2 a string of input from child 1 into cstring variable
    read(pipe2[0], buffer, sizeof(buffer));
    
    //create and open text file
    outptr = fopen("output.txt", "w");
    
    //input entire string into text file
    fputs(buffer, outptr);
    
    //close text file and close read end of pipeline 2
    fclose(outptr);
    close(pipe2[0]);
  
  } else {
      //parent process
    
      //close unused terminals of both pipelines
      close(pipe1[0]);
      close(pipe2[1]);
      close(pipe2[0]);

      //open text file and declare cstring array
      inptr = fopen("input.txt", "r");
      char line[500];

      //read each line of input file into write terminal of pipeline 1 until eof  
      while (fgets(line, sizeof(line), inptr) != NULL){
        write(pipe1[1], line, strlen(line));
    }

      //close file pointer and write terminal of pipeline 1
      fclose(inptr);
      close(pipe1[1]);
  
      //wait for child processes to finish before returning from main
      waitpid(pid1, NULL, 0);
      waitpid(pid2, NULL, 0);
    }
  }
  
  return 0;
}