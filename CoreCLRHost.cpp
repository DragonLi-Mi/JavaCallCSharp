/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */
#include <iostream>
#include <string.h>
#include "CoreCLRHost.hpp"
#include "utils.hpp"
#include "Sample1.h"

int runFromEntryPoint(
            std::string currentExeAbsolutePath,
            std::string clrFilesAbsolutePath,
            std::string managedAssemblyAbsoluteDir,
            std::string assemblyName,
            std::string entryPointType,
            std::string entryPointName)
{
    std::cout<<"currentExeAbsolutePath="<<currentExeAbsolutePath<<std::endl<<"clrFilesAbsolutePath="<<clrFilesAbsolutePath<<std::endl<<"managedAssemblyAbsoluteDir="<<managedAssemblyAbsoluteDir<<std::endl<<"assemblyName="<<assemblyName<<std::endl;
    std::cout<<"entryPointType="<<entryPointType<<std::endl<<"entryPointName="<<entryPointName<<std::endl;
  std::string coreClrDllPath = clrFilesAbsolutePath + "/" + coreClrDll;


  if ( coreClrDllPath.size() >= PATH_MAX ) {
      std::cerr << "Path to libcoreclr.so too long!" << std::endl;
      return -1;
  }

  std::string nativeDllSearchDirs = managedAssemblyAbsoluteDir + ":" + clrFilesAbsolutePath;

  std::string tpaList;
  AddFilesFromDirectoryToTpaList( clrFilesAbsolutePath, tpaList );
  //std::cout<<"line 32"<<std::endl;
  auto dl = dynamicLinker::dynamicLinker::make_new( coreClrDllPath );
  auto coreclr_initialize = dl->getFunction<coreclrInitializeFunction>("coreclr_initialize");
  auto coreclr_shutdown = dl->getFunction<coreclrShutdownFunction>("coreclr_shutdown");
  auto coreclr_create_delegate = dl->getFunction<coreclrCreateDelegateFunction>("coreclr_create_delegate");
 //std::cout<<"line 37"<<std::endl;
  try {
    dl->open();
    coreclr_initialize.init();
    coreclr_shutdown.init();
    coreclr_create_delegate.init();
  } catch ( dynamicLinker::openException e ) {
    std::cerr << "Cannot find " << coreClrDll << "Path that was searched: "
              << coreClrDllPath << std::endl;
    std::cerr << e.what() << std::endl;
    return -1;
  } catch ( dynamicLinker::symbolException e ) {
    std::cerr << "Probably your libcoreclr is broken or too old." << std::endl;
    std::cerr << e.what() << std::endl;
    return -1;
  } catch ( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << "dynamicLinkerEx: " << e.what() << std::endl;
    return -1;
  }

  const char *propertyKeys[] = {
      "TRUSTED_PLATFORM_ASSEMBLIES",
      "APP_PATHS",
      "APP_NI_PATHS",
      "NATIVE_DLL_SEARCH_DIRECTORIES",
      "AppDomainCompatSwitch"
  };

  const char *propertyValues[] = {
      tpaList.c_str(),
      managedAssemblyAbsoluteDir.c_str(),
      managedAssemblyAbsoluteDir.c_str(),
      nativeDllSearchDirs.c_str(),
      "UseLatestBehaviorWhenTFMNotSpecified"
  };

  void* hostHandle = NULL;
  unsigned int domainId = 0;
  int status = -1;

  // initialize coreclr
  try {
    status = coreclr_initialize (
      currentExeAbsolutePath.c_str(),
      "simpleCoreCLRHost",
      sizeof(propertyKeys) / sizeof(propertyKeys[0]),
      propertyKeys,
      propertyValues,
      &hostHandle,
      &domainId
    );
  } catch ( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if ( status < 0 ) {
    std::cerr << "ERROR! coreclr_initialize status: 0x" << std::hex << status << std::endl;
    return -1;
  }

  // Fancy modern C++ code. You can also just use void *.
  auto no_del = []( auto x ) { (void)(x); };
  auto csharp_runIt = std::unique_ptr<csharp_runIt_t, decltype(no_del)>(nullptr, no_del);

  try {
    // create delegate to our entry point
    status = coreclr_create_delegate (
      hostHandle,
      domainId,
      assemblyName.c_str(),
      entryPointType.c_str(),
      entryPointName.c_str(),
      reinterpret_cast<void**>(&csharp_runIt)
    );
  } catch ( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if ( status < 0 ) {
    std::cerr << "ERROR! coreclr_create_delegate status: 0x" << std::hex << status << std::endl;
    return -1;
  }

  myClass tmp = myClass();
  tmp.question();

  /*
   *  If arguments are in in different order then second arg is 0 in C#.
   *  probably something with padding/offset/ptr byte size
   */
  (*csharp_runIt)( tmp, std::mem_fun_ref(&myClass::print) );

  try {
    status = coreclr_shutdown ( hostHandle, domainId );
  } catch ( dynamicLinker::dynamicLinkerException e ) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  if ( status < 0 ) {
    std::cerr << "ERROR! coreclr_shutdown status: 0x" << std::hex << status << std::endl;
    return -1;
  }

  return 0;
}


JNIEXPORT jint JNICALL Java_Sample1_intMethod
       (JNIEnv *env, jobject obj, jint num){
                return num * num;
            }
     JNIEXPORT jboolean JNICALL Java_Sample1_booleanMethod
          (JNIEnv *env, jobject obj, jboolean boolean){
                  return !boolean;
              }
    JNIEXPORT jstring JNICALL Java_Sample1_stringMethod
        (JNIEnv *env, jobject obj, jstring string){
                const char *str = env->GetStringUTFChars(string,0);
                char cap[128];
               strcpy(cap,str);
               env->ReleaseStringUTFChars(string , str);
                return env->NewStringUTF(cap);
            }

    JNIEXPORT jint JNICALL Java_Sample1_intArrayMethod
        (JNIEnv *env, jobject obj, jintArray array){
                int i, sum=0;
                jsize len = env->GetArrayLength(array);
                jint *body = env ->GetIntArrayElements(array,0);
                for (i=0;i<len;i++)
                {
                            sum+=body[i];
                        }
                env->ReleaseIntArrayElements(array, body,0);
                return sum;
            }
JNIEXPORT jint JNICALL Java_Sample1_coreClrHost(JNIEnv *env, jobject obj, jstring string)
    {
  const char *str = env->GetStringUTFChars(string,0);
  char cap[128];
  strcpy(cap,str);
  std::string dllpath(cap); //"./Managed.dll";
  env->ReleaseStringUTFChars(string , str);
 // std::string dllpath = env->NewStringUTF(cap);
  std::string cwd = SCCH_fs::current_path();
  cwd += "/";
  std::cout<<"dll path :"<<dllpath<<std::endl;

  std::string assemblyName(dllpath);
  std::string assemblyDir(assemblyName);


  if( !assemblyName.size() ) {
    std::cerr << "ERROR: Bad ASSEMBLY_PATH !" << std::endl;
    return 0;
  }

  size_t find = assemblyName.rfind('/');
  if( find == std::string::npos )
    find = 0;

  assemblyName = assemblyName.substr( find+1, assemblyName.size() );

  if( assemblyName.size() < 5 ||
      assemblyName.substr( assemblyName.size()-4,
                           assemblyName.size()) != ".dll" ) {
    std::cerr << "ERROR: Assembly is not .dll !" << std::endl;
    return 0;
  }

  assemblyName = assemblyName.substr( 0, assemblyName.size()-4 );

  assemblyDir.erase(find);  // get dir of assembly
  assemblyDir = cwd + assemblyDir;

  int exitCode = runFromEntryPoint(
                          cwd, //+std::string("./tar.so"), // absolute path to this exe
                          std::string("/usr/share/dotnet/shared/Microsoft.NETCore.App/2.1.30/"),     // absolute path to coreCLR DLLs
                          assemblyDir, // absolute path to DLL to run
                          assemblyName,
                          std::string("Managed"),
                          std::string("runIt"));

  if ( exitCode < 0 )
    std::cout << "Exit Code: " << exitCode << std::endl;


  return 1;
}

int main( int argc, char* argv[] ) {  return 0;}
