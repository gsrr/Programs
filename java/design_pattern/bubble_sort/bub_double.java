class bub_double
{

        public static void display(double[] num)
        {
                for(int i = 0 ; i < num.length ; i++)
                {
                        System.out.print(num[i] + " ");
                }
                System.out.println();
        }
        public static void swap(double[] num, int i, int j)
        {
                double tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
        }
        public static void main(String args[])
        {
                double[] num = {5.01, 10.22, 11.33, 90.44, 33.11, 1.33, 4.22, 199.77, 67.66, 78.99};
                display(num);
                
                for(int i = 0 ; i < num.length ; i++)
                {
                        for(int j = i + 1 ; j < num.length ; j++)
                        {
                                if(num[i] > num[j])
                                {
                                        swap(num , i , j);
                                }
                        }
                }
                display(num);
        }
}
