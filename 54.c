#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

void print_limit(int resource, const char* resource_name) {
    struct rlimit limit;

    getrlimit(resource, &limit);

    printf("Resource name: %s\n", resource_name);

    printf("Soft limit: ");
    if (limit.rlim_cur == RLIM_INFINITY) 
        printf("Unlimited\n");
    else 
        printf("%lld\n", (long long)limit.rlim_cur);

    printf("Hard limit: ");
    if (limit.rlim_max == RLIM_INFINITY) 
        printf("Unlimited\n");
    else 
        printf("%lld\n", (long long)limit.rlim_max);
    
    printf("\n");
}

int main() {
    printf("System resource limits: \n");
    print_limit(RLIMIT_CPU, "Max CPU Time (s): ");
    print_limit(RLIMIT_FSIZE, "Max File size (bytes) : ");
    print_limit(RLIMIT_DATA, "Max Data Segment Size: ");
    print_limit(RLIMIT_STACK, "Max Stack size: ");
    print_limit(RLIMIT_CORE, "Max Core file size: ");
    print_limit(RLIMIT_NPROC, "Max number of Processes: ");
    print_limit(RLIMIT_NOFILE, "Max number of open file: ");
    print_limit(RLIMIT_AS, "Max Address Space (bytes): ");

    return 0;
}
