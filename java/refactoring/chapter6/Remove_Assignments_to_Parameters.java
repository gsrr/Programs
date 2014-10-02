package example.Remove_Assignments_to_Parameters;


public class Remove_Assignments_to_Parameters
{
        
        public int discount (int inputVal, int quantity, int yearToDate) 
        {
                if (inputVal > 50) inputVal -= 2;
                if (quantity > 100) inputVal -= 1;
                if (yearToDate > 10000) inputVal -= 4;
                return inputVal;
        }

        public static void main(String args[])
        {
                Remove_Assignments_to_Parameters test = new Remove_Assignments_to_Parameters();
                System.out.println(test.discount(100, 50, 10001));        
        }
}

