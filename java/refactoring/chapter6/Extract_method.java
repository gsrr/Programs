package example.Extract_method;

import java.util.Vector;
import java.util.Enumeration;



class Order
{
        int _price;
        public Order(int price)
        {
               this._price = price;
        }
        public int getAmount()
        {
                return this._price;
        }
}

class Extract_method
{
        Vector<Order> _orders = new Vector<Order>();
        String _name;
        public Extract_method(String name, int[] prices)
        {
                this._name = name;
                for (int i = 0 ; i < prices.length ; i++)
                {
                        this._orders.addElement(new Order(prices[i]));
                }
        }        

        public void printOwing() 
        {
                
                Enumeration e = this._orders.elements();
                double outstanding = 0.0;
                //print banner
                System.out.println ("**************************");
                System.out.println ("***** Customer Owes ******");
                System.out.println ("**************************");
                // calculate outstanding
                while (e.hasMoreElements()) {
                        Order each = (Order) e.nextElement();
                        outstanding += each.getAmount();
                }
                //print details
                System.out.println ("name: " + this._name);
                System.out.println ("amount: " + outstanding);
        }

        public static void main(String args[])
        {
             int[] prices = {10, 20, 30, 40, 50};   
             Extract_method test = new Extract_method("My Order", prices);   
             test.printOwing();
        }
}
