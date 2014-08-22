#include<iostream>
#include<algorithm>

using namespace std;

struct Book
{
        int printT;
        int bindT;
};

bool compare(Book a, Book b)
{
        return a.bindT>b.bindT;
}

int main()
{
        while(1)
        {
                int n;
                cin >> n;
                if(n == 0)
                {
                        break;
                }
                struct Book *book = (struct Book*) malloc(n * sizeof(struct Book));
                for(int i=0; i<n; i++)
                {
                        cin >> book[i].printT >> book[i].bindT;
                }
                sort(book, book+n, compare);
                int finalPrintT = 0, finalBindT = 0, finalT = 0;

                for(int i=0; i<n; i++)
                {
                        finalPrintT += book[i].printT; 
                        if ( (finalPrintT + book[i].bindT ) > finalT)
                                finalT = finalPrintT + book[i].bindT;

                }

                cout << finalT << "\n";     
                free(book);
        }

}
