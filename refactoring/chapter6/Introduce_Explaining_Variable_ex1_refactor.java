package example.Introduce_Explaining_Variable;

import java.lang.Math; 

class Introduce_Explaining_Variable_ex1_refactor
{
        int _quantity;
        int _itemPrice;

        public Introduce_Explaining_Variable_ex1_refactor(int quantity, int itemPrice)
        {
                this._quantity = quantity;
                this._itemPrice = itemPrice;
        }

        public double price() 
        {
                final double basePrice = this._quantity * this._itemPrice;
                final double quantityDiscount = Math.max(0, this._quantity - 500) * this._itemPrice * 0.05;
                final double shipping = Math.min(basePrice * 0.1, 100.0);
                return basePrice - quantityDiscount + shipping;
        }

        public static void main(String args[])
        {
                Introduce_Explaining_Variable_ex1_refactor test = new Introduce_Explaining_Variable_ex1_refactor(20, 100);
                System.out.println(test.price());
        }
}
