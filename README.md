# libc8lexer

A lexer module for Chip-8 assembly.

## Usage

There a mainly two functions.Each of them have two overload,one has log output and other doesn't.

To use the output version, just passsing a ofstream.

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
for(auto x:libc8Lexer(ss.str(),infile))
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
std::ofstream log = ("test.log");
std::string source = "ADD V1,V2;ADD V2,V3;DRW V1, V2, 3";
for(auto x:libc8LineLexer(source,log))
	std::cout<<x<<" ";
```
The output would be:
```
ADD V1 V2 ADD V2 V3 DRW V1 V2 3
```
And contents in test.log:
```
Instruction found: ADD
8 Bit Register found: V1
8 Bit Register found: V2
Instruction found: ADD
8 Bit Register found: V2
8 Bit Register found: V3
Instruction found: DRW
8 Bit Register found: V1
8 Bit Register found: V2
Var found: 3
```