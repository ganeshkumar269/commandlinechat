#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
template <class dataType>
void vectorprint(vector<dataType> arr,const char c = 'h',const char* stream = "cerr"){
    if(c == 'v' && !strcmp(stream,"cout"))
        for(unsigned long i = 0 ; i < arr.size() ; ++i)
            cout<<arr[i]<<endl;
    else if (c == 'v')
        for(unsigned long i = 0 ; i < arr.size() ; ++i)
            cerr<<arr[i]<<endl;
    else if (!strcmp(stream,"cout")){
        for(unsigned long i = 0 ; i < arr.size() ; ++i)
            cout<<arr[i]<<" ";
        cout<<endl;
    }
    else {
        for(unsigned long i = 0 ; i < arr.size() ; ++i)
            cerr<<arr[i]<<" ";
        cerr<<endl;
    }
}