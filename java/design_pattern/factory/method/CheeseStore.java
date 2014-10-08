
class CheeseStore extends PizzaStore{
        Pizza createPizza(){
                return new CheesePizza();
        }
}
