# langproc2019

**Translator from C to Python3 and compiler of C to MIPS**

*to run:*

```
$ make bin/c_compiler
$ ./bin/c_compiler -{MODE} source.c -o {dest_file}
```
2 modes:

- -S is to compile C90 to MIPS1 assembly (dest_file needs to be .s)
- --translate is to translate a subset of C90 to python3 (dest_file needs to be .py)



*to test:*
- `test_translator.sh` which tests the translator against the test cases in c_translator_tests
- `test_compiler.sh` which tests the compiler against the test_deliverable (in capitals), and a handful of other tests (func_call, mul)

--------------
*comments:*

- Compiler supports basic implementation

- Function calls resulted in a segmentation fault which I couldn't figure out in time
