# Jam
### "best c clone"

## Compiling
To compile a .ja file, you first need to have the source code (everything in /src/) on your system. Once you have that make sure that g++ is in your environment variables. Compile the source code using this terminal command in your /src/ directory

```bash
g++ -o jam jam.cpp
```

Once you have done that make sure that the binary filepath is in the environment variables (you can find how to do that in a c compiling tutorial). Then you will have to do this command to compile it (this will work in every directory from now on, on this pc).

```bash
jam input.ja output
```
