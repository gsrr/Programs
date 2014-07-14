package example.Inline_method;

class Inline_method
{
        private int _numberOfLateDeliveries;
        public Inline_method(int numberOfLateDeliveries)
        {
                this._numberOfLateDeliveries = numberOfLateDeliveries;
        }
        int getRating() 
        {
                return (_numberOfLateDeliveries > 5) ? 2 : 1;
        }
        public static void main(String args[])
        {
                Inline_method test = new Inline_method(10);
                System.out.println("ret : " + test.getRating());                
        }
}




