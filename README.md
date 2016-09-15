tracetool - a configurable and efficient logging framework for C++
---------------------------------------------------------------
tracetool is a framework for tracing the execution of a C or C++ program and
inspecting its state. This is achieved by instrumenting the source code of the
target program and linking the recompiled sources against a shared `tracelib`
library.

![Image Of TraceTool GUI]
(http://blog.froglogic.com/wp-content/uploads/Screen-Shot-2016-09-15-at-13.39.37.png)

License
-------
tracetool is free software: you can redistribute it and/or modify it under the
terms of the [GNU Lesser General Public
License](https://www.gnu.org/licenses/lgpl-3.0-standalone.html) as published by
the Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

Installation
------------
Building the framework requires

* A C++ compiler, e.g. GCC or [Microsoft Visual Studio 2008 or newer](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)
* [CMake](http://www.cmake.org) 3.0.0 or newer
* [Qt](https://www.qt.io/) 5.6
* For building the documentation, [Doxygen](http://www.stack.nl/~dimitri/doxygen/) is needed.

The actual build is the merely a matter of running the commands

```
cmake -DCMAKE_PREFIX_PATH=<path_to_Qt>
make
```

On Windows, you may want to pass `-G "NMake Makefiles"` to cmake to generate
Makefiles and then use `nmake` to use those Makefiles.

Quick Start
-----------
Here's a quick step by step guide on how to instrument a basic program
so that it generates trace information. Here's the initial source code
of the sample program:

```c++
#include <iostream>
#include <string>

int main()
{
    using namespace std;

    string name;
    cout << "Please enter your name: ";
    cin >> name;

    cout << "Hello, " << name << "!" << endl;
}
```

First, instrument the above source code so that the `tracelib.h`
header is included and insert a few calls to various tracelib macros into
the source code. Here's the instrumented code:

```c++
#include <iostream>
#include <string>

#include "tracelib.h"

int main()
{
    fTrace(0) << "main() entered";

    using namespace std;

    string name;
    cout << "Please enter your name: ";
    cin >> name;

    fWatch(0) << fVar(name);

    cout << "Hello, " << name << "!" << endl;

    fTrace(0) << "main() finished";
}
```

Save the resulting file to e.g. `hello\_instrumented.cpp`.

Here's a sample compile line for use with `cl.exe` (the compiler
which comes with Microsoft Visual Studio):

```
cl /EHsc hello_instrumented.cpp /I <TRACELIB_PREFIX>\include\tracelib
    <TRACELIB_PREFIX>\lib\tracelib.lib
    ws2_32.lib
```

The resulting binary (`hello\_instrumented.exe` in the above case) will
behave as before. The tracing (and the resulting change to runtime
performance) is only activated in case a special configuration file was
detected.

Creating a configuration file is a matter of writing some XML. Save
the following file as `tracelib.xml` and store it in the same directory
as `hello\_instrumented.exe` which was built above:

```xml
<tracelibConfiguration>
<process>
  <name>hello_instrumented</name>
  <output type="stdout"/>
  <serializer type="plaintext"/>
</process>
</tracelibConfiguration>
```

Now, running the program will generate quite a bit of additional output:
```
03.09.2010 16:00:56: Process 2524 [started at 03.09.2010 16:00:56] (Thread 468): [LOG] 'main() entered' hello_instrumented.cpp:8: int __cdecl main(void)
Please enter your name: Max
03.09.2010 16:00:57: Process 2524 [started at 03.09.2010 16:00:56] (Thread 468): [WATCH] hello_instrumented.cpp:16: int __cdecl main(void)
Hello, Max!
03.09.2010 16:00:57: Process 2524 [started at 03.09.2010 16:00:56] (Thread 468): [LOG] 'main() finished' hello_instrumented.cpp:20: int __cdecl main(void)
03.09.2010 16:00:57: Process 2524 [started at 03.09.2010 16:00:56] finished
```

Components
----------
The tracetool framework consists of multiple components:

* `tracelib.dll` (resp. `libtracelib.so` on Linux) is a dynamic library (plus
accompanying header files) which has to be linked into any application which
wishes to use the tracing functionality.
* `tracegui` is a GUI for reviewing previously recorded traces as
well as recording and watching the trace generated by running applications
live.
* `traced` is a daemon process which collects and stores trace data
in the background without running a GUI.Traced applications can be
configured to send their output over a network connection to `traced.exe`.
The recorded traces can be sent to other people and reviewed later
using `tracegui`.
* `trace2xml` is a utility program for dumping a trace database
generated by `tracegui` or `traced` into an XML file which can then
be processed by other scripts.
* `xml2trace` performs the reverse operation of `trace2xml`: given an XML
file, a `.trace` file is generated which can be loaded by `tracegui`.
* `convertdb` is a helper utility for converting earlier versions of
databases with tracelib traces.

Acknowledgements
----------------
This project is really just standing on the shoulders of giants. It was made
possible by and takes advantage of a few other open source projects:

* The [PCRE library](http://www.pcre.org) is used for matching function names
to include in the execution trace via regular expressions.
* For matching functionn names to include in the execution trace via wildcard patterns, the
[wildcmp
function](http://www.codeproject.com/Articles/1088/Wildcard-string-compare-globbing)
is used.
* Reading the `tracelib.xml` file is done using the
[TinyXML](http://www.grinninglizard.com/tinyxml/) parser.
* Stack traces logged for selected trace points are generated by
[StackWalker](https://stackwalker.codeplex.com/).
* Efficient storage of execution traces is implemented using
  [SQLite](https://www.sqlite.org/).
