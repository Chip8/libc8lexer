# libc8lexer

A lexer module for Chip-8 assembly.

*Extra Link:  [Standard Chip-8 Instructions](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1)*
## Usage

There a mainly two functions.

### libc8Lexer

This is lexer for a hole source program(lexer line to line).

#### For example:

```asm
//file test.asm
ADD V1, V2
SUB V2, V3
```

```c++
std::istream infile(test.asm);
std::stringstream ss;
ss<<infile.rdbuf();
for(auto x:libc8Lexer(ss.str()))
	std::cout<<x<<" ";
infile.close();
```

The output would be:
```
ADD V1 V2 SUB V2 V3
```

### libc8LineLexer

This is a one line lexer,cuz it only supports to read one line(no '\n')

But you can use ';' to specify one line;

#### Example

```c++
std::string source = "ADD V1,V2;ADD V2,V3;DRW V1, V2, 3";
for(auto x:libc8LineLexer(source,log))
	std::cout<<x<<" ";
```
The output would be:
```
ADD V1 V2 ADD V2 V3 DRW V1 V2 3
```