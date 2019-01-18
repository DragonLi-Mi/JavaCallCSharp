# JavaCallCSharp
Java call C# lib build with .NET CORE 2.0 via C++ as wraper
The code is based on [example from coreCLR](https://github.com/dotnet/coreclr/tree/master/src/coreclr/hosts/unixcoreruncommon)

Java using JNI to call C++ code. then C++ host a core CLR to run C# code.
# pre-require
JDK: You should edit the Makefile and set the JAVALIB PATH

.NET CORE SDK 2.0: I only tested it in Ubuntu 16.04 x64

gcc 6: std C++ 14 for the filesystem

# usage:
git submodule init
git submodule update

cmake .
cmake --build . 

java -cp sample1.jar Sample1 


`You should keep the compiled file in the same fold.`
