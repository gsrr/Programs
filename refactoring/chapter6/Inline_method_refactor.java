package example.Inline_method;

class Inline_method_refactor
{
        private int _numberOfLateDeliveries;
        public Inline_method_refactor(int numberOfLateDeliveries)
        {
                this._numberOfLateDeliveries = numberOfLateDeliveries;
        }

        int getRating() 
        {
                return (moreThanFiveLateDeliveries()) ? 2 : 1;
        }

        boolean moreThanFiveLateDeliveries()
        {
                return this._numberOfLateDeliveries > 5;
        }

        public static void main(String args[])
        {
                Inline_method_refactor test = new Inline_method_refactor(10);
                System.out.println("ret : " + test.getRating());                
        }
}




