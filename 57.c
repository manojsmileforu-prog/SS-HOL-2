#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/sysinfo.h>

int main()
{
    long arg_max = sysconf(_SC_ARG_MAX);
    printf("maximum length of the arguments to the exec family of functions- %ld\n", arg_max);

    long child_max = sysconf(_SC_CHILD_MAX);
    printf("maximum number of simultaneous process per user id- %ld\n", child_max);

    long clk_ticks = sysconf(_SC_CLK_TCK);
    printf("number of clock ticks (jiffy) per second- %ld\n", clk_ticks);

    long open_max = sysconf(_SC_OPEN_MAX);
    printf("maximum number of open files- %ld\n", open_max);

    long page_size = sysconf(_SC_PAGESIZE);
    printf("size of a page- %ld\n", page_size);

    long num_pages = sysconf(_SC_PHYS_PAGES);
    printf("total number of pages in the physical memory- %ld\n", num_pages);

    long num_avl_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("number of currently available pages in the physical memory- %ld\n", num_avl_pages);

    return 0;
}
