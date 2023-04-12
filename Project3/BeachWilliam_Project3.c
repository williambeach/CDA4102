/*
*
William Beach
CDA4102 - Project 3 - Cache Memory in C
*
*/

//Cache = array of sets

//m = bits per address --> i.e. 32 bit, 64 bit, etc...
//c = total cache size --> c = s * e * b
//e = lines per set --> direct-mapped (1 line per set), 2-way set associative (2 lines per set), n-way set associative (n lines per set)
//b = bytes of data block per line --> m / 8 bits = bytes per data block in each line
//s = cache sets       --> c / (e * b)
//t = tag bits         --> m - (bb + sb)
//sb = set index bits   --> logbase2(s)
//bb = block offset bits --> logbase2(b)

//0 = data load
//1 = data store
//2 = instruction load

//unified cache contains both instructions and data

//command-line argument format:

/*

total cache size                       block size                    associativity  
-c <cache size>                     -b <block size>              -e <number of lines>   

type: unified/split l and d     write-back/write-through     write allocate/write no allocate
    -t [u/sld]                        -w [wb/wt]                     -a [wa/wna]

*/

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

struct settings{
  unsigned int cache_size;
  unsigned int block_size;
  unsigned int num_lines;
  char *cache_type;
  char *write_style;
  char *allocation;
}cache_settings;

struct address{
  char *tag;
  char *set;
  char *offset;
}cache_address;

FILE *trace_file;


void cacheType(char *arr);
void writeType(char *arr);
void allocationType(char *arr);
void parse_trace_file();
void hex_to_binary(char *hex);




int main(int argc, char *argv[]){
  int option;
  while ((option = getopt(argc, argv, "c:b:e:t:w:a:")) != -1){
      switch (option){
          case 'c':
              cache_settings.cache_size = (unsigned int)(atoi(optarg));
              printf("cache_size: %i bytes\n", cache_settings.cache_size);
              break;
          case 'b':
              cache_settings.block_size = (unsigned int)(atoi(optarg));
              printf("block_size: %i bytes\n", cache_settings.block_size);
              break;
          case 'e':
              cache_settings.num_lines = (unsigned int)(atoi(optarg));
              printf("lines per block: %i\n", cache_settings.num_lines);
              break;
          case 't':
              cache_settings.cache_type = optarg;
              cacheType(cache_settings.cache_type);
              break;
          case 'w':
              cache_settings.write_style = optarg;
              writeType(cache_settings.write_style);
              break;
          case 'a':
              cache_settings.allocation = optarg;
              allocationType(cache_settings.allocation);
              break;
          default:
              printf("invalid option\n");
              printf("aborting program");
              exit(1);
      }
    }
    //
}

void cacheType(char *arr){
  if (strcmp(arr, "u") == 0){
    printf("unified cache selected\n");
  } else if (strcmp(arr, "sld") == 0){
    printf("split-ld cache selected\n");
  } else{
    printf("invalid cache type selected\n");
    printf("aborting program\n");
    exit(1);
  }
}
      
void writeType(char *arr){
  if (strcmp(arr, "wb") == 0){
    printf("write-back selected\n");
  } else if (strcmp(arr, "wt") == 0){
    printf("write-through selected\n");
  } else{
    printf("invalid write type selected\n");
    printf("aborting program\n");
    exit(1);
  }
}

void allocationType(char *arr){
    if (strcmp(arr, "wa") == 0){
        printf("write allocate selected\n");
    } else if (strcmp(arr, "wna") == 0){
        printf("write no-allocate selected\n");
    } else{
        printf("invalid allocation selected\n");
        printf("aborting program\n");
        exit(1);
    }
}

void parse_trace_file(){
  char buffer[100];
  char *reference;
  char *hex;
  int length;
  trace_file = fopen("trace.txt", "r");
  while (fgets(buffer, sizeof(buffer), trace_file) != NULL){
    reference = strtok(buffer, " ");
    hex = strtok(NULL, " ");
    
    
    
  }

}

void hex_to_binary(char *hex){
  const char hex_to_binary[15] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", 
  "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
  const char hex_numbers = "0123456789abcdef";

}
