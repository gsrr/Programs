package example.Replace_Temp_with_Query;

class Replace_Temp_with_Query
{
        int _quantity;
        int _itemPrice;

        public Replace_Temp_with_Query(int quantity, int itemPrice)
        {
                this._quantity = quantity;
                this._itemPrice = itemPrice;
        }
        public double getBasePrice()
        {
                double basePrice = this._quantity * this._itemPrice;
                if (basePrice > 1000)
                        return basePrice * 0.95;
                else
                        return basePrice * 0.98;

        }
        public static void main(String args[])
        {
                Replace_Temp_with_Query test = new Replace_Temp_with_Query(5, 300);
                System.out.println("BasePrice: " + test.getBasePrice());
        }
}
