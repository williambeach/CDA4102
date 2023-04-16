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
-c <cache size>                     -b <block size>              -e <number of lines>   //up to 4-way

type: unified/split i and d     write-back/write-through     write allocate/write no allocate
    -t [u/sid]                        -w [wb/wt]                     -a [wa/wna]

example: -c 1024 -b 4 -e 1 -t u -w wt -a wna

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

struct line{
  unsigned int valid_bit;
  unsigned int dirty_bit;
  char tag[100];
  char set[100];
  char offset[100];
};

struct set_direct_mapped{
  struct line line1;
};

struct set_2_way{
  struct line line1;
  struct line line2;
};

struct set_3_way{
  struct line line1;
  struct line line2;
  struct line line3;
};

struct set_4_way{
  struct line line1;
  struct line line2;
  struct line line3;
  struct line line4;
};



FILE *trace_file;

void parse_command_line(int argc, char *argv[]);
void cacheType(char *arr);
void writeType(char *arr);
void allocationType(char *arr);
void initialize_cache(struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4);
void parse_trace_line(struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4);
void hex_to_binary(char hex[], char *binary_address);
void binary_to_cache_bits(char *binary_address, char *reference, struct set_direct_mapped set_array1[], struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4, char tag[], char index[], char offset[], int *hits, int *misses, int *memory_accesses);
void uni_write_through_no_allocate(char tag[], char index[], char offset[], char *reference, struct set_direct_mapped set_array1[], struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4, int *hits, int *misses, int *memory_accesses);
int binary_to_decimal(char index[]);



int main(int argc, char *argv[]){
  int i;
  parse_command_line(argc, argv);
  cache_settings.cache_sets = (cache_settings.cache_size / (cache_settings.num_lines * cache_settings.block_size));
  cache_settings.set_index_bits = log2(cache_settings.cache_sets);
  cache_settings.block_offset_bits = log2(cache_settings.block_size);
  cache_settings.tag_bits = 32 - cache_settings.block_offset_bits - cache_settings.set_index_bits;
  struct set_direct_mapped set_array1[cache_settings.cache_sets];
  struct set_direct_mapped *ptr1 = set_array1;
  struct set_2_way set_array2[cache_settings.cache_sets];
  struct set_2_way *ptr2 = set_array2;
  struct set_3_way set_array3[cache_settings.cache_sets];
  struct set_3_way *ptr3 = set_array3;
  struct set_4_way set_array4[cache_settings.cache_sets];
  struct set_4_way *ptr4 = set_array4;
  initialize_cache(ptr1, ptr2, ptr3, ptr4);
  parse_trace_line(ptr1, ptr2, ptr3, ptr4);
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
}

void initialize_cache(struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4){ 
  int i;
  if (strcmp(cache_settings.cache_type, "u") == 0){
    if (cache_settings.num_lines == 1){
      for (i=0; i<cache_settings.cache_sets;i++){
        ptr1[i].line1.valid_bit = 0;
      }
    } else if (cache_settings.num_lines == 2){
        for (i=0; i<cache_settings.cache_sets;i++){
          ptr2[i].line1.valid_bit = 0;
          ptr2[i].line2.valid_bit = 0;
        }
    } else if (cache_settings.num_lines == 3){
        for (i=0; i<cache_settings.cache_sets;i++){
          ptr3[i].line1.valid_bit = 0;
          ptr3[i].line2.valid_bit = 0;
          ptr3[i].line3.valid_bit = 0;
        }
    } else if (cache_settings.num_lines == 4){
        for (i=0; i<cache_settings.cache_sets;i++){
          ptr4[i].line1.valid_bit = 0;
          ptr4[i].line2.valid_bit = 0;
          ptr4[i].line3.valid_bit = 0;
          ptr4[i].line4.valid_bit = 0;
        }
    } else {
      printf("associativity > 4\n");
      printf("exiting program\n");
      exit(1);
    }
  } else{
    //initialize split i-d cache with valid bit and dirty bit
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

void parse_trace_line(struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4){
  char tag[cache_settings.tag_bits];
  char index[cache_settings.set_index_bits];
  char offset[cache_settings.block_offset_bits];
  double hit_rate;
  double miss_rate;
  int *phits;
  int *pmisses;
  int *pmemory_accesses;
  int hits = 0;
  int misses = 0;
  int memory_accesses = 0;
  phits = &hits;
  pmisses = &misses;
  pmemory_accesses = &memory_accesses;
  char binary_address[50] = {'\0'};
  char copy_of_binary[50] = {'0', '0', '0', '0', '0', '0', '0', '0'};
  char buffer[50];
  char reference[50];
  char hex[50];
  int length;
  trace_file = fopen("trace.txt", "r");
  while (fgets(buffer, sizeof(buffer), trace_file) != NULL){
    if (buffer[strlen(buffer) - 1] == '\n'){
      buffer[strlen(buffer) - 1] = '\0';
    }
    strncpy(reference, buffer, 1);
    strncpy(hex, buffer + 2, strlen(buffer) - 1);
    hex_to_binary(hex, binary_address);
    if ((int)strlen(binary_address) == 24){
      strcat(copy_of_binary, binary_address);
      memset(binary_address, '\0', sizeof binary_address);
      strcpy(binary_address, copy_of_binary);
    }
    binary_to_cache_bits(binary_address, reference, ptr1, ptr2, ptr3, ptr4, tag, index, offset, phits, pmisses, pmemory_accesses);
    memset(binary_address, '\0', sizeof binary_address);
    memset(copy_of_binary, '\0', sizeof copy_of_binary);
    strcpy(copy_of_binary, "00000000");
  }
  printf("Hits: %d\n", *phits);
  printf("Misses: %d\n", *pmisses);
  printf("Memory Accesses: %d\n", *pmemory_accesses);
  printf("Hit Rate: %.2lf\n", (double)*phits / (*phits + *pmisses));
  printf("Miss Rate: %.2lf\n", 1.0 - ((double)*phits / (*phits + *pmisses)));
  fclose(trace_file);
}

void hex_to_binary(char hex[], char *binary_address){
  char temp;
  char *target;
  int index;
  int i;
  char *hex_to_binary[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
  char hex_numbers[] = "0123456789abcdef";
  for (i=0;i<strlen(hex);i++){
    temp = hex[i];
    target = strchr(hex_numbers, temp);
    index = (int)(target - hex_numbers);
    strcat(binary_address, hex_to_binary[index]);
  }
}

void binary_to_cache_bits(char *binary_address, char *reference, struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4, char tag[], char index[], char offset[], int *hits, int *misses, int *memory_accesses){
  char copy[100];
  strcpy(copy, binary_address);
  strncpy(tag, copy, cache_settings.tag_bits);
  strncpy(index, copy + cache_settings.tag_bits, strlen(copy) - 1 - cache_settings.block_offset_bits - cache_settings.tag_bits);
  strncpy(offset, copy + cache_settings.tag_bits + cache_settings.set_index_bits, strlen(copy) - cache_settings.tag_bits - cache_settings.set_index_bits);
  if ((strcmp(cache_settings.cache_type, "u") == 0) && (strcmp(cache_settings.write_style, "wt") == 0) && (strcmp(cache_settings.allocation, "wna") == 0)){
    uni_write_through_no_allocate(tag, index, offset, reference, ptr1, ptr2, ptr3, ptr4, hits, misses, memory_accesses);
  }
}

void uni_write_through_no_allocate(char tag[], char index[], char offset[], char *reference, struct set_direct_mapped *ptr1, struct set_2_way *ptr2, struct set_3_way *ptr3, struct set_4_way *ptr4, int *hits, int *misses, int *memory_accesses){
  int numeric_reference;
  numeric_reference = atoi(reference);
  int decimal_set_index;
  decimal_set_index = binary_to_decimal(index);
  if (cache_settings.num_lines == 1){
    if (ptr1[decimal_set_index].line1.valid_bit == 0){
      (*misses)++;
      (*memory_accesses)++;
      strcpy(ptr1[decimal_set_index].line1.tag, tag);
      ptr1[decimal_set_index].line1.valid_bit = 1;
    } else if (ptr1[decimal_set_index].line1.valid_bit == 1 && (numeric_reference == 0 || numeric_reference == 2)){
        if (strcmp(ptr1[decimal_set_index].line1.tag, tag) == 0){
          (*hits)++;
        } else{
          (*misses)++;
          (*memory_accesses)++;
          memset(ptr1[decimal_set_index].line1.tag, '\0', sizeof ptr1[decimal_set_index].line1.tag);
          strcpy(ptr1[decimal_set_index].line1.tag, tag);
        }
    } else if (ptr1[decimal_set_index].line1.valid_bit == 1 && numeric_reference == 1){
      if (strcmp(ptr1[decimal_set_index].line1.tag, tag) == 0){
        (*hits)++;
        (*memory_accesses)++;
      } else{
        (misses)++;
        (*memory_accesses)++;
      }
    }
    
  }
}

int binary_to_decimal(char index[]){
  int sum = 0;
  int i;
  for (i=0; i<strlen(index); i++){
    if (index[i] == '1'){
      sum += (int)pow(2, strlen(index) - 1 - i); 
    }
  }
  return sum;
}