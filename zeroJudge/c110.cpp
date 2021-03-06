#include <stdio.h>



int number_six(int nums[])
{
        return nums[6];
}

int number_five(int nums[])
{
        nums[1] = nums[1] - 11 * nums[5];
        return nums[5];
}

int number_four(int nums[])
{
        nums[2] = nums[2] - 5 * nums[4];
        return nums[4];
}

int number_three(int nums[])
{
        int box = nums[3] / 4;
        nums[3] = nums[3] % 4;
        switch(nums[3])
        {
                case 3:
                        nums[2] = nums[2] - 1;
                        nums[1] = nums[1] - 5;
                        return box + 1; 
                case 2:
                        nums[2] = nums[2] - 3;
                        nums[1] = nums[1] - 6;
                        return box + 1;
                case 1:
                        nums[2] = nums[2] - 5;
                        nums[1] = nums[1] - 7;
                        return box + 1;
                case 0:
                        return box;

        }
}

int number_two(int nums[])
{
        int box = nums[2] / 9;
        nums[2] = nums[2] % 9;
        if(nums[2] != 0)
        {
                nums[1] = nums[1] - 4 * (9 - nums[2]);
                return box + 1;
        }
        else
        {
                return box;
        }
}

int number_one(int nums[])
{
        if(nums[2] < 0)
        {
                nums[1] = nums[1] - 4 * (-1) * nums[2];
        }
        if(nums[1] <= 0)
        {
                return 0;
        }

        int box =  nums[1] / 36;
        nums[1] = nums[1] % 36;
        if(nums[1] != 0)
        {
                return box + 1;
        }
        else
        {
                return box;
        }
}

int box_number(int i , int nums[])
{
        if(nums[i] <= 0)
        {
                return 0;
        }

        switch(i)
        {
                case 6:
                        return number_six(nums);
                        break;
                case 5:
                        return number_five(nums);
                        break;
                case 4:
                        return number_four(nums);
                        break;
                case 3:
                        return number_three(nums);
                        break;
                case 2:
                        return number_two(nums);
                        break;
                case 1:
                        return number_one(nums);
                        break;
        }
}

int main()
{
        int num[7];
        while(scanf("%d %d %d %d %d %d",&num[1],&num[2],&num[3],&num[4],&num[5],&num[6]))
        {
                int i;
                for(i = 1 ; i <= 6 ; i++)
                {
                        if(num[i] != 0) 
                        {
                                break;
                        }
                }
                if(i==7) break;
                
                int sum = 0;
                for( i = 6 ; i > 0 ; i--)
                {
                        if(num[i] > 0)
                        {
                                sum = sum + box_number(i , num);
                        }
                } 
                printf("%d\n",sum);
        }
        return 0;
}
