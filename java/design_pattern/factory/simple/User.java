
public class User{
        public static void main(String args[])
        {
                PizzaStore ps = new PizzaStore(new SimplePizzaFactory());
                ps.orderPizza("cheese");
        }
}
