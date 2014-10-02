package example.Inline_temp;


class Inline_temp_refactor
{
        AnOrder anOrder;
        public Inline_temp_refactor(AnOrder a)
        {
                anOrder = a;
        }
        public boolean isPriceBigger()
        {
                return (anOrder.basePrice() > 1000);
        }
        public static void main(String args[])
        {
                Inline_temp_refactor test = new Inline_temp_refactor(new AnOrder(1500));
                System.out.println("Is price bigger than 1000 :" + test.isPriceBigger());
        }
}

