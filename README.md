# libc8lexer

A lexer module for Chip-8 assembly.

*Extra Link:  [Standard Chip-8 Instructions](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1)*
## Usage

Include the header file as a static/dynamic library file.

### class libc8Lexer

```asm
//Source file content,read into string source
ADD V1, V2
SUB V2, V3
JP I
CALL I
```

```C++
libc8Lexer lexer(source);
if(lexer.Scan())
	{
	std::cout<<lexer.Output();
}
```

The output would be:

```
[Instruction]    (0 - 2) : ADD
[8 Bit Register]    (4 - 5) : V1
[Comma]    (6) : ,
[8 Bit Register]    (8 - 9) : V2
[Instruction]    (11 - 13) : SUB
[8 Bit Register]    (15 - 16) : V2
[Comma]    (17) : ,
[8 Bit Register]    (19 - 20) : V3
[Instruction]    (22 - 23) : JP
[Address Register]    (25) : I
[Instruction]    (27 - 30) : CALL
[Address Register]    (32) : I
```

*There are also a member function of libc8lexer which returns the token list*

```C++
std::vector<libc8Token>& libc8lexer::GetList()
```