#include <iostream>
#include <vector>
#include <sstream>
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

void merge(int l,int r,vector<int>& nums){
    if(l == r) return;
    int mid = (l + r) >> 1;
    merge(l,mid,nums),merge(mid + 1,r,nums);
    vector<int> temp;
    // assume that two part of l ~ mid and mid + 1 ~ r have been sorted, so we combine them
    int i,j;
    for(i = l,j = mid + 1;i <= mid && j <= r;){
        if(nums[i] >= nums[j]){
            temp.push_back(nums[j]);
            j ++;
        }else{
            temp.push_back(nums[i]);
            i ++;
        }
    }
    while(i <= mid) temp.push_back(nums[i ++]);
    while(j <= r) temp.push_back(nums[j ++]);

    // copy
    for(int k = l;k <= r;k ++){
        nums[k] = temp[k - l];
    }
    
}


int main(){
    freopen("data.txt","r",stdin);
    read(nums);
    print(nums);
    
    int len = nums.size();
    merge(0,len - 1,nums);
    print(nums);
    return 0;
}