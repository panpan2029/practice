//sort

#include "../yuanHeadAll.h"
#include "../yuanFun.h"
#include "../CPUTimer.h"

using namespace std;

//Insertion Sort
template<typename itr, typename Comp>
void insertionSort(const itr & begin, const itr & end, Comp lessThan = less<Comp>())
{
	if(begin == end) return;
	itr j;
	for (itr p = begin+1; p!=end; ++p)
	{
		auto tmp = std::move(*p);
		for(j=p; j != begin && lessThan(tmp,*(j-1)); --j)
			*j = std::move(*(j-1));
		*j = std::move(tmp);
	}
}

//selection problem, Kth, lc 215. Kth Largest Element in an Array
//https://leetcode.com/problems/kth-largest-element-in-an-array/discuss/60309/4-C++-Solutions-using-Partition-Max-Heap-priority_queue-and-multiset-respectively
//Partition, Max-Heap, priority_queue and multiset respectively
//sort and find 
//pick k elements and sort, and check remaining n-k, 
//use maxheap, combine first picking k elemnets and then insert remaining
//quick selection, O(N)
int findKthLargest(vector<int>& nums, int k) {
    /* version 1.0 really.....*/
    sort(nums.begin(), nums.end(), greater<int>()); 
    int i =0; 
    while( i < k && i < nums.size()){
        ++i;
    }
    return nums[i-1];//care!
}
int findKthLargest_priority(vector<int>& nums, int k) {
    /* version 1.0 really.....*/
    priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.begin()+k);
    for(int i = k; i < nums.size(); ++i){
    	if(nums[i] <= pq.top()) continue;
    	else {
    		pq.push(nums[i]);
    		pq.pop();
    	}
    }
    return pq.top();
}
//Search in Rotated Sorted Array lc 33
int main(){
	vector<int> v{3,2,1,5,6,4};
	cout << findKthLargest(v, 2) <<endl;
	return 0;

	vector<int> unsortedV;
	srand(time(0));
	for(int  i = 0; i < 10; ++i)
		unsortedV.push_back(i);
	random_shuffle(unsortedV.begin(), unsortedV.end());
	cout << unsortedV <<endl;

	insertionSort(unsortedV.begin(), unsortedV.end(), greater<int>{});
	cout << unsortedV << endl;
	return 0;
}