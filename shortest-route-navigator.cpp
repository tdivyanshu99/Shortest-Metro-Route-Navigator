#include <bits/stdc++.h>
using namespace std;

map<string,vector<pair<string,int>>> mpfinal;
map<string,string> info;

void make_graph(){
    mpfinal.clear();
    fstream fin;
    fin.open("metro-routes.txt",ios::in);
    int edges=0;
    string src,dest;
    int wt;
    map<string,vector<pair<string,int>>> mp;
    while(!fin.eof()){
        fin>>src>>dest>>wt;
        mp[src].push_back({dest,wt});
        mp[dest].push_back({src,wt});
        edges++;
    }
    fin.close();
    for(auto i:mp){
        string node=i.first;
        //cout<<i.first<<"--> ";
        int j;
        set<pair<string,int>> st;
        for(j=0;j<i.second.size();j++){
            st.insert({i.second[j].first,i.second[j].second});
        }
        for(auto z:st){
            mpfinal[node].push_back({z.first,z.second});
        }
        //cout<<endl;
    }
}

void Dijkstra(string src,string destination){
    bool flagSrc=false,flagDest=false;
    map<string,string> parent;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
        if(node==destination){
            flagDest=true;
        }
    }
    if(flagSrc==false || flagDest==false){
        cout<<"\nYou entered either wrong Source or destination, which is not part of our ecosystem.\n";
        return;
    }
    map<string,int> dist;
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; 
                auto f=st.find({dist[dest],dest}); 
                if(f!=st.end()){ 
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    if(dist[destination]==INT_MAX){
        cout<<"\nThese places are not connected to each other directly or indirectly\n";
        return;
    }
    cout<<"\n***********Printing shortest path*********\n\n";
    string finish=destination;
    vector<string> shortest_path;
    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<"-->";
    }
    cout<<shortest_path[i]<<endl<<endl;
    cout<<"Number of stations you need to change is: "<<shortest_path.size()<<endl;
    for(auto d:dist){
        string element=d.first;
        int distance=d.second;
        if(element==destination){
            cout<<"Shortest distance from "<<src<<" to "<<element<<" is: "<<distance<<endl;
            break;
        }
    }
}

void navigate_helper(string src,map<string,bool>& visited,string dest){
    visited[src]=true;
    for(auto i:mpfinal[src]){
        string node=i.first;
        if(visited[node]==false){ // to avoid cycle in DFS tree
            navigate_helper(node,visited,dest);
        }
    }
    //return false;
}
bool navigate(string src,string dest){
    bool flagSrc=false,flagDest=false;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
        if(node==dest){
            flagDest=true;
        }
    }
    if(flagSrc==false || flagDest==false){
        cout<<"\nYou have entered either wrong Source or Destination, which is not part of our ecosystem.\n";
        return false;
    }
    map<string,bool> visited;
    for(auto i:mpfinal){
        string node=i.first;
        visited[node]=false;
    }
    // iterate over all vertices
    navigate_helper(src,visited,dest);
    if(visited[dest]==false){
        return false;
    }
    map<string,string> parent;
    map<string,int> dist;
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; // pahunchna kahan hai current parent node se
                auto f=st.find({dist[dest],dest}); // checking if current child node is present in set
                if(f!=st.end()){ // this will not get executed for first few times
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    cout<<"\nYou can follow the below described path to reach to your misplaced device\n\n";
    string finish=dest;
    vector<string> shortest_path;
    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<"-->";
    }
    cout<<shortest_path[i]<<endl<<endl;
    return true;
    //dfs_helper(src,visited);
}

void kthSmallest(string src,int k){
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;
    map<string,int> dist;
    map<string,string> parent;
    bool flagSrc=false;
    for(auto i:mpfinal){
        string node=i.first;
        if(node==src){
            flagSrc=true;
        }
    }
    if(flagSrc==false){
        cout<<"\nYou have entered wrong Source which is not part of our ecosystem.\n";
        return;
    }
    for(auto i:mpfinal){
        string node=i.first;
        dist[node]=INT_MAX;
    }
    set<pair<int,string>> st;
    dist[src]=0;
    parent[src]="src";
    st.insert(make_pair(0,src)); // (wt,node) pair is stored in set
    while(!st.empty()){
        auto p=*(st.begin());
        string nodeParent=p.second; // parent node
        int nodeDistance=p.first; // parent distance
        st.erase(p);
        for(auto child:mpfinal[nodeParent]){
            if((nodeDistance+child.second) < dist[child.first]){
                string dest=child.first; // pahunchna kahan hai current parent node se
                auto f=st.find({dist[dest],dest}); // checking if current child node is present in set
                if(f!=st.end()){ // this will not get executed for first few times
                    st.erase({dist[dest],dest});
                }
                dist[dest]=(nodeDistance+child.second);
                parent[dest]=nodeParent;
                st.insert({dist[dest],dest});
            }
        }
    }
    for(auto i:dist){
        string node=i.first;
        int distance=i.second;
        pq.push({distance,node});
    }
    int li=k;
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq1;
    pq1=pq;
    cout<<"Shortest distance from "<<src<<" to "<<"all places is as follows:\n\n";
    while(pq1.size()>0){
        if(pq1.top().first==INT_MAX || pq1.top().second==src){
            pq1.pop();
            continue;
        }
        cout<<pq1.top().second<<" -- "<<pq1.top().first<<endl;
        pq1.pop();
    }
    cout<<endl;
    while(k>0){
        pq.pop();
        k--;
    }
    cout<<"\n************Printing 'K'th minimum shortest path*************\n\n";
    string finish=pq.top().second;
    vector<string> shortest_path;
    while(finish!=parent[src]){
        shortest_path.push_back(finish);
        finish=parent[finish];
    }
    reverse(shortest_path.begin(),shortest_path.end());
    int i;
    cout<<"Among the above mentioned shortest distances, the places that lies at "<<li<<" "<<"minimum shortest distance from "<<src<<" is "<<pq.top().second<<" which is at a distance of: "<<pq.top().first<<endl<<endl;
    for(i=0;i<shortest_path.size()-1;i++){
        cout<<shortest_path[i]<<"-->";
    }
    cout<<shortest_path[i]<<endl<<endl;
}

void printGraph(){
    for(auto i:mpfinal){
        string node=i.first;
        cout<<node<<" -> ";
        for(auto j:mpfinal[node]){
            cout<<"("<<j.first<<","<<j.second<<")"<<" ";
        }
        cout<<endl;
    }
    cout<<"\n**************************************************************\n";
}

int main()
{
    cout<<"-----------------------------Metro Map Navigator--------------------------------\n\n";
    cout<<"1. Compute the shortest route between your current Metro Station and Destination Metro Station.\n"<<endl;
    cout<<"2. Tell, whether you can reach to your misplaced phone lost at other station or not. If YES then show the path.\n"<<endl;
    cout<<"3. If you want to go to the place with 'K'th minimum shortest path from your current location, then choose this option.\n"<<endl;

    make_graph();
    cout<<"\n**********THE GRAPH FORMED BY THE PROVIDED DATA IS************\n\n";
    printGraph();
    char ch;
    do{
        cout<<"\nEnter the option:\n";
        int choice,k;
        cin>>choice;
        string src,dest;
        switch(choice){
            case 1:{
                cout<<"\nEnter your current location:  ";
                cin>>src;
                cout<<"\nEnter the Destination:  ";
                cin>>dest;
                cout<<endl;
                Dijkstra(src,dest);
                break;
            }

            case 2:{
                cout<<"\nEnter your current location: ";
                cin>>src;
                cout<<"\nEnter the location of your misplaced device: ";
                cin>>dest;
                bool found=navigate(src,dest);
                if(found){
                    cout<<"\nSo, yes, you can reach from "<<src<<" to "<<dest<<" to collect your phone\n"<<endl;
                }
                else{
                    cout<<"\nThere is no way, you can reach from "<<src<<" to "<<dest<<" to collect your phone\n"<<endl;
                }
                break;
            }


            case 3:{
                cout<<"\nEnter your current location: ";
                cin>>src;
                cout<<endl;
                cout<<"Enter the value of 'K': ";
                cin>>k;
                cout<<endl;
                kthSmallest(src,k);
                cout<<endl;
                break;
            }

            default:{
                cout<<"\nYou Entered the wrong option\n";
                break;
            }
        }
        cout<<"\nDo you want to continue(y/n)\n";
        cin>>ch;
    }while(ch=='y');
}
