abstract class Template{
        void doAll(){
                A();
                B();
                C();
                System.out.println();
        }
        abstract void A();
        abstract void B();
        abstract void C();
}

class SubA extends Template{
        void A(){
                System.out.println("A:SubA");
        }
        void B(){
                System.out.println("B:SubA");
        }
        void C(){
                System.out.println("C:SubA");
        }
}

class SubB extends Template{
        void A(){
                System.out.println("A:SubB");
        }
        void B(){
                System.out.println("B:SubB");
        }
        void C(){
                System.out.println("C:SubB");
        }
}

public class ex1{
        public static void main(String args[])
        {
                Template t = new SubA();
                t.doAll();
                t = new SubB();
                t.doAll();
        }
}
