## title: Kadane's Algorithm
  - for maximum or minumum subarray sum.

we can use it to calculate the largest sub array contain the same element a;
 - create a array b where if arr[i] == a then b[i] = 1, otherwise b[i] = 0;

* intuition code :
`
 int maxSubArraySum(int arr[],int n)
   {
     int max_sub_array_sum = INT_MIN;
     int curr =0;

     for(int i = 0 ; i < n; ++i)
       {
         curr+= arr[i];

         if(curr>max_sub_array_sum)
                 max_sub_array_sum = curr;

         if(curr<0)
                 curr = 0;

       }
     return max_sub_array_sum;
   }
`
* dp:
For each index i, DP[i] stores the maximum possible Largest Sum Contiguous Subarray ending at index i.
DP[i] = max(DP[i-1] + arr[i] , arr[i] )

`
int maxSubArraySum(int arr[],int n)
  {
    std::vector<int> dp(n,0);

    dp[0] = arr[0];
    int ans = dp[0];
    for(int i = 1 ; i< n ;++i)
      {
        dp[i] = std::max(arr[i],arr[i]+dp[i-1]);
        ans = std::max(ans, dp[i]);
      }
    return ans;
    }
`
* application:


