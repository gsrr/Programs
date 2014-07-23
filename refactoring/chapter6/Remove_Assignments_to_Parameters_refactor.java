package example.Remove_Assignments_to_Parameters;


public class Remove_Assignments_to_Parameters_refactor
{
        
        public int discount (int inputVal, int quantity, int yearToDate) 
        {
                int result = inputVal;
                if (inputVal > 50) result -= 2;
                if (quantity > 100) result -= 1;
                if (yearToDate > 10000) result -= 4;
                return result;
        }

        public static void main(String args[])
        {
                Remove_Assignments_to_Parameters_refactor test = new Remove_Assignments_to_Parameters_refactor();
                System.out.println(test.discount(100, 50, 10001));        
        }
}

