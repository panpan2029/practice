//greedy

#include "../yuanHeadAll.h"
#include "../yuanFun.h"
#include "../CPUTimer.h"

/* greedy, greedy choice property; optimum sub-solution.
 * 
 */

/* find Minimum number of Coins to sum up to the given value 
 * not always work!
 */
vector<pair<int, int>> findMin(vector<int> denomination, int value){
	vector<pair<int, int>> cnt_den;
	sort(denomination.begin(), denomination.end(), greater<int>());
	for(int i = 0; i < denomination.size(); ++i)
	{
		int cnt = 0; 
		while(value > denomination[i]){
			++cnt;
			value -= denomination[i];
		}
			
		if(cnt != 0)
			cnt_den.push_back(make_pair(cnt, denomination[i]));
	}
	return cnt_den;
}

// class  HuffmanCode; 
// bool cmp(const Node * l, const Node * r){ //call to non-static member function without an object argument
// 		return l->freq >= r->freq;
// 	}

class HuffmanCode
{
public:
	HuffmanCode(const vector<char> & chars, const vector<float> & freq){
		if(chars.size() != freq.size()) abort();
		for (int i = 0; i < chars.size(); ++i)
			minHeap.push(new Node{chars[i], NULL, NULL, freq[i]});
		while(minHeap.size()!=1){
			Node * left = minHeap.top();
			minHeap.pop();
			Node * right = minHeap.top();
			minHeap.pop();
			Node * newNode = new Node{'$', left, right, left->freq + right->freq};
			minHeap.push(newNode);
		}
	}
	~HuffmanCode(){
		if(minHeap.size() > 0)
			remove(minHeap.top());
	}
	void printCode() const{
		printCode(minHeap.top(), "");
	}
	struct Node
	{
		char character;
		float freq;
		Node * left;
		Node * right;
		Node(char c = '$', Node * l = NULL, Node * r = NULL , float f = 0.0 ): character{c}, left{l}, right{r}, freq{f} { }
	};
	
private:
	
	struct cmp
	{
		bool operator()(const Node* a, const Node* b) const {return a->freq >= b->freq ;}
	}mycmp;

	void remove(Node* n){
		if( n == NULL ) return;
		if(n->left != NULL) remove(n->left);
		if(n->right != NULL) remove(n->right);
		delete n;
	}
	void printCode(Node* root, string str) const{
		if(root == NULL) return;
		if(root->character != '$')
			cout << root->character << ':' << str << endl;
		printCode(root->left, str+'0');
		printCode(root->right, str+'1');
	}

	priority_queue<Node*, vector<Node*>, cmp> minHeap;
	// priority_queue<Node*, vector<Node*>, [](Node* a, Node* b){return a->freq >= b->freq;}> minHeap;
};
int main(){
	// vector<int> denomination{1, 2, 5, 10, 20, 50, 100, 500, 1000};
	// vector<pair<int, int>> cnt_den = findMin(denomination, 93);
	// for(auto & p : cnt_den)
	// 	cout << p.first << '\t' << p.second << endl;
	/* test Huffman code */
	vector<char> characters{'a', 'b', 'c', 'd', 'e', 'f'};
	vector<float> freq{ 5, 9, 12, 13, 16, 45 };
	HuffmanCode hc(characters, freq);
	hc.printCode();
	return 0;
}

