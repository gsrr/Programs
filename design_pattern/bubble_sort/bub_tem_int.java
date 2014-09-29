public class bub_tem_int extends bub_abs_tem
{
        private int[] num = {5, 10, 11, 90, 33, 1, 4, 199, 67, 78};
        
        public void display()
        {
                for(int i = 0 ; i < num.length ; i++)
                {
                        System.out.print(num[i] + " ");
                }
                System.out.println();
        }
        public void swap(int i, int j)
        {
                int tmp = num[i];
                num[i] = num[j];
                num[j] = tmp;
        }
        public boolean outOrder(int i , int j)
        {
                if(num[i] > num[j])
                {
                        return true;
                }
                else
                {
                        return false;
                }
        }
        public void setLength()
        {
                this.length = num.length;
        }
        public static void main(String args[])
        {
                bub_abs_tem act = new bub_tem_int();
                act.setLength();
                act.do_sort();
        }
}
