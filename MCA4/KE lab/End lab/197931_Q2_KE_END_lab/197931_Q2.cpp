/*
Nikunj Verma
197931
*/
#include<bits/stdc++.h>
using namespace std;

vector<double> sum(2,0);
vector<int> num(2,0);
map<pair<string,bool>,int> sup;
map<string,double> conf;
map<string,char> alias;

vector<string> splitter(string& s)
{
	int n = s.size();
	int i=0, j=0;
	vector<string> ans;
	while(i<n)
	{
		while(i<n && s[i] == ' ') i++;
		j = i;
		while(j<n && s[j] != ' ') j++;
		ans.push_back(s.substr(i, j-i));
		i = ++j;
	}
	return ans;
}
vector<vector<string>> ReadIp(string file)
{
	ifstream fin(file);
	vector<vector<string>> ans;
	while(!fin.eof())
	{
		string s;
		getline(fin,s);
		ans.push_back(splitter(s));
	}
	return ans;
}


void Making_Combination(vector<string>& data, string s="", int i=1)
{
	if(i == data.size()-1)
	{
		if(s != "")
		{
			sup[{s,false}]++;
			sup[{s + data[i], true}]++;
		}
		return;
	}
	Making_Combination(data, s, i+1);
	Making_Combination(data, s+data[i], i+1);
}
void Find_Support(vector<vector<string>>& data)
{	
	int n = data.size();
	sup.clear();
	for(int i=1; i<n; i++)
	{
		Making_Combination(data[i]);
	}
}

void TestMaker(vector<string>& data, string s="", int i=0)
{
	if(i == data.size())
	{
		if(s != "")
		{
			if(sup[{s,false}] >= 3)
			{
				if(conf.find(s+"yes") != conf.end())
				{
					num[1]++;
					sum[1] += conf[s+"yes"];
				}
				if(conf.find(s+"no") != conf.end())
				{
					num[0]++;
					sum[0] += conf[s+"no"];
				}
			}
		}
		return;
	}
	TestMaker(data, s, i+1);
	TestMaker(data, s+data[i], i+1);
}

void calculate_Confidence()
{
	conf.clear();
	
	for(auto i: sup)
	{
		if(i.first.second || i.second < 3) continue;
		string s = i.first.first;
		if(sup[{s+"yes",true}] >= 3)
		{
			double x = double(sup[{s+"yes",true}])/sup[{s,false}];
			if(x >= 0.3) conf[s+"yes"] = x;
		}
		if(sup[{s+"no",true}] >= 3)
		{
			double x = double(sup[{s+"no",true}])/sup[{s,false}];
			if(x >= 0.3) conf[s+"no"] = x;
		}
	}
}

string Finding_label(vector<string>& data)
{
	sum[0] = 0;
	sum[1] = 0;
	num[0] = 0;
	num[1] = 0;
	TestMaker(data);
	if(num[0]) sum[0] /= num[0];
	if(num[1]) sum[1] /= num[1];
	
	for(auto i: data) cout<<i<<" ";
	
	cout<<"Yes: "<<sum[1]<<"  No:"<<sum[0]<<endl;
		
	return (sum[0] >= sum[1])?"no":"yes";
}

void Testing_it()
{
	auto data = ReadIp("Test_data.txt");
	
	ofstream fout("Output.txt");
	
	int n = data.size();
	for(int i=0; i<n; i++)
	{
		for(auto j: data[i]) fout<<j<<" ";
		fout<<Finding_label(data[i])<<endl;
	}
}


void Solving(vector<vector<string>>& data)
{
	Find_Support(data);
	calculate_Confidence();
	for(auto i: conf)
	{
		cout<<i.first<<" "<<i.second<<endl;
	}
	Testing_it();
}

int main()
{
	vector<vector<string>> data = ReadIp("Train_data.txt");
	Solving(data);
	
	return 0;
}
