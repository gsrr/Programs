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
                        java.lang.reflect.Method libAdd = myClass.getMethod("addition");
                        System.out.println(libAdd.invoke(lib));

                }
                catch(Exception e)
                {
                        ;
                }
        }


}
