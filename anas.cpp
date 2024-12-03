#include<iostream>
using namespace std;
int main ()
{
	int x=0,y=1;
	x=++x;
	y=x++;
	y=y++;
	cout<<x<<endl;
	cout<<y<<endl;
}
