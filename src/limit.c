#include <sys/resource.h>
#include <sys/time.h>

int setResLimit(int time_limit, int memory_limit, int java)
{
    struct rlimit rl;

    rl.rlim_cur = time_limit / 1000 + 1;
    if (time_limit % 1000 > 800)
        rl.rlim_cur += 1;
    rl.rlim_max = rl.rlim_cur + 1;
    if (setrlimit(RLIMIT_CPU, &rl))
        return -1;

    rl.rlim_cur = memory_limit * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_DATA, &rl))
        return -1;

    //Support java
    if (java == 0)
    {
        rl.rlim_cur = memory_limit * 1024 * 2;
        rl.rlim_max = rl.rlim_cur + 1024;
        if (setrlimit(RLIMIT_AS, &rl))
            return -1;
    }

    rl.rlim_cur = 256 * 1024 * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_STACK, &rl))
        return -1;

    return 0;
}
