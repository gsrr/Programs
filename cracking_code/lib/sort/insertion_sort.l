

/* ::def#void insertion_sort(int* arr, int len, int val) :: */
void insertion_sort(int* arr, int len, int val)
{
        int i;
        for(i = len - 1 ; i > -1 ; i--)
        {
                if(arr[i] < val)
                {
                        arr[i + 1] = arr[i];
                }
                else
                {
                        break;
                }       
        }       
        arr[ i + 1] = value;
}
/* #end */
