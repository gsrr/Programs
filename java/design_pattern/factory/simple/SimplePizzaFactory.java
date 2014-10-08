public class SimplePizzaFactory
{
        public Pizza createPizza(String type)
        {
                if(type.equals("cheese"))
                {
                        return new CheesePizza();
                }
                else
                {
                        return null;
                }
        }
}
