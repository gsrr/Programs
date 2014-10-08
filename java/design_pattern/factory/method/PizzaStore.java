public abstract class PizzaStore{
        public Pizza orderPizza(){
                Pizza pizza = createPizza();
                pizza.prepare();
                pizza.bake();
                return pizza;
                        
        }
        abstract Pizza createPizza();
}


