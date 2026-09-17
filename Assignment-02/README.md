# Assignment 2 — Infinite Loop & `/proc` Process Information

## Aim

To create an infinite-loop process in C, run it in the background, find its Process ID (PID), and examine process information using the Linux `/proc` filesystem.

---

## 1. Create an Infinite Loop Program

Create a file named `infinite.c`:

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        printf("Process is running...\n");
        sleep(1);
    }

    return 0;
}

---
```
Continue your `README.md` from there with this:

````markdown
---

## 2. Compile the Program

Compile the program using:

```bash
gcc infinite.c -o infinite
````

---

## 3. Run the Program in the Background

Run the program in the background using:

```bash
./infinite &
```

The number printed by the shell is the **PID (Process ID)** of the running program.

---

## 4. Verify the Process

Verify the running process using:

```bash
ps -p <PID>
```

---

## 5. `/proc` Filesystem

Linux provides process information through the virtual `/proc` filesystem.

Access the process directory using:

```bash
cd /proc/<PID>
```

or:

```bash
ls /proc/<PID>
```

---

## 6. Important `/proc/<PID>` Entries

* `cmdline` → command used to start the process
* `cwd` → current working directory
* `exe` → executable
* `environ` → environment variables
* `fd/` → open file descriptors
* `maps` → memory mappings
* `stat` → process statistics
* `status` → detailed human-readable process information
* `task/` → thread information

---

## 7. Examples

View detailed process information:

```bash
cat /proc/<PID>/status
```

View process statistics:

```bash
cat /proc/<PID>/stat
```

View open file descriptors:

```bash
ls -l /proc/<PID>/fd
```

---

## 8. Terminate the Process

Terminate the infinite-loop process using:

```bash
kill <PID>
```

