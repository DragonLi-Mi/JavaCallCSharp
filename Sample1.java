public class Sample1
{
    public native int intMethod(int n);
    public native boolean booleanMethod(boolean bool);
    public native String stringMethod(String text);
    public native int intArrayMethod(int[] intArray);
    public native int coreClrHost(String dllpath);
    public static void main(String[] args)
{
    //System.loadLibrary("Sample1");
    System.load(System.getProperty("user.dir") + java.io.File.separator + "libtar.so");

    Sample1 sample = new Sample1();

    int success= sample.coreClrHost("./bin/Debug/netcoreapp2.1/Managed.dll");

}

}
