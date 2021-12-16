#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream file("training.txt");
	int n=0;  
	int y=0;  
	string line;
	map<string,int> yes,no;
	while(!file.eof())
	{
		int cnt=0;
		getline(file,line);
		string arr[5];
		string s="";
		int j=0;
		for(int i=0;i<line.length();i++)
		{
			if(line[i]=='\t')
			{   
				arr[j]=s;
				s="";
				j++;
			}
			else
			{
				s=s+line[i];
			}
		}
		arr[4]=s;
		
		map<string,int>::iterator it;
		if(arr[4]=="no")  //storing the  count of 'no' class label various attributes
		{
			n++;
			j=0;
			for(int j=0;j<4;j++)
			{
				no[arr[j]]++;
			}	
		}
		if(arr[4]=="yes")  //storing the  count of 'yes' class label various attributes
		{
			y++;
			j=0;
			for(int j=0;j<4;j++)
			{
				yes[arr[j]]++;
			}	
		}
	}
	ofstream file3("nikku.txt");
	float p1,p2,p3,p4,pn=1,py=1;
	ifstream file4("test.txt");
	while(!file4.eof())
	{
		int c=0;
		getline(file4,line);
		
		string s="";
		for(int i=0;i<line.length();i++)
		{
			
		   if(line[i]==' ')
		   {
		    p1=yes[s];
		  
		   	p1=(float)p1/y;
		   	py=py*p1;
		   	
		   	p1=no[s];
		  
		   	p1=(float)p1/n;
		   	pn=pn*p1;
		   	
		   	s="";
			}
			else
			{
				s=s+line[i];
				}	
		}
		    p1=yes[s];
		  
		   	p1=(float)p1/y;
		   	py=py*p1;
		   	
		   	p1=no[s];
		  
		   	p1=(float)p1/n;
		   	pn=pn*p1;
		
		
		if(pn>=py)
		file3<<line<<" "<<"no"<<endl;
		else
		file3<<line<<" "<<"yes"<<endl;
		pn=1;
		py=1;
	}
	return 0;
}
