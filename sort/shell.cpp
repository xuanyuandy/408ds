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

void shell(vector<int>& nums){
    int len = nums.size();
    for(int step = (len >> 1);step >= 1;step >>= 1){
        // 0 ~ step - 1 is the initial data
        // assume that the behind element is sorted
        for(int i = step;i < len;i ++){
            int temp = nums[i],j;
            for(j = i - step;j >= 0 && nums[j] > temp;j -= step){
                nums[j + step] = nums[j];
            }
            nums[j + step] = temp;
        }
    }
}

int main(){
    freopen("data.txt","r",stdin);
    read(nums);
    print(nums);
    // shell sort 
    // we first choose the init step is len / 2
    shell(nums);
    print(nums);
    return 0;
}