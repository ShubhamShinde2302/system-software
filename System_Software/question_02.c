#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        printf("Process is running... PID = %d\n", getpid());
        sleep(1);
    }

    return 0;
}


/* ===================== OUTPUT =====================

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ gcc question_02.c -o question_02
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ./question_02 &
[1] 132
Process is running... PID = 132
Process is running... PID = 132
Process is running... PID = 132

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ jobs -l
[1]+   132 Running                 ./question_02 &

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ps -ef | grep question_02
root       132   126  0 10:32 pts/0    00:00:00 ./question_02

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cd /proc/132
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls
arch_status      environ            maps           pagemap      stat
attr             exe                mem            personality  statm
autogroup        fd                 mountinfo      projid_map   status
auxv             fdinfo             mounts         root         syscall
cgroup           gid_map            mountstats     sched        task
clear_refs       io                 net            schedstat    timens_offsets
cmdline          ksm_merging_pages  ns             sessionid    timerslack_ns
comm             ksm_stat           numa_maps      setgroups    uid_map
coredump_filter  limits             oom_adj        smaps        wchan
cpuset           loginuid           oom_score      smaps_rollup
cwd              map_files          oom_score_adj  stack

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat status
Name:	question_02
Umask:	0022
State:	S (sleeping)
Tgid:	132
Pid:	132
PPid:	126
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Threads:	1
VmPeak:	    2688 kB
VmSize:	    2688 kB
VmRSS:	    1792 kB
VmData:	     224 kB
VmStk:	     132 kB
VmExe:	       4 kB
VmLib:	    1748 kB
voluntary_ctxt_switches:	4
nonvoluntary_ctxt_switches:	2

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat cmdline
./question_02
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cat stat
132 (question_02) S 126 125 125 34816 125 4194304 109 0 0 0 0 0 0 0 20 0 1 0 2846 2752512 409 ...

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l exe
lrwxrwxrwx 1 shubham shubham 0 Sep 22 10:32 exe -> /home/shubham/Desktop/LINUX/question_02

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l cwd
lrwxrwxrwx 1 shubham shubham 0 Sep 22 10:32 cwd -> /home/shubham/Desktop/LINUX

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ ls -l fd
total 0
lr-x------ 1 shubham shubham 64 Sep 22 10:32 0 -> /dev/null
lrwx------ 1 shubham shubham 64 Sep 22 10:32 1 -> /dev/pts/0
lrwx------ 1 shubham shubham 64 Sep 22 10:32 2 -> /dev/pts/0

shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ kill 132
shubham@shubham-Nitro-ANV15-52:~/Desktop/LINUX$ cd ~/Desktop/LINUX
[1]+  Terminated              ./question_02


==================================================== */
