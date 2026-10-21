#include <stdio.h>
#include <unistd.h>

#define CPU_FREQ 310000000000; //3.1 GHz
unsigned long long rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start, end, cycles, time_ns;
    int i = 0;

    start = rdtsc();

    for(i = 0; i < 100; i++)
        getppid();

    end = rdtsc();

    cycles = end - start;

    time_ns = (cycles * 1000000000ULL) / CPU_FREQ;

    printf("Cycles taken for 100 getppid() calls: %llu cycles\n", cycles);
    printf("The time taken to execute 100 getppid() calls is: %llu ns\n", time_ns);

    return 0;
}
