class bub_int
{

        public static void display(int[] num)
        {
                for(int i = 0 ; i < num.length ; i++)
                {
                        System.out.print(num[i] + " ");
                }
                System.out.println();
        }
        public static void swap(int[] num, int i, int j)
        {
                int tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
        }
        public static void main(String args[])
        {
                int[] num = {5, 10, 11, 90, 33, 1, 4, 199, 67, 78};
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
