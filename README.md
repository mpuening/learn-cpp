Learn C++
=========

This repository is my musing while learning Modern C++. This project is mostly test cases.

Makefile Commands
-----------------
The `make config` command invokes `cmake` to set up the `build` directory.

The `make build` command invokes `cmake` to build the binaries.

The `make test` command invokes `ctest` to run the test cases.

The `make clean` command invokes `cmake` to clean the build directory.

The `make realclean` command deletes the `build` directory.

Perhaps `make config build test` would be your first command.

Eclipse IDE Support
-------------------

While some people may feel at home using a simple editor to write C++ code, I
wanted an IDE with support for intelli-sense and debugging. My "goto" IDE is
Eclipse, and fortunately, CMake has some support for generating an Eclipse project
for easy importing.

To build the Eclipse project, run the following command:

 ```
 make eclipse-setup
 ```

Now, be careful about that command. It creates a sub-directory at `eclipse/learn-cpp`
that contains the `.project` and `.settings` files. It is this directory that one will 
import into Eclipse. One does not import the root directory of this project.

To import to project into Eclipse:

* Select File > Import > C/C++ > Existing Code as C++ Makefile Project
* Select the `learn-cpp/eclipse/learn-cpp` directory as the existing code location
* Select `MacOSX GCC` as the Toolchain for Indexer Settings (if using a Mac)

To verify import, ensure these settings are made:

* Right click project > Properties > C/C++ Build > Tool Chain Build
* Select `MacOSX GCC` for the Current toolchain (if using a Mac)
* Select `GNU Make Builder` for the Current Builder

Once imported, one will find most of the code under the `[Targets]` sub-folders.
In my naming conventions of the CMake targets, libraries ending in `_src` have
the source files. One should see `Header Files` and `Source Files` for each library.
The libraries ending in `_lib` are the actual static libraries. For applications
(or executables), one will see an `[exe] app` sub-folder the the main program.
Test sub-folders should also be there having the test cases.

If for some reason, Eclipse does not understand the code, perhaps likely the Indexer
is not working correctly. One can correct this by doing this:

* Right click project > Index > Rebuild

To build the application:

* Right click project > Build Project

To run or debug the application, one needs to create a "Run Configuration" or
"Debug Configuration".

To configure a "Run Configuration" for the Poco app:

* Right click project > Run As > Run Configurations...
* right click C/C++ Application > New Configuration
* Enter `learn-cpp App` as the name of the configuration
* Browse to `eclipse/learn-cpp/bin/app/app` as the C/C++ Application
* Select Apply or Run to save

Once created, the configuration should display in icon menu for easy running.

To run test cases, one could also build a Run Configuration for each file. But
I have yet to find a solution to run all test cases together in Eclipse (`ctest`).

After one updates the CMake files, one can again run the `eclipse-setup` command
from the `Makefile`. Afterwards, just right click the project and select Refresh.
New changes should display, but to get the project working properly again, it may
require a project clean and the index rebuilt. Also check if the "C/C++ Build"
section in the project properties has disappeared. If so, delete the project and
re-import. I haven't figured out how to restore it after it disappears.

