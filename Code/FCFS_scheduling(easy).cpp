#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//structure to store process detail
struct Process
{
    string name;
    int arrival_time;
    int burst_time;
};

//helpful in sorting the process by arrival time
bool a_t_sort(Process a,Process b)
{
    return a.arrival_time < b.arrival_time; 
}

void input_process(vector<Process> &Proc)
{
    //taking input 
    for(int i = 0;i<Proc.size();i++)
    {
        cout<<"p["<<i+1<<"] : ";
        Proc[i].name = to_string(i+1);

        cout<<"Arrival time : ";
        cin>>Proc[i].arrival_time;
        cout<<"       ";

        cout<<"Burst Time : ";
        cin>>Proc[i].burst_time;
        cout<<"\n";
    }
}

void Gantt_chart_n_Result(vector<Process> &Proc)
{
    //Gantt Chart
    sort(Proc.begin(),Proc.end(),a_t_sort);

    cout<<"\nGantt Chart : "<<"\n\n";
    vector<int> time22;
     if(Proc[0].arrival_time != 0)
    {
        cout<<"|||";
        time22.push_back(0);
    }
    time22.push_back(Proc[0].arrival_time);
    for (int i=0; i<Proc.size(); i++)
    {
        time22.push_back(Proc[i].burst_time) ;
    }
    for (int i=0; i<Proc.size(); i++)
    {
        cout<<" |||P["<< Proc[i].name << "]|||"; 
    }
    cout<<"|\n"<<time22[0]<<"   ";
    for(int i = 1;i<time22.size();i++)
    {
        time22[i] = time22[i] + time22[i-1];
        cout<<time22[i]<<"         ";
    }
    
    cout<<"\n\nResults : \n\n";

    //Waiting Time
    double waiting_time = 0.0;
    int i = 0;
    if(Proc[0].arrival_time != time22[0])
    {
        i = 1;
    }
    int temp = 0;
    for( ; i < time22.size() - 1 ;i++)
    {
        waiting_time = waiting_time - Proc[temp].arrival_time + time22[i];
        temp++;
    }
    cout<<"Average Waiting Time : "<<waiting_time/Proc.size()<<"\n";

    //Turnaround Time
    double turnaround_time = 0.0;
    i = 1;
    if(Proc[0].arrival_time != time22[0])
    {
        i = 2;
    }
    temp = 0;
    for( ; i < time22.size();i++)
    {
        turnaround_time = turnaround_time - Proc[temp].arrival_time + time22[i];
        temp++;
    }
    cout<<"Average Turaround Time : "<<turnaround_time/Proc.size()<<"\n";
}

int main()
{
    int n;
    cout<<"\t\tEnter Process Details : "<<"\n";
    cout<<"Enter the number of Process : ";
    cin>>n;

    //vector to store processes
    vector<Process> Proc(n);

    //input process detail
    input_process(Proc);

    //Calculate Gantt Chart and results
    Gantt_chart_n_Result(Proc);
    
    return 0;
}