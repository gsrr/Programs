#include <stdio.h>
#include <stdlib.h>



struct point
{
        int p1;
        int p2;
};


int triangleArea(struct point p1, struct point p2, struct point p3)
{
        int a = p1.p1;
        int b = p1.p2;
        int c = p2.p1;
        int d = p2.p2;
        int e = p3.p1;
        int f = p3.p2;
        return abs(a * d + c * f + b * e - b * c - d * e - a * f);
}
int main()
{
        struct point points[200];
        int n;
        while(scanf("%d", &n) != EOF)
        {
                int a,b;
                int i,j,k;
                for(i = 0 ; i < n ; i++)
                {
                        scanf("%d %d", &a, &b);
                        struct point temp;
                        temp.p1 = a;
                        temp.p2 = b;
                        points[i] = temp;
                }
                int maxValue = 0;
                for (i = 0 ; i < n ; i++)
                {
                        for(j = i + 1 ; j < n ; j++)
                        {
                                for(k = j + 1 ; k < n ; k++)
                                {
                                        int area = triangleArea(points[i], points[j], points[k]);
                                        if (area > maxValue)
                                        {
                                                maxValue = area;
                                        }
                                }
                        }
                }
                printf("%.2f\n", maxValue / 2.0);
        }
                      
        return 0;
}
