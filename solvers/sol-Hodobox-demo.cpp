#include <iostream>

using namespace std;

void eat()
{
    string s;
    while(getline(cin,s)) ;
}

string coms[] = {"0","take torch","east","take key","south"};

int main()
{
    for(int i=0;i<5;++i)
    {
        cout << coms[i] << endl;
    }
    eat();
}