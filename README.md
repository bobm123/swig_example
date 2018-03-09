"# swig_example" 
Running the swig example of C and Python from the basic tutorial found here:
http://www.swig.org/tutorial.html

I had trouble making it work, until I followed the easy 36-step instructions from answer here (and copied in StepByStepInstructions.txt):
https://stackoverflow.com/questions/11693047/how-to-create-a-dll-with-swig-from-visual-studio-2010/11732619

Also note, output DLL extension must be .pyd, (don't forget step 24). See also:
https://stackoverflow.com/questions/44419199/windows-and-python-2-7-x-how-to-load-and-deploy-a-swig-generated-module

This repository contains the project that results. So far I've tested it with Python 3.6 and Visual Studio 2017.

- Skip step 16 (right-click example.i and compile). Instead run it from the command line in the same directory as example.i to generate example_swig.c for the next few steps. You may have to create the release folder first so swig can put example.py there.

swig -python -outdir Release example.i

- The instructions are for C++ while the swig example shows a C file. He makes a note of this in the stack overflow answer, but I missed that the first time though. If you do want C++, the command line above (and the one added to the Custom Build Tool for example.i) will have "-c++" in it.

swig -c++ -python -outdir Release example.i

- The linker originally issued this warning:
LINK : warning LNK4075: ignoring '/INCREMENTAL' due to '/OPT:ICF' specification

So I added the following to the project Properties>>Linker>>Command Line>>Additional Options
/opt:noicf /opt:noref

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
