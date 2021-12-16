//Pratik Chowdhury,197937
//no output file is generated, result is shown in command prompt
//works for any dataset(check .txt files for generalized data format input), need to explicitly mention class label column
//mentioned class label column, will be treated as the prediction class and other columns as features
#include<bits/stdc++.h>
using namespace std;
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};
int train_size;
unordered_map<string,int> class_label_count;
unordered_map<string,int> class_label_index;
unordered_map<pair<string,string>,vector<int>,hash_pair> given_class_label_feature_count;
unordered_map<pair<string,string>,vector<float>,hash_pair> probabilities; //contains all possible probabilities combinations

vector<string> tokenizer(string s)
{
    stringstream ss(s);
    string word;
    vector<string> v;
    while(ss>>word){
        v.push_back(word);
    }
    return v;
}

vector<vector<string>> read_data(string file_name)
{
    ifstream fin;
    string line;
    vector<vector<string>> data;
    fin.open(file_name);
    while(fin)
    {
        getline(fin,line);
        data.push_back(tokenizer(line));
    }
    data.pop_back(); //last line from data was getting readed 2 times, don't know why
    train_size = data.size()-1;
    return data;
}
int find_class_label_index(vector<vector<string>> data,string class_label){
    int index = -1;
    for(int i=0;i<data[0].size();i++)
    {
        if(data[0][i]==class_label) index=i;
    }
    return index;
}
void train_helper(vector<vector<string>> data,string class_label)
{
    int index = find_class_label_index(data,class_label);
    int t=0;
    for(int i=1;i<data.size();i++) {
        string s = data[i][index];
        class_label_count[s]++;
        if(class_label_count[s] == 1) class_label_index[s] = t++;
    }
    for(int j=0;j<data[0].size();j++)
    {
        if(j==index) continue;
        for(int i=1;i<data.size();i++)
        {
            pair<string,string> p(data[0][j],data[i][j]);
            if(given_class_label_feature_count.find(p) == given_class_label_feature_count.end())
                given_class_label_feature_count[p] = vector<int>(class_label_index.size());
            int label_index = class_label_index[data[i][index]];
            given_class_label_feature_count[p][label_index]++;
        }
    }
}
void calculate_probabilities()
{
    for(auto i: given_class_label_feature_count)
    {
        pair<string,string> p = i.first;
        vector<int> t = i.second;
        vector<float> t_2;
        for(int i=0;i<t.size();i++){
            for(auto it = class_label_index.begin();it!=class_label_index.end();it++)
                if(it->second == i) t_2.push_back(float(t[i])/class_label_count[it->first]);
        }
        probabilities[p] = t_2;
    }
}
void train_model(vector<vector<string>> data,string class_label)
{
    train_helper(data,class_label);
    calculate_probabilities();
}
void test_model(string file_name,string class_label,string output_file)
{
    ofstream fout;
    fout.open(output_file);
    vector<vector<string>> data = read_data(file_name);
    int index = find_class_label_index(data,class_label);
    vector<string> class_labels(class_label_index.size());
    for(auto it: class_label_index)
        class_labels[it.second] = it.first;
    if(file_name == "validate.txt") fout<<"Validation Data"<<endl<<endl;
    else fout<<"Testing Data"<<endl<<endl;
    for(int i=0;i<data[0].size();i++) fout<<data[0][i]<<" ";
    fout<<endl;
    for(int i=1;i<data.size();i++)
    {
        vector<float> bayes_probabilities(class_label_index.size(),1);
        for(int j=0;j<data[i].size();j++)
        {
            fout<<data[i][j]<<" ";
            if(file_name=="validate.txt" and j==index) continue;
            pair<string,string> p(data[0][j],data[i][j]);
            for(int k=0;k<class_label_index.size();k++) bayes_probabilities[k]*= probabilities[p][k];
        }
        fout<<endl;
        for(int k=0;k<class_label_index.size();k++) bayes_probabilities[k]*= (float)class_label_count[class_labels[k]]/train_size;
        pair<string,float> prediction("",-1);
        for(int k=0;k<class_label_index.size();k++){
            if(bayes_probabilities[k]>prediction.second) {prediction.second = bayes_probabilities[k]; prediction.first = class_labels[k];}
            fout<<"P("<<class_labels[k]<<"/X) : "<<bayes_probabilities[k]<<endl;
        }
        fout<<"Predction : "<<prediction.first<<endl;

    }
}
void print_data(vector<vector<string>> data)
{
    for(int i=0;i<data.size();i++)
    {
        for(int j=0;j<data[i].size();j++)
        {
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    print_data(read_data("train.txt"));
    train_model(read_data("train.txt"),"Class:buys_computer");
    test_model("validate.txt","Class:buys_computer","output_validate.txt");
    test_model("test.txt","Class:buys_computer","output_test.txt");
}
