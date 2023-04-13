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

type: unified/split i and d     write-back/write-through     write allocate/write no allocate
    -t [u/sid]                        -w [wb/wt]                     -a [wa/wna]

*/

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

struct settings{
  unsigned int cache_size;
  unsigned int block_size;
  unsigned int num_lines;
  char *cache_type;
  char *write_style;
  char *allocation;
  int cache_sets;
  int set_index_bits;
  int block_offset_bits;
  int tag_bits;
}cache_settings;


struct address{
  char *tag;
  char *set;
  char *offset;
};

struct line{
  unsigned int valid_bit;
  unsigned int dirty_bit;
  struct address cache_address;
};

struct set{
  struct line line_array[1];
};

FILE *trace_file;

void parse_command_line(int argc, char *argv[]);
void cacheType(char *arr);
void writeType(char *arr);
void allocationType(char *arr);
void initialize_cache();
void parse_trace_line();
void hex_to_binary(char *hex, char *binary_address);


int main(int argc, char *argv[]){
  parse_command_line(argc, argv);
  initialize_cache();
  parse_trace_line();
  return 0;
}

void parse_command_line(int argc, char *argv[]){
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
    //calculate cache sets
  cache_settings.cache_sets = cache_settings.cache_size / (cache_settings.num_lines * cache_settings.block_size);
  cache_settings.set_index_bits = log2(cache_settings.cache_sets);
  cache_settings.block_offset_bits = log2(cache_settings.block_size);
  cache_settings.tag_bits = 32 - cache_settings.block_offset_bits - cache_settings.set_index_bits;
}

void initialize_cache(){
  if (cache_settings.cache_type = "u"){
    struct set set_array[cache_settings.cache_sets];
  } 
}



void cacheType(char *arr){
  if (strcmp(arr, "u") == 0){
    printf("unified cache selected\n");
  } else if (strcmp(arr, "sld") == 0){
    printf("split-id cache selected\n");
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

void parse_trace_line(){
  char binary_address[50] = {'\0'};
  char buffer[50];
  char *reference;
  char *hex;
  int length;
  trace_file = fopen("trace.txt", "r");
  while (fgets(buffer, sizeof(buffer), trace_file) != NULL){
    reference = strtok(buffer, " ");
    hex = strtok(NULL, " ");
    hex_to_binary(hex, binary_address);
    printf("%s\n", binary_address);
    memset(binary_address, '\0', sizeof binary_address);
  }
}

void hex_to_binary(char *hex, char *binary_address){
  char temp;
  char *target;
  int index;
  int i;
  int address_bits = (strlen(hex) - 1) * 4;
  char *hex_to_binary[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
  char hex_numbers[] = "0123456789abcdef";
  for (i=0;i<strlen(hex)-1;i++){
    temp = hex[i];
    target = strchr(hex_numbers, temp);
    index = (int)(target - hex_numbers);
    strcat(binary_address, hex_to_binary[index]);
  }
}