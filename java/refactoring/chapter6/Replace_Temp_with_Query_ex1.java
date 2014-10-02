package example.Replace_Temp_with_Query;

class Replace_Temp_with_Query_ex1
{
        int _quantity;
        int _itemPrice;

        public Replace_Temp_with_Query_ex1(int quantity, int itemPrice)
        {
                this._quantity = quantity;
                this._itemPrice = itemPrice;
        }
        public double getPrice()
        {
                int basePrice = _quantity * _itemPrice;
                double discountFactor;
                if (basePrice > 1000) discountFactor = 0.95;
                else discountFactor = 0.98;
                return basePrice * discountFactor;
        }
        public static void main(String args[])
        {
                Replace_Temp_with_Query_ex1 test = new Replace_Temp_with_Query_ex1(5, 300);
                System.out.println("BasePrice: " + test.getPrice());
        }
}
