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
//C = total cache size --> S * E * B
//E = lines per set    --> 2-way set associative (2 lines per set), n-way set associative (n lines per set)
//B = Bytes of data block per line --> m / 8 bits = Bytes per data block in each line
//S = Cache sets       --> C / (E * B)
//t = tag bits         --> m - (b + s)
//s = set index bits   --> logbase2(S)
//b = block offset bits --> logbase2(B)

/*command-line argument format:
--total cache size, --block size, --associativity, -unified/-splitl/-splitd, -write-back/write-through, -write allocate/write no allocate
<--C>  <-B> <bytes of block data> <-E> <number of lines> <-U/-SL/-SD> <-WB/-WT> <-WA/-WNA>

--C=1024 --B=4 --E=1 [-U]

*/

#include <stdio.h>
#include <string.h>



int main(int argc, char *argv[]){
    
    
}



