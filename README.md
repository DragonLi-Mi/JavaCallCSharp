# JavaCallCSharp
Java call C# lib build with .NET CORE 2.0 via C++ as wraper
The code is based on [example from coreCLR](https://github.com/dotnet/coreclr/tree/master/src/coreclr/hosts/unixcoreruncommon)

Java using JNI to call C++ code. then C++ host a core CLR to run C# code.
# pre-require

.NET CORE SDK 2.0: I only tested it in Ubuntu 18.04 x64 (Follow https://dotnet.microsoft.com/download/linux-package-manager/ubuntu18-04/sdk-current)
Install .NET Core 2.1 SDK (works well if you dont have any dotnet installed, tested  Ubuntu 20.04.3 LTS wsl)

1. Enable Microsoft PPA

```
wget https://packages.microsoft.com/config/ubuntu/20.04/packages-microsoft-prod.deb 
sudo dpkg -i packages-microsoft-prod.deb
```

2. Installing .NET Core 2.1 SDK

```
sudo apt update 
sudo apt install apt-transport-https 
sudo apt install dotnet-sdk-2.1 
```

gcc 6: std C++ 14 for the filesystem
Installing build tools

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt install cmake
```

# usage:
```
git submodule init
git submodule update

cmake .
cmake --build . 

javac Sample1.java
java -cp sample1.jar Sample1 
```

`You should keep the compiled file in the same folder.`
