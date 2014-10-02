public class bub
{
        protected int length = 0;
        public void do_sort(Handler handle)
        {
                length = handle.getLength();
                handle.display();
                for(int i = 0 ; i < length ; i++)
                {
                        for(int j = 0 ; j < length - 1 - i ; j++)
                        {
                                if(handle.outOrder(j))
                                {
                                        handle.swap(j);
                                }
                        }
                }
                handle.display();
        }

}
