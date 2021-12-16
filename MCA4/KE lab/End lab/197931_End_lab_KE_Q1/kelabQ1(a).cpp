/*
   Nikunj Verma
   197931
   MCA 2nd year
    (a) Values for the data are 22, 25, 25, 16, 19,25, 35, 36, __, 45, 25, 30,20, 20, 21, 22  35, 46, 52, 70, 13, __, 16,  33, 33, 35, 35,
	i. Write a cpp program to find the missing values using a missing value replacement  technique (other than replacing with global constant)
	ii. Find 1st and 3rd quartiles.
	iii. Write a cpp program to perform smoothing by equi-width binning.
*/
#include<bits/stdc++.h>
using namespace std;
void print(vector<int>v)
{
	for(auto i:v)
		cout<<i<<" ";
	cout<<endl;
}

void mean_replace(vector<int>&arr)
{
	int sum=0,cnt=0;
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]!=INT_MIN)
			sum += arr[i];
		else
			cnt++;
	}
	cnt=(arr.size())-cnt;
	int mean=(sum/cnt);
	replace(arr.begin(), arr.end(), INT_MIN,mean);
	cout<<"\n1. After substitute the missing values using Mean"<<endl;
	print(arr);

	fstream file1("Q_a(i)_output.txt",ios::out);
	file1<<"Nikunj Verma\nRoll No.197931\n\n";
	file1<<"after replacing missing value by mean we get: \n";
	for(auto i:arr)
		file1<<i<<" ";   

	file1.close();
}
void perform_mean(vector<int>&arr)
{
	cout<<"Here i'm denoting missing values by INT_MIN("<<INT_MIN<<")"<<endl;
	cout<<"initial values are: "<<endl;
	print(arr);
	mean_replace(arr);
}
void quartile(vector<int>arr)
{
	sort(arr.begin(),arr.end());
	int N=arr.size();
	int Q1=(N+1)/4;
	int Q3= 3 * (N+1)/4;
	cout<<"\n\n2.Quartiles: \n1st Quartile is: "<<arr[Q1-1]<<"\n3rd Quartile is:"<<arr[Q3-2]<<endl;
	fstream file1("Q_a(ii)_output.txt",ios::out);
	file1<<"Nikunj Verma\nRoll No.197931\n\n";
	file1<<"Quartiles are:\n";
	file1<<"1st Quartile: "<<arr[Q1-1]<<"\n";
	file1<<"3rd Quartile: "<<arr[Q3-1]<<"\n";

	file1.close();
}
void equi_width(vector<int>arr)
{
 	int n=arr.size();   
    int mn=arr[0],mx=-1;
    for(int i=0;i<n;i++)
    {
    	mn=min(mn,arr[i]);
    	mx=max(mx,arr[i]);
	}
	int no;
	cout<<"Enter Number of Bins: ";
	cin>>no;
	cout<<endl;

	vector<int>v(no+1);
    int w = (mx-mn)/no;
	for(int i=1;i<=no;i++)
	{
		v[i]=(mn+(w*(i)));
	 } 
	 vector<vector<int>>ans;
	 for(int i=0;i<no;i++)
	 {
	 	vector<int>b;
	 	for(int j=0;j<n;j++)
	 	{
	 		if(arr[j]>=v[i] && arr[j]<=v[i+1])
	 		b.push_back(arr[j]);
		 }
		 ans.push_back(b);
	 }

	 fstream file1("Q_a(iii)_output.txt",ios::out);
	 file1<<"Nikunj Verma\nRoll No.197931\n\n";
	 file1<<"Bin Size is: "<<no<<"\n\n";
	 file1<<"After smoothing by equi_width\n\n";
	 for(int i=0;i<ans.size();i++)
	 {
	 	for(int j=0;j<ans[i].size();j++)
	 	{
	 	file1<<ans[i][j]<<" ";
	 	cout<<ans[i][j]<<" ";
	 	}
	 	cout<<endl;
	 	file1<<"\n";
 	 }
 	 file1.close();
}
int main()
{

	vector<int>arr={22,25,25,16,19,25,35,36,INT_MIN,45,25,30,20,20,21,22,35,46,52,70,13,INT_MIN,16,33,33,35,35};
	perform_mean(arr);
	quartile(arr);
	equi_width(arr);
	return 0;
}