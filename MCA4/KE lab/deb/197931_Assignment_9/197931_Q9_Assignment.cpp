/*
Nikunj Verma
197931
Assignment 9
*/
#include<bits/stdc++.h>
using namespace std;

int main()
{

    map<string,vector<string>> cols;
    map<string,int> cnt;
    map<string,map<string,double>> prob;
    vector<string> attr;
    ifstream fin("training.txt");
    string line,str="";
    getline(fin,line);
    for(auto x:line)
    {
        if(x=='\t')
        {
            cols[str]={};
            attr.push_back(str);
            str="";
        }
        else
            str+=x;
    }
    cols[str]={};
    attr.push_back(str);
    while(!fin.eof())
    {
        getline(fin,line);
        str="";
        int i=0;
        for(auto x:line)
        {
            if(x=='\t')
            {
                cols[attr[i]].push_back(str);
                str="";
                i++;
            }
            else
                str+=x;
        }
        cols[attr[i]].push_back(str);
    }
    fin.close();
    for(int i=0;i<attr.size()-1;++i)
    {
        string atr=attr[i];
        string cls=attr.back();
        for(int i=0;i<cols[atr].size();++i)
        {
            string k=cols[atr][i];
            string v=cols[cls][i];
            prob[k][v]++;
            cnt[k]++;
        }
    }
    for(auto x:prob)
    {
        for(auto y:x.second)
            prob[x.first][y.first]=y.second/cnt[x.first];
    }
    map<string,double> cls_prob;
    for(auto x:cols[attr.back()])
        cls_prob[x]++;

    for(auto x:cls_prob)
        cls_prob[x.first]=x.second/cols[attr.back()].size();

    fin.open("test.txt");
    ofstream fout("Output.txt");

    getline(fin,line);
    str="";
    for(auto x:line)
    {
        if(x=='\t')
        {
            fout<<str<<'\t';
            str="";
        }
        else
            str+=x;
    }
    fout<<str<<'\t';
    fout<<attr.back()<<'\n';
    map<string,double> res;
    while(!fin.eof())
    {
        vector<string> input_values;
        getline(fin,line);
        str="";
        int i=0;
        for(auto x:line)
        {
            if(x=='\t')
            {
                input_values.push_back(str);
                str="";
                i++;
            }
            else
                str+=x;
        }
        input_values.push_back(str);
        string rs;
        double mx=DBL_MIN;
        for(auto p:cls_prob)
        {
            double d=p.second;
            for(auto v:input_values)
                d*=prob[v][p.first];
            if(d>mx)
            {
                mx=d;
                rs=p.first;
            }
        }
        for(auto v:input_values)
            fout<<v<<'\t';
        fout<<rs<<'\n';
    }
    fin.close();
    fout.close();
    cout<<"See Output file that has generated!!";
    return 0;
}
