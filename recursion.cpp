#include <iostream>
#include <vector>
using namespace std;

class MaximumSeqSum
{
	/* DS, page 61 */
	/* math */
	/* best: linear time, one pass through the data*/
	/* D&C, NlgN*/
	/* brute and force, N^2*/
public:
	int getSum(const vector<int> & in)
	{
		int max = 0;
		int thisMax = 0; 
		for (int i = 0; i < in.size(); ++i)
		{
			thisMax += in[i];
			if(thisMax < 0) thisMax = 0;
			if(thisMax > max) max = thisMax;
		}
		return max;
	}
};



int main()
{
	vector<int> arr{4, -3, 5, -2, -1, 2, 6, -2};
	MaximumSeqSum m;
	cout << m.getSum(arr) << endl;
	return 0;
}