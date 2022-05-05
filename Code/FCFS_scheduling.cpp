#include<iostream>
#include<map>
#include<vector> 
#include<algorithm>
using namespace std;
    
//for storing process with its BT and AT
map<int,vector<int>> prc; 
//for storing the process indices, used in gantt chart
map<pair<int,int>,vector<int>> indexing;
//for calculating results
vector<int> t_calc;
//global variable for storing number of process
int num_process = 0;
    
void input_Process()
{
    //local variable for storing number of process
    int number;
    int a_time;
    int b_time;
    
    cout<<"\t\tEnter Process Details : "<<"\n";
    cout<<"Enter Number of Process : ";
    cin>>number;
    num_process = number;
    cout<<"\n"<<"  Process"<<"\n";
    for(int i = 0;i<number;i++)
    {
        cout<<"  P["<<i+1<<"]"<<"\t\t"<<"Burst Time : ";
        cin>>b_time;
        cout<<"\t\t"<<"Arrival Time : ";
        cin>>a_time;
        cout<<"\n";
        prc[a_time].push_back(b_time);
        indexing[{a_time,b_time}].push_back(i + 1);
    }
}
    
void Gantt_Chart()
{
    cout<<"Gantt Chart : "<<"\n\n";
    auto i = prc.begin();
    if(i->first != 0)
    {
        cout<<" ||||";
    }
    for( ;i != prc.end();i++)
    {
        if((i->second).size() > 1)
        {
            sort((i->second).begin(),(i->second).end());
        }
        for(int j = 0;j<(i->second).size();j++)
        {
            if(j == 0 && i == prc.begin())
            {
                t_calc.push_back(i->first);
                t_calc.push_back((i->second)[0]);
            }
            else
            {
                t_calc.push_back((i->second)[j]);
            }
            cout<<" ||||[P"<<indexing[{i->first,(i->second)[j]}][0]<<"]||||";
            indexing[{i->first,(i->second)[j]}].erase(indexing[{i->first,(i->second)[j]}].begin());
        }
    }
    cout<<"\n";
    int prev = 0;
    for(int i = 0;i < t_calc.size();i++)
    {
        if(t_calc[i] != 0 && i == 0)
        {
            cout<<"0"<<"    ";
        }
        cout<<prev + t_calc[i]<<"           ";
        prev += t_calc[i];
        t_calc[i] = prev;
    }
    cout<<"\n";
}
    
void Result_Calc()
{
    cout<<"\n"<<"Results : "<<"\n\n";
    //Average waiting time
    double waiting_time = 0.0,n_wt = 0.0,d_wt = 0.0;
    int it = 0;
    for(auto i = prc.begin();i!=prc.end();i++)
    {
        for(int j = 0;j<(i->second).size();j++)
        {
            n_wt += t_calc[it] - (i->first);
            d_wt += 1;
            it++;
        }
    }
    cout<<"Average Waiting Time : "<<n_wt/d_wt<<"\n";
    
    //Average turnaround time
    double turaround_time = 0.0,n_tt = 0.0,d_tt = 0.0;
    it = 1;
    for(auto i = prc.begin();i!=prc.end();i++)
    {
        for(int j = 0;j<(i->second).size();j++)
        {
            n_tt += t_calc[it] - (i->first);
            d_tt += 1;
            it++;
        }
    }
    cout<<"Average Turnaround Time : "<<n_tt/d_tt<<"\n";
    
    //Throughput = schedule Length / number of process
    //schedule Length = last Completion time - first response time
    int schedule_length = t_calc[t_calc.size()-1] - (prc.begin())->first;
    cout<<"Throughput : "<<double(schedule_length)/num_process;
}
    
int main()
{
    //for taking process details input 
    input_Process();
    //for constructing gantt chart
    Gantt_Chart();
    //for calculation of waiting time etc
    Result_Calc();
    return 0;
}