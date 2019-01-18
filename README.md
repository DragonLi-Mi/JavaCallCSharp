[![Build Status](https://dev.azure.com/marcozo0520/JavaCallCSharp/_apis/build/status/eisber.JavaCallCSharp?branchName=master)](https://dev.azure.com/marcozo0520/JavaCallCSharp/_build/latest?definitionId=1?branchName=master)


# JavaCallCSharp
Java call C# lib build with .NET CORE 2.0 via C++ as wraper
The code is based on [example from coreCLR](https://github.com/dotnet/coreclr/tree/master/src/coreclr/hosts/unixcoreruncommon)

Java using JNI to call C++ code. then C++ host a core CLR to run C# code.
# pre-require

.NET CORE SDK 2.0: I only tested it in Ubuntu 18.04 x64 (Follow https://dotnet.microsoft.com/download/linux-package-manager/ubuntu18-04/sdk-current)

gcc 6: std C++ 14 for the filesystem

# usage:
git submodule init
git submodule update

cmake .
cmake --build . 

java -cp sample1.jar Sample1 


`You should keep the compiled file in the same fold.`
