
public class Rhombus
{
        public void findFive(int[] arr)
        {
                String[] animals ={"cat", "fish", "dog"};
                int pos = 0;
                if(5 == arr[1])
                {
                        pos = 1;
                }
                else if(5 == arr[2])
                {
                        pos = 2;
                }
                
                
                System.out.println("The position of 5 is : " + (pos + 1));
                System.out.println("The animal type is : " + animals[pos]);

        }
        public static void main(String args[])
        {
                int[] arr = {7, 10, 5};
                Rhombus rh = new Rhombus();
                rh.findFive(arr);
        }
}
