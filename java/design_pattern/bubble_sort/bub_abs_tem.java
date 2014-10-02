abstract class bub_abs_tem
{
        protected int length = 0;
        public void do_sort()
        {
                display();
                for(int i = 0 ; i < length; i++)
                {
                        for(int j = 0 ; j < length - 1 - i ; j++)
                        {
                                if(outOrder(j, j+1))
                                {
                                        swap(j, j+1);
                                }
                        }
                }
                display();
        
        }
        public abstract void display();
        public abstract void swap(int i, int j);
        public abstract boolean outOrder(int i , int j);
        public abstract void setLength();
}
