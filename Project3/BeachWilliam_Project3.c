/*
*
*
William Beach
CDA4102 - Project 3 - Cache Memory in C
*
*
*/

/*Cache = array of sets*/

//m = bits per address --> i.e. 32 bit, 64 bit, etc...
//c = total cache size --> s * e * b
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
      -t [u/sl/sd]                   -w [wb/wt]                      a [wa/wna]

*/

#include <stdio.h>
#include <string.h>
#include <getopt.h>



int main(int argc, char *argv[]){
    int option;
    while ((option = getopt(argc, argv, "c:b:e:t:w:a:")) != -1){

    }
    
}



