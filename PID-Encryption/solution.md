```
cryptanalyse-ch21@challenge01:~$ cat /tmp/pid.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	char pid[16];
	snprintf(pid, sizeof(pid), "%d", getpid() + 1);
	printf("%s", crypt(pid, "$1$awesome"));
}
cryptanalyse-ch21@challenge01:~$ cd /tmp
cryptanalyse-ch21@challenge01:/tmp$ gcc /tmp/pid.c -lcrypt -o /tmp/pid
cryptanalyse-ch21@challenge01:~$ /challenge/cryptanalyse/ch21/ch21 $(/tmp/pid)
$1$awesome$SC580veY99jupkxl2ZPpY0=$1$awesome$SC580veY99jupkxl2ZPpY0WIN!
bash-4.3$ cat .passwd 
-/q2/a9d6e31D
```

-------------------------------------------------------------------------------
### Ressources
[How does linux determine the next pid - Stack Overflow](https://stackoverflow.com/questions/3446727/how-does-linux-determine-the-next-pid)