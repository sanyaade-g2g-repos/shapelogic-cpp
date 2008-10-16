====================
ShapeLogic C++ v 0.1
====================

This is a very rudimenary release. This is not an adequate description of how
to build ShapeLogic C++, but just a few pointers.
See project site for more information: http://www.shapelogic.org/cpp.html

Also ShapeLogic C++ v 0.1 release does not do much, the main function is to
show how the different components of ShapeLogic C++ work together.

Main components:
* Boost  the C++ library
* Generic Image Library for writing new image processing code
* FLTK, Fast Light Toolkit lightweight cross platform GUI
* Google Testing Framework
* Boost.build v2 for command line based build system

Make sure that they are available on your system.

In ShapeLogic C++ 0.2 OpenCV will be added for reading and writing different
image formats and for a long list of existing computer vision algorithms.

-------------------------------------------------------------------------------
Build under UNIX, Linux, possibly OS X
-------------------------------------------------------------------------------

ShapeLogic C++ can be build from command line:

cd shapelogic-cpp
bjam

ShapeLogic C++ can be build from Eclipse CDE:
There is a project file coming with the project

For more information see http://www.shapelogic.org/cpp-setup-linux.html

-------------------------------------------------------------------------------
Build under Windows
-------------------------------------------------------------------------------

It has been built using MSVC Express.

Start by compiling FLTK. This worked with the MSVC version 2005 project file.

Rename the Jamfile.msvc and Jamroot.msvc to Jamfile and Jamroot.
 
Then from a command line run:

cd shapelogic-cpp
bjam

For more information see http://www.shapelogic.org/cpp-setup-windows.html
