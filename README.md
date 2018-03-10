# swig_example 
I wanted to try the swig example for C and Python from the basic tutorial found here:
http://www.swig.org/tutorial.html

I had trouble making it work, until I followed these easy 36-step instructions I found in an answer on stackoverflow.com 
https://stackoverflow.com/questions/11693047/how-to-create-a-dll-with-swig-from-visual-studio-2010/11732619

I put a copy of them in StepByStepInstructions.txt

Also note, output DLL extensions for python  must be .pyd, (don't forget step 24). See also:
https://stackoverflow.com/questions/44419199/windows-and-python-2-7-x-how-to-load-and-deploy-a-swig-generated-module

This repository contains the project that results from all this. So far I've tested it with Python 3.6 and Visual Studio 2017. Here are a few notes of my own

- Skip step 16 (right-click example.i and compile). Instead, generate example_swig.c by running it from the command line in project directory. You may have to create the Release directory first so swig can put example.py there.

`swig -python -outdir Release example.i`

- The instructions are for C++ while the swig example shows a C file. He makes a note of this in the stack overflow answer, but I missed that the first time though. If you do want C++, the command line above (and the one added to the Custom Build Tool for example.i) will have "-c++" in it.

`swig -c++ -python -outdir Release example.i`

- The linker originally issued this warning:
LINK : warning LNK4075: ignoring '/INCREMENTAL' due to '/OPT:ICF' specification

So I added the following to the project Properties>>Linker>>Command Line>>Additional Options

`/opt:noicf /opt:noref`

- Visual Studio complains that ctime may be unsafe, so I added the macro definition as suggested, Properties>>C/C++>>Preprocessor>>Preprocessor Definitions

`_CRT_SECURE_NO_WARNINGS`

Or you could use ctime_s as the warning also suggests, something like this:

```
char time_str[27];

char *get_time()
{
    time_t ltime;
    time(&ltime);
    ctime_s(time_str, sizeof(time_str), &ltime);

    return time_str;
}
``` 

## My Results
```
>cd release
>python
Python 3.6.1 (v3.6.1:69c0db5, Mar 21 2017, 17:54:52) [MSC v.1900 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>>
Python 3.6.1 (v3.6.1:69c0db5, Mar 21 2017, 17:54:52) [MSC v.1900 32 bit (Intel)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import example
>>> dir(example)
['__builtin__', '__builtins__', '__cached__', '__doc__', '__file__', '__loader__', '__name__', '__package__', '__spec__', '_example', '_newclass', '_object', '_swig_getattr', '_swig_property', '_swig_repr', '_swig_setattr', '_swig_setattr_nondynamic', 'cvar', 'fact', 'get_time', 'my_mod']
>>> example.fact(12)
479001600
>>> example.my_mod(13,4)
1
>>> example.get_time()
'Fri Mar  9 11:05:35 2018\n'
>>>
```

## TODO
- edits for README.me
- Make path to python a env variable
- tell the world
