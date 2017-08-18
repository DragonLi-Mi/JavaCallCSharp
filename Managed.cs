/*
 *  Copyright (c) Hubert Jarosz. All rights reserved.
 *  Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

using System;
using System.Runtime.InteropServices;

public class Managed {

[UnmanagedFunctionPointer(CallingConvention.ThisCall)]
unsafe delegate void myDelegate( IntPtr thisptr );

public static unsafe void runIt( IntPtr thisptr, IntPtr mem_fun ) {
    Console.WriteLine("Here's C# code:");

    myDelegate fun = (myDelegate) Marshal.GetDelegateForFunctionPointer( mem_fun, typeof(myDelegate) );

    fun(thisptr);  // first argument of member functions in C++ is "this", but it's hidden from us :-)
  }
}
