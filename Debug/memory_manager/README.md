Memory Manager
=========

Introduction
------------

This module provides a simple and efficient way to track the memory operations 
done in your application. 

How it works
----------------

- Add module files (.hpp/.cpp) to your project.
- Turn on the debug mode ( -DDEBUG for instance with gcc)
- Init the module (requested logfilename)
- Use allocation/desallocation operators as always (full transparency)
- Call the Memory manager's report routine
- Log file analysis -> Profit !

Example
-------


See [samples/main.cpp](https://github.com/rexou/Cpp-Tools/blob/master/Debug/memory_manager/samples/main.cpp "samples/main.cpp") for self-explanatory source code & the resulting file [samples/memory_leaks.report](https://github.com/rexou/Cpp-Tools/blob/master/Debug/memory_manager/samples/memory_leaks.report "samples/memory_leaks.report").

Hope you'll enjoy it.

NOTE
-----

This module has been realized in/for a C++03 context, I guess it would be easier to make sure
your app isn't leaking with C++11 smart pointers.
