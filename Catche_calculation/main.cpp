//REFERENCE : http://www.cplusplus.com/forum/general/35557/

//compilation instructions
//g++ -std=c++11 main.cpp -o output
//./output

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdint> 

using namespace std;

clock_t whack_cache(const int sz)
{
    char* buf = new char[sz];

    clock_t start = clock();

    for (int64_t i = 0; i < 64 * 1024 * 1024; i++)
        ++buf[(i * 64) % sz]; // writing in increments hopefully means we write to a new cache-line every time

    clock_t elapsed = clock() - start;

    delete [] buf;
    return elapsed;
}

int main()
{
    std::cout << "writing timing results to \"results.csv\"" << std::endl;

    FILE* f = fopen("results.csv", "w");
    if (!f)
        return 1;

    for (int sz = 1024; sz <= 16 * 1024 * 1024; sz <<= 1)
    {
        fprintf(f, "%d, %lu\n", sz / 1024, whack_cache(sz));
        std::cout << ".";
        fflush(stdout);
    }

    fclose(f);

    std::cout << "done" << std::endl;
    return 0;
}
/* EXPLANATION :
The following psedocode is being executed :
1. Initialize an array of sizes (this is what we empirically check to find the catche limit)
sizes = [1k, 4k, 256K, ...]
2. Loop through the proposed sizes, creating arrays corresponding to those sizes
We are asking the question: Does my catche size lie between the sizes before and after current size in the list?

foreach size in sizes 
    create array of `size`
3. We check the time it takes for the program to access chunks of memory from the array we define according to the sizes in the list
    start timer
    for i = 0 to n // just keep accessing array
4. We try to access a particular location in the array 
        arr[(i * 16) % arr.length]++ // i * 16 supposed to modify every cache line ... see link
    record/print time
5. After running the code, the following is observed in the csv file:
1       687927
2       666515
4       656682
8       643137
16      645672
32      647209
64      646452
128     644158
256     646450
512     649640
1024    681884
2048    653158
4096    658866
8192    712274
16384   756725

On LHS we have the size and on the RHS we have the time taken according to clock()
Huge jump is observed from 512 to 1024 and 4096 to 8192
These jumps corresponds to the catche size ranges.
*/