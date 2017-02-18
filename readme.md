[![Build status](https://ci.appveyor.com/api/projects/status/4yjvhauivwk0wgex?svg=true)](https://ci.appveyor.com/project/AraHaan/bin2c)
[![Build Status](https://api.travis-ci.org/AraHaan/bin2c.svg?branch=master)](https://travis-ci.org/AraHaan/bin2c)
[![Build status](https://doozer.io/badge/AraHaan/bin2c/buildstatus/master)](https://doozer.io/user/arahaan/bin2c)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/3aab1e403474490aaacaa1a2883ccf8a)](https://www.codacy.com/app/AraHaan/bin2c?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AraHaan/bin2c&amp;utm_campaign=Badge_Grade)
[![GitHub watchers](https://img.shields.io/github/watchers/arahaan/bin2c.svg)](https://github.com/AraHaan/bin2c/watchers)
[![GitHub forks](https://img.shields.io/github/forks/arahaan/bin2c.svg)](https://github.com/arahaan/bin2c/network)
[![GitHub stars](https://img.shields.io/github/stars/arahaan/bin2c.svg)](https://github.com/arahaan/bin2c/stargazers)
[![GitHub license](https://img.shields.io/badge/license-MIT-orange.svg)](https://raw.githubusercontent.com/weiboad/adbase/master/LICENSE)

bin2c v0.15.0 - Windows/Linux/MAC - [FINAL]:

Windows (Requires Visual Studio 2015 or newer with command line tools):

- open the Developer Command Prompt x86 (for 32-bit compile) or x64 (for 64-bit compile).

- then to actually build create a bat file named compile.bat in the folder you downloaded bin2c to with this content: 
```cmd
@echo off
RC.exe /nologo /r bin2c.rc
cl.exe /nologo /Ox /Tp "bin2c.cpp" /EHsc /link /NOLOGO /OUT:"bin2c.exe" /SUBSYSTEM:CONSOLE "bin2c.res" /FIXED
```

*Note: Doing this to compile is critical to being able to run bin2c on systems before Windows 7 because before that (Windows Vista and older) does not have the* ``api-ms-win-*.dll`` *files present for the C/C++ runtime. Doing this will have the compiled binary import functions from kernel32.dll only. Which kernel32.dll is present in Windows since Windows 95 so theoretically bin2c could probably work on Windows 95 but I would not try to test that to know for sure.*

- after the file is (compile.bat) created maximize the Developer command prompt(s) you opened and type in:
```cmd
cd path\to\where\you\downloaded\bin2c
path\to\where\you\downloaded\bin2c>compile.bat
```

-	then to build tests do something like this (you can also add this to the end of compile.bat to test out the build):
```cmd
cd tests
..\\bin2c.exe /custvar "IMAGE_VP" /nohead /infile ".\\VP.jpg" /outfile ".\\VP.hpp"
cl.exe /nologo /Ox /Tp "VP.cpp" /EHsc /link /NOLOGO /OUT:"VP.exe" /SUBSYSTEM:CONSOLE /FIXED
cd ..
```

This *should* Generate working tests.

*Note: since v0.2.0 the generated output will contain the name of the original files.*

MAC:

-	To build you need either gcc/g++ 6.3.0 (or latest) or clang 3.9.1 (or latest).

*Note: Don't forget to use the rc file. (which might need some changes) This should hopefully allow you to have a resource section.*
*Also Since I do not work for apple nor do I even own a mac I do not know for sure how to compile an resoruce script on a mac for a .rsrc section on the compiled binary.*

Linux:

-	To build you need either gcc/g++ 6.3.0 (or latest) or clang 3.9.1 (or latest).
