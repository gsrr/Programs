package example.Introduce_Explaining_Variable;

import java.lang.Math; 

class Introduce_Explaining_Variable_ex1
{
        int _quantity;
        int _itemPrice;

        public Introduce_Explaining_Variable_ex1(int quantity, int itemPrice)
        {
                this._quantity = quantity;
                this._itemPrice = itemPrice;
        }

        public double price() 
        {
                return this._quantity * this._itemPrice - Math.max(0, this._quantity - 500) * this._itemPrice * 0.05 + Math.min(this._quantity * this._itemPrice * 0.1, 100.0);

        }

        public static void main(String args[])
        {
                Introduce_Explaining_Variable_ex1 test = new Introduce_Explaining_Variable_ex1(20, 100);
                System.out.println(test.price());
        }
}
