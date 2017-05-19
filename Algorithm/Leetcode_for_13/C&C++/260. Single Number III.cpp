
// 还是使用亦或操作。
// 然后分别找出两个单独的数字
class Solution {  
public:  
    vector<int> singleNumber(vector<int>& nums) {  
    vector<int> res;  
    int sum=nums.size();  
    if(sum==0)  
        return res;  
    if(sum<=2)  
        return nums;  
    int temp=nums[0];  
    for(int i=1;i<sum;++i)  
        temp^=nums[i];  
    int count=0;  //    记录第几位是1
    while(1)  
    {  
        if(temp&1==1)  
            break;  
        else  
        {  
            temp>>=1;  
            ++count;  
        }  
    }  
    int res1=0;  
    int res2=0;  
    for(int i=0;i<sum;++i)  // 分别找出两个数字
    {  
        if((nums[i]>>count)&1==1)  
            res1^=nums[i];  
        else  
            res2^=nums[i];  
    }  
    res.push_back(res1);  
    res.push_back(res2);  
    return res;  
    }  
};  
