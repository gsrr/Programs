package example.Inline_temp;


class AnOrder
{
        int _price;
        public AnOrder(int price)
        {
                this._price = price;
        }

        public int basePrice()
        {
                return this._price;
        }
}

class Inline_temp
{
        AnOrder anOrder;
        public Inline_temp(AnOrder a)
        {
                anOrder = a;
        }
        public boolean isPriceBigger()
        {
                double basePrice = anOrder.basePrice();
                return (basePrice > 1000);
        }
        public static void main(String args[])
        {
                Inline_temp test = new Inline_temp(new AnOrder(800));
                System.out.println("Is price bigger than 1000 :" + test.isPriceBigger());
        }
}

