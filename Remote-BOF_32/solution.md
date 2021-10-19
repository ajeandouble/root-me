Notes:

I modified the version to print interresting things
Should investigate using valgrind/gdb/ghidra/ida whatever

On BSS you get:

array[handlers_n] of struct handler { name; name; }
handlers_n = 30

strcmp keep looping and probably heats a non-readable segment so SEGFAULT.

might be a good idea to overwrite stmp with a custom func to see what happens

we should overwrite handlers_n with the right thing
but we should especially overwrite handlers_n with a custom handler name which was not used.
and make the address point to the beginning of buff whih is also stored in BFF
as we recall we can execute BSS? (or maybe not) -> need to check that with the options

then BOF

So summary: BSS exploitation. we can overwrite a function pointer which is used as a pointer remotely

AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAabcdBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBb

we know overwrited n_handler to be 




BTW why if you do struct handler { int ; int a; } you get sizeof of only a?

