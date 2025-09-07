#include "util.hpp"

// basic 1D prefix sum calculation;
void prefix_sum() {
	vector<int> vec {1, 2, 3, 4, 5, 6, 7};
	vector<int> prefix(vec.size() + 1);

    for(int i = 0; i < vec.size(); ++i) prefix[i + 1] = prefix[i] + vec[i]; // next accumulated value depends on current accumulated value + current value

    // or partial_sum(vec.begin(), vec.end(), prefix.begin() + 1);
	
    cout << vec << "\n";
    cout << prefix << "\n";


    // Now, range-sum queries are O(1) instead of O(N).
    // query returns range-sum from [l, r)
    auto query = [&prefix](int l, int r) {return prefix[r] - prefix[l];};

    cout << query(3, 5) << endl; 
    cout << query(2, 6) << endl;
    cout << query(0, 4) << endl;
    cout << query(0, 7) << endl;
    
}

// two pointer to calculate the longest contiguous segment within a budget t
void two_pointer() {
    vector<int> vec {1, 3, 2, 5, 2, 3, 3, 1};
    int t = 9;
    int r = -1, sum = 0, ans = 0;
	// sum stores sum of A[l ... r inclusive]
	for (int l = 0; l < vec.size(); sum -= vec[l++]) // before every l++ subtract vec[l] from our budget
    {
		while (r + 1 < vec.size() && sum + vec[r + 1] <= t) sum += vec[++r]; // after ++r, add vec[r] top our budget
		ans = max(ans, r - l + 1); // running tab of the longest segment so far.
	}
	cout << ans << "\n";
}
int main() {
    prefix_sum();
    return 0;
}