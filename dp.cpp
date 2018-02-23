//dynamic programming
//ECS 122A Winter 2018, hw5
//Yuan

// #include "../yuanHeadAll.h"
// #include "../yuanFun.h"
// #include "../CPUTimer.h"
#include <iostream>     // std::cout
#include <vector> 
using namespace std;

string addParenthesis(string str, int l, int r, vector<vector<int>> & loc){
	// if(l == r) return str.substr(l,1);
	// if(l+1 == r) return "(" + str.substr(l,2) + ")";
	// string lstr = addParenthesis(str, l, loc[l][r], loc);
	// string rstr = addParenthesis(str, loc[l+1][r], r, loc);
	// if(loc[l][r] - l + 1 > 3)  lstr = "(" + lstr + ")";
	// if(r - loc[l+1][r] + 1 > 3)  rstr = "(" + rstr + ")";
	// return lstr + rstr ;
	string ans = "";
	if(l == r) ans = str.substr(l,1);
	else if(l+1 == r) ans = "(" + str.substr(l,2) + ")";
	else 
	{
		string lstr = addParenthesis(str, l, loc[l][r], loc);
		string rstr = addParenthesis(str, loc[l][r]+1, r, loc);
		if(loc[l][r] - l + 1 >= 3)  lstr = "(" + lstr + ")";
		if(r - loc[l][r]  >= 3)  rstr = "(" + rstr + ")";
		// return "(" + lstr + ")" + "(" + rstr + ")" ;
		ans = lstr + rstr;
	}
	// cout << "l:" << l << "\tr:" << r << "\tstring: " << ans << endl;
	return ans ;
}
int matrix_chain_mult(vector<int> & info){
	int length = info.size() - 1;
	vector<vector<int>> counts(length, vector<int>(length, 10000));
	for(int i = 0; i < length; ++i ) counts[i][i] = 0;
	vector<vector<int>> loc(info.size()-1, vector<int>(info.size()-1, -1));
	
	// cout << length << endl;
	for(int d  = 2; d <= length; ++d)
	{
		// cout << "here" << endl;
		// for(int i = 0; i < counts.size(); ++i)
		for(int i = 0; i + d <= counts.size(); ++i)
		{
			int j = i + d -1; //right bound
			for(int k = i ; k < j ; ++k){
				if(counts[i][k] + counts[k+1][j] + info[i]*info[k+1]*info[j+1] < counts[i][j]){
					counts[i][j] = counts[i][k] + counts[k+1][j] + info[i]*info[k+1]*info[j+1];
					loc[i][j] = k;
				}
			}
		}
	}
	// cout << counts << endl;
	for(int i = 0; i < counts.size(); ++i)
	{
		for(int j = 0; j < counts[i].size(); ++j)
			cout << counts[i][j] << "\t";
		cout << "\n";
	}
	// cout << loc << endl;
	for(int i = 0; i < loc.size(); ++i)
	{
		for(int j = 0; j < loc[i].size(); ++j)
			cout << loc[i][j] << "\t";
		cout << "\n";
	}

	string str = "";
	for(int i = 0; i < info.size()-1; ++i)
		str.append(1,'$');

	// cout << str << endl;
	cout << addParenthesis(str, 0, str.size()-1, loc) << endl;

	return counts[0][counts.size()-1];
}

void MCS(string a, string b){
	int loc = -1;
	int maxlen = 0;
	vector<vector<int>> dp(a.size(), vector<int>(b.size(),0));
	for(int i = 0; i < a.size(); ++i)
		for(int j = 0; j < b.size(); ++j){
			if(i == 0 || j == 0)
			{
				if(a[i] == b[j])
					dp[i][j] = 1;
			}
			else{
				if(a[i] == b[j])
					dp[i][j] = dp[i-1][j-1] + 1;
				if(dp[i][j] > maxlen ){
					maxlen = dp[i][j];
					loc = i;
				}
			}				
		}
	if(maxlen > 0)
		cout << "MCS : " << a.substr(loc - maxlen+1, maxlen) << endl;
	else cout << "no MCS";

	for(int i = 0; i < dp.size(); ++i)
	{
		for(int j = 0; j < dp[i].size(); ++j)
			cout << dp[i][j] << "\t";
		cout << "\n";
	}
}
int main(){
	MCS("algorithm", "logarithm");
	// return 0;

	vector<int> info{5,6,3,7,5,3,4};
	cout << matrix_chain_mult(info) << endl;

	return 0;
}

