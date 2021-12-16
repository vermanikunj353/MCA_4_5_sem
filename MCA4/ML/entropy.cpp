#include<bits/stdc++.h>
using namespace std;
float entropy(float yes,float no,float total)
{
	float a=(yes/total);
	float b=(no/total);
	float en=(((-1)*a)* log2(a)) - (b* log2(b));
	return en;
}
int main()
{
	float yes,no,total;
	cout<<"total: ";
	cin>>total;
	cout<<"\nyes: ";
	cin>>yes;
	cout<<"\nno: ";
	cin>>no;
	cout<<entropy(yes,no,total);
	return 0;
}