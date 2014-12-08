import java.lang.reflect.*;


class Number
{
        int x = 10;
        int y = 20;
}

public class Handler
{
        public static void main(String args[])
        { 
                Number number = new Number();
                try
                {
                        Class myClass = Class.forName("Library");
                        java.lang.reflect.Constructor constructor = myClass.getConstructor(Number.class);
                        java.lang.reflect.Method objAdd = myClass.getMethod("addition");
                        

                        Class[] pargs = {int.class, int.class};
                        java.lang.reflect.Method objSub = myClass.getMethod("sub",pargs);

                        
                        Object obj = constructor.newInstance(number);
                        System.out.println(objAdd.invoke(obj));
                        System.out.println(objSub.invoke(obj, 20, 5));
                        
                        Library lib = new Library(new Number());
                        java.lang.reflect.Method libAdd = Library.class.getMethod("addition");
                        System.out.println(libAdd);
                        java.lang.reflect.Method libaaa = Library.class.getMethod("aaa");

                        System.out.println(libaaa);
                        if(libaaa.equals(""))
                        {
                                System.out.println("not null");
                        }
                        else
                        {
                                System.out.println("null");

                        }
                        System.out.println(libAdd.invoke(lib));

                }
                catch(Exception e)
                {
                        System.out.println("exception");
                }
        }


}
