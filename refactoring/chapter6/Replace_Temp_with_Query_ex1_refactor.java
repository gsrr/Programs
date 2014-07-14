package example.Replace_Temp_with_Query;

class Replace_Temp_with_Query_ex1_refactor
{
        int _quantity;
        int _itemPrice;

        public Replace_Temp_with_Query_ex1_refactor(int quantity, int itemPrice)
        {
                this._quantity = quantity;
                this._itemPrice = itemPrice;
        }
        public int basePrice()
        {
                return this._quantity * this._itemPrice;
        }
        public double discountFactor()
        {
                if (basePrice() > 1000) 
                        return 0.95;
                else 
                        return 0.98;
        }
        public double getPrice()
        {
                double discountFactor = discountFactor();
                return basePrice() * discountFactor;
        }
        public static void main(String args[])
        {
                Replace_Temp_with_Query_ex1_refactor test = new Replace_Temp_with_Query_ex1_refactor(5, 300);
                System.out.println("BasePrice: " + test.getPrice());
        }
}
