#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

int main()
{
    struct rlimit old_limit, new_limit, limit;

    getrlimit(RLIMIT_NOFILE, &old_limit);
    printf("Before setting limit: \n");
    printf("Current soft limit for number of open files: %lld\n", (long long)old_limit.rlim_cur);
    printf("Current hard limit for number of open files: %lld\n", (long long)old_limit.rlim_max);

    new_limit.rlim_cur = 512;
    new_limit.rlim_max = old_limit.rlim_max;

    printf("Attempting to set new limit\n");
    setrlimit(RLIMIT_NOFILE, &new_limit);

    printf("After setting new limit, limits are: \n");
    getrlimit(RLIMIT_NOFILE, &limit);

    printf("Current soft limit for number of open files: %lld\n", (long long)limit.rlim_cur);
    printf("Current hard limit for number of open files: %lld\n", (long long)limit.rlim_max);

    return 0;

}
