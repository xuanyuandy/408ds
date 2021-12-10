#include <iostream>
#include <vector>
#include <sstream>
#include <assert.h>
using namespace std;

vector<int> nums;

int read(vector<int>& nums){
    int len = 0,x;
    string line;
    getline(cin,line);
    stringstream ss(line);
    while(ss >> x){
        len ++;
        nums.push_back(x);
    }
    return len;
}

void print(vector<int>& nums){
    for(int i = 0;i < nums.size();i ++){
        cout << nums[i] << " ";
    }
    cout << '\n';
}

int Partition(int l,int r,vector<int>& nums){
    int pivot = nums[l]; // choose the first element as pivot
    while(l < r){
        while(l < r && nums[r] >= pivot) r --;
        nums[l] = nums[r];
        while(l < r && nums[l] <= pivot) l ++;
        nums[r] = nums[l];
    }
    assert(l == r);
    nums[l] = pivot;
    return l;
}

void quick(int l,int r,vector<int>& nums){
    if(l < r){
        int PivotPosition = Partition(l,r,nums);
        quick(l,PivotPosition - 1,nums);
        quick(PivotPosition + 1,r,nums);
    }
}

int main(){
    freopen("data.txt","r",stdin);
    read(nums);
    print(nums);
    
    int len = nums.size();
    quick(0,len - 1,nums);
    print(nums);
    return 0;
}