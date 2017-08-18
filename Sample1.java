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
    System.load("/home/hqy/jtest/CoreCLRHost/tar.so");

    Sample1 sample = new Sample1();
    int square = sample.intMethod(5);
    boolean bool = sample.booleanMethod(true);
    String text =  sample.stringMethod("JAVA");
    int sum = sample.intArrayMethod(new int[]{1,1,2,3,5,8,13});

    int success=0;
    success= sample.coreClrHost("./Managed.dll");
    System.out.println("intMethod: "+ square);
    System.out.println("boolMethod: "+ bool);
    System.out.println("stringMethod: "+ text);
    System.out.println("intArrayMethod: "+ sum);
    System.out.println("status:"+success);

}

}
