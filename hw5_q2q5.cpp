//dynamic programming
//ECS 122A Winter 2018, hw5
//Yuan
 
#include <iostream>     // std::cout
#include <vector> 
using namespace std;

//Question 2
string addParenthesis(string str, int l, int r, vector<vector<int>> & loc){

	string ans = "";
	if(l == r) ans = str.substr(l,1);
	else if(l+1 == r) ans = "(" + str.substr(l,2) + ")";
	else 
	{
		string lstr = addParenthesis(str, l, loc[l][r], loc); //recursion for left part substring
		string rstr = addParenthesis(str, loc[l][r]+1, r, loc);
		if(loc[l][r] - l + 1 >= 3)  lstr = "(" + lstr + ")"; //no need to add parenthesis for single or two matrices
		if(r - loc[l][r]  >= 3)  rstr = "(" + rstr + ")";
		ans = lstr + rstr;
	}
	return ans ;
}
void matrix_chain_mult(vector<int> & info){ // a little different from code in lecture, cuz the subscript is from 0, so corresponding p[i] is one less than the equation on lecture
	int length = info.size() - 1;
	vector<vector<int>> counts(length, vector<int>(length, 10000)); 
	vector<vector<int>> loc(info.size()-1, vector<int>(info.size()-1, -1));
	for(int i = 0; i < length; ++i ) counts[i][i] = 0; // initial

	for(int d  = 2; d <= length; ++d)
	{
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
	//print table of value and location
	for(int i = 0; i < counts.size(); ++i)
	{
		for(int j = 0; j < counts[i].size(); ++j)
			cout << counts[i][j] << "\t";
		cout << "\n";
	}
	for(int i = 0; i < loc.size(); ++i)
	{
		for(int j = 0; j < loc[i].size(); ++j)
			cout << loc[i][j] << "\t";
		cout << "\n";
	}

	//print substring, I use $ to represent the specific matrix name
	string str = "";
	for(int i = 0; i < info.size()-1; ++i)
		str.append(1,'$');

	// cout << str << endl;
	cout << addParenthesis(str, 0, str.size()-1, loc) << endl;

	cout << "minimal number of scalar multiplication is : " << counts[0][counts.size()-1] << endl;
}

//Question 5
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
	cout << '\n';
}


int main(){

	//test for question 5
	MCS("algorithm", "logarithm");

	//test for question 2
	vector<int> info{5,6,3,7,5,3,4};
	matrix_chain_mult(info);

	return 0;
}

