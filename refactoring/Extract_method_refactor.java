package example.Extract_method;

import java.util.Vector;
import java.util.Enumeration;


class Extract_method_refactor
{
        Vector<Order> _orders = new Vector<Order>();
        String _name;
        public Extract_method_refactor(String name, int[] prices)
        {
                this._name = name;
                for (int i = 0 ; i < prices.length ; i++)
                {
                        this._orders.addElement(new Order(prices[i]));
                }
        }        

        void printBanner()
        {
                System.out.println ("**************************");
                System.out.println ("***** Customer Owes ******");
                System.out.println ("**************************");

        }

        void printDetail(double outstanding)
        {
                System.out.println ("name: " + this._name);
                System.out.println ("amount: " + outstanding);
        }

        double getOutstanding()
        {
                double outstanding = 0.0;
                Enumeration e = this._orders.elements();
                while (e.hasMoreElements()) {
                        Order each = (Order) e.nextElement();
                        outstanding += each.getAmount();
                }
                return outstanding;
        }
        public void printOwing() 
        {
                
                printBanner();
                double outstanding = getOutstanding();
                printDetail(outstanding);
        }

        public static void main(String args[])
        {
             int[] prices = {10, 20, 30, 40, 60};   
             Extract_method_refactor test = new Extract_method_refactor("My Order", prices);   
             test.printOwing();
        }
}
