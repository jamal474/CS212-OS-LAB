#include<bits/stdc++.h>
using namespace std;

int main()
{
    /* n - number of reference elements
       frames - number of frames in memory
       fault - number of page faults
       hit - number of page hits
       front - keep the "first in" element's index
    */
    int n, frames, fault = 0,hit = 0,front = 0;

    cout<<"Enter reference string size : ";
    cin>>n;

    //  ref_s - stores reference string
    int ref_s[n];
    cout<<"Enter reference string : ";
    for(int i = 0;i<n;i++)
    {
        cin>>ref_s[i];
    }
    cout<<"Enter number of page frames : ";
    cin>>frames;

    //table - its to show memory status
    vector<vector<int>> table(frames);
    for(int i = 0;i<frames;i++)
    {
        table[i] = vector<int>(n,-1);
    }

    // cur_mem - stores current position of memory
    vector<int> cur_mem(frames,-1);

    //inlist - it shows if an element was already present in memory or not
    bool inlist = false;
    for(int i = 0;i<n;i++)
    {
        inlist = false;
        for(int j = 0;j<frames;j++)
        {
            if(cur_mem[j] == ref_s[i])
            {
                hit++;
                inlist = true;
                break;
            }
            if(cur_mem[j] == -1)
            {
                fault++;
                cur_mem[j] = ref_s[i];
                inlist = true;
                break;
            }
        }
        if(inlist == false)
        {
            fault++;
            cur_mem[front] = ref_s[i];
            front = (front + 1)%frames;
        }
        for(int j = 0;j<frames;j++)
        {
            table[j][i] = cur_mem[j];
        }
    }


    // X - in the ouput means that frame is empty
    cout<<"\nref. str ";
    for(int i = 0;i<n;i++)
    {
        cout<<ref_s[i]<<" ";
    }
    cout<<"\n\n";
    for(int i = 0; i<frames;i++)
    {
        cout<<"Frames : ";
        for(int j =  0;j<n;j++)
        {
            if(table[i][j] == -1)
            {
                cout<<"X"<<" ";
            }
            else
            {
                cout<<table[i][j]<<" ";
            }
        }
        cout<<endl;
    }

    //Result
    cout<<"\tResult"<<endl;
    cout<<"\t\tFaults : "<<fault<<endl;
    cout<<"\t\tHits   : "<<hit<<endl;

    return 0;
}