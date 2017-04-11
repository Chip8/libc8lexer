# libc8lexer

A lexer module for Chip-8 assembly.

*Extra Link:  [Standard Chip-8 Instructions](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#3.1)*
## Usage

Include the header file as a static/dynamic library file.

### class C8Lexer

```asm
//Source file content,read into string source
ADD V1, V2
SUB V2, V3
JP I
CALL I
```

```C++
libc8lexer lexer(source);
if(lexer.Scan())
	{
	std::cout<<lexer.Output();
}
```

The output would be:

```
[Instruction]    (2 - 5) : ADD
[8 Bit Register]    (5 - 6) : V1
[Comma]    (6) : ,
[8 Bit Register]    (9 - 10) : V2
[Instruction]    (13 - 16) : SUB
[8 Bit Register]    (16 - 17) : V2
[Comma]    (17) : ,
[8 Bit Register]    (20 - 21) : V3
[Instruction]    (23 - 25) : JP
[Address Register]    (25) : I
[Instruction]    (30 - 34) : CALL
[Address Register]    (32) : I
```

*There are also a member function of libc8lexer which returns the token list*

```C++
std::vector<libc8Token>& libc8lexer::GetList()
```