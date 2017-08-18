# JavaCallCSharp
Java call c# lib build with .NET CORE 2.0
# pre-require
jdk: You should edit the Makefile and set the JAVALIB

.NET CORE SDK 2.0:I only test it in Ubuntu 16.04

gcc 6: std c++ 14 for the filesystem

# usage:
javac Sample1.java

javah Sample1

make

cd cs

dotnet restore

dotnet build 

java Sample1 


`You should keep the compiled file in the same fold.`
