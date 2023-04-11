/*
*
*
William Beach
CDA4102 - Project 3 - Cache Memory in C
*
*
*/

//Cache = array of sets

//m = bits per address --> i.e. 32 bit, 64 bit, etc...
//c = total cache size --> c = s * e * b
//e = lines per set    --> 2-way set associative (2 lines per set), n-way set associative (n lines per set)
//b = bytes of data block per line --> m / 8 bits = bytes per data block in each line
//s = cache sets       --> c / (e * b)
//t = tag bits         --> m - (bb + sb)
//sb = set index bits   --> logbase2(s)
//bb = block offset bits --> logbase2(b)

//command-line argument format:

/*

total cache size     block size        associativity  
-c <cache size>   -b <block size>   -e <number of lines>   

type: unified/splitl/splitd     write-back/write-through    write allocate/write no allocate
      -t [u/sl/sd]                   -w [wb/wt]                      -a [wa/wna]

*/

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

struct simulator{
    unsigned int cache_size;
    unsigned int block_size;
    unsigned int num_lines;
    char *cache_type;
    char *write_style;
    char *allocation;
};

void cacheType(char *arr);
void writeType(char *arr);
void allocationType(char *arr);

int main(int argc, char *argv[]){
    struct simulator cache;
    int option;
    while ((option = getopt(argc, argv, "c:b:e:t:w:a:")) != -1){
        switch (option){
            case 'c':
                cache.cache_size = (unsigned int)(atoi(optarg));
                printf("cache_size: %i bytes\n", cache.cache_size);
                break;
            case 'b':
                cache.block_size = (unsigned int)(atoi(optarg));
                printf("block_size: %i bytes\n", cache.block_size);
                break;
            case 'e':
                cache.num_lines = (unsigned int)(atoi(optarg));
                printf("lines per block: %i\n", cache.num_lines);
                break;
            case 't':
                cache.cache_type = optarg;
                cacheType(cache.cache_type);
                break;
            case 'w':
                cache.write_style = optarg;
                writeType(cache.write_style);
                break;
            case 'a':
                cache.allocation = optarg;
                allocationType(cache.allocation);
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
  } else if (strcmp(arr, "sl") == 0){
    printf("split-l cache selected\n");
  } else if (strcmp(arr, "sd") == 0){
    printf("split-d cache selected\n");
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
        printf("write no allocate selected\n");
    } else{
        printf("invalid allocation selected\n");
        printf("aborting program\n");
        exit(1);
    }
}


