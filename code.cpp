#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pages;
    int frames;
    int frameRage;
};

void solve(int start_frame, int frames, int n, vector <int> pages, int total_pages, int tlb_size, int curr_process)
{
    if(!frames)
    {
        cout << "No frames allocated to process " << curr_process<<endl;
        return;
    }

    int faults = 0;
    set <int> s;
    map <int, int> tlb, m, frameM;
    list <int> ffl;

    for(int i = start_frame; i < start_frame + frames; i++)
    {
        ffl.push_back(i);
    }

    vector <int> PT(total_pages);
    for(int i = 0; i < total_pages; i++)
    {
        PT[i] = -1;
    }

    int frame_no = 0;
    for(int i = 0; i < n ; i++)
    {
        if(tlb.find(pages[i]) != tlb.end())
        {
            cout << "Process " << curr_process << ":for page reference " << pages[i] << ", TLB hit with frame no." << tlb[pages[i]] << endl;
            m[pages[i]] = i;
        }
        else
        {
            if(PT[pages[i]] != -1)
            {
                cout << "Process " << curr_process << ":for page reference " << pages[i] << ", TLB miss->page table valid->with frame no." << PT[pages[i]] << endl;
                if(tlb.size() < tlb_size)
                {
                    tlb[pages[i]] = PT[pages[i]];
                }
                else
                {
                    int TLB_page = INT_MAX;
                    int value;
                    for(auto x = tlb.begin(); x != tlb.end(); x++)
                    {
                        if(m[x->first] < TLB_page)
                        {
                            TLB_page = m[x->first];
                            value = x->first;
                        }
                    }
                    tlb.erase(value);
                    tlb[pages[i]] = PT[pages[i]];
                }
                m[pages[i]] = i;
            }
            else
            {
                faults++;
                cout << "Process " << curr_process << ":for page reference " << pages[i] << ", TLB miss->page table invalid->handing page fault.... ->";
                if(frame_no<frames)
                {
                    PT[pages[i]] = frame_no + start_frame;
                    frameM[pages[i]] = frame_no + start_frame;
                    if(tlb.size() < tlb_size)
                    {
                        tlb[pages[i]] = PT[pages[i]];
                    }
                    else
                    {
                        int TLB_page = INT_MAX;
                        int value;
                        for(auto x = tlb.begin(); x != tlb.end(); x++)
                        {
                            if(m[x->first] < TLB_page)
                            {
                                TLB_page = m[x->first];
                                value = x->first;
                            }
                        }
                        tlb.erase(value);
                        tlb[pages[i]] = PT[pages[i]];
                    }
                    frame_no++;
                    m[pages[i]] = i;
                }
                else
                {
                    int LRU_page = INT_MAX;
                    int value;
                    for(auto x = frameM.begin(); x != frameM.end(); x++)
                    {
                        if(m[x->first] < LRU_page)
                        {
                            LRU_page = m[x->first];
                            value = x->first;
                        }
                    }
                    int frameAlloted = frameM[value];
                    frameM.erase(value);
                    PT[value] = -1;
                    tlb.erase(value);
                    frameM[pages[i]] = frameAlloted;
                    PT[pages[i]] = frameAlloted;
                    tlb[pages[i]] = PT[pages[i]];
                    m[pages[i]] = i;
                }
                cout << "frames alloted = " << frameM[pages[i]] << endl;
            }
        }
    }
    cout << "Process " << curr_process << " finished" << endl;
    cout << "Number of page faults : " << faults << endl;
}

int main()
{
    srand (time(NULL));
    int k, m, f, s;
    cout << "Enter total number of process : ";
    cin >> k;
    cout << "Enter maximum number of pages per process : ";
    cin >> m;
    cout << "Enter total number of frames in main memory : ";
    cin >> f;
    cout << "Enter size of tlb : ";
    cin >> s;

    int t = k;
    process p[k];
    int mt = 0;

    for(int i = 0; i < k; i++){
        int mi = rand() % m + 1;
        p[i].pages = mi;
        mt += mi;
    }

    cout << "Pages allocated to each process : ";
    for(int i = 0; i < k; i++) 
    {    
        cout << p[i].pages << " ";
    }
    cout << endl;

    for(int i = 0; i < k; i++)
    {
        float x = ((float)p[i].pages / (float)mt);
        p[i].frames = round(x * f);
        p[i].frameRage = (i == 0) ? p[i].frames : (p[i].frames + p[i - 1].frameRage);
    }

    cout << "Frames allocated to each process : ";
    for(int i = 0; i < k; i++)
    {
        cout << p[i].frames <<  " ";
    }
    cout << endl;

    cout << "Frame Range allocated to each process : ";
    for(int i = 0; i < k; i++)
    {
        cout << p[i].frames << " ";
    }
    cout << endl;
    
    while (t--)
    {
        int curr_process = rand()%k;
        cout << "Process Number : " << curr_process<<endl;

        vector <int> ref_string;
        for(int i = 0;i < 2 * m; i++)
        {
            int temp = rand() % p[curr_process].pages;
            ref_string.push_back(temp);
        }

        cout<<"Referance string : ";
        for(int i = 0; i < ref_string.size() ; i++)
        {
            cout << ref_string[i] << " ";
        }
        cout << endl;

        int frames = (curr_process == 0) ? p[0].frameRage : (p[curr_process].frameRage - p[curr_process - 1].frameRage);
        int start_frame = (curr_process == 0) ? 0 : p[curr_process - 1].frameRage;

        solve(start_frame,frames, 2 * m, ref_string, p[curr_process].pages, s, curr_process);
    }
    return 0;
}