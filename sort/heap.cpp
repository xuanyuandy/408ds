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

void quick(int l,int r,vector<int>& nums){
    if(l >= r) return;
    int i = l - 1,j = r + 1;
    int midv = nums[(l + r) >> 1];
    while(i < j){
        do i ++; while(nums[i] < midv);
        do j --; while(nums[j] > midv);
        if(i < j) swap(nums[i],nums[j]);
    }
    quick(l,j,nums),quick(j + 1,r,nums);
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