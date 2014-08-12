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
        int n;
        cin >> n;
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
                finalBindT = (finalPrintT + book[i].bindT );
                finalT = max(finalBindT, finalT);
        }

        cout << finalT;     

}
