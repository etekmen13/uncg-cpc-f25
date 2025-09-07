#include "util.hpp"
#include <vector>
#include <algorithm>
using namespace std;

#pragma region PrefixSum
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
#pragma endregion

#pragma region MonotonicDeque
std::vector<int> sliding_window_monotonic_deque() {
    vector<int> a {1,3,-1,-3,5,3,6,7};
    int k = 3;
    if (k <= 0 || k > (int)a.size()) return {};
    std::deque<int> dq; // store indices, values decreasing
    std::vector<int> ans;
    ans.reserve(a.size() - k + 1);

    for (int i = 0; i < (int)a.size(); ++i) {
        // push a[i]: pop smaller from back
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);

        // pop expired from front (i - k + 1 is the left index)
        if (dq.front() <= i - k) dq.pop_front();

        // record answer once we have a full window
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}
#pragma endregion

#pragma region MaxQueue
/*
  Sliding Window Maximum in O(n) using a MaxQueue:
  - A MaxQueue = two MaxStacks: 'in' (push-right) and 'out' (pop-left).
  - Each MaxStack stores the running maximum alongside values.
  - The window's max is max(in.max(), out.max()).
  - When 'out' is empty and we need to pop-left, we transfer all from 'in' to 'out'
    (recomputing running max for 'out'). Amortized O(1) per operation.

  - Read more: https://cp-algorithms.com/data_structures/stack_queue_modification.html
*/

struct MaxStack {
    vector<int> vals;   // actual values
    vector<int> mx;     // running max up to this index

    void push(int x) {
        vals.push_back(x);
        mx.push_back(mx.empty() ? x : std::max(x, mx.back()));
    }

    int pop() {
        int x = vals.back();
        vals.pop_back();
        mx.pop_back();
        return x;
    }

    bool empty() const { return vals.empty(); }

    int get_max() const { return mx.back(); }
};

struct MaxQueue {
    MaxStack in, out;

    void push(int x) { in.push(x); }

    // Move everything from 'in' to 'out', reversing order and rebuilding running max for 'out'.
    void transfer() {
        while (!in.empty()) {
            int x = in.pop();
            out.push(x);
        }
    }

    // Pop from the left side of the queue.
    void pop() {
        if (out.empty()) transfer();
        out.pop();
    }

    int get_max() const {
        if (in.empty())  return out.get_max();
        if (out.empty()) return in.get_max();
        return std::max(in.get_max(), out.get_max());
    }
};

// MaxQueue aka Sliding Window Aggregation (SWAG) aka folding over a monoid (associative op, identity element);
vector<int> sliding_window_max_queue() {
    vector<int> nums {1,3,-1,-3,5,3,6,7};
    int k = 3;
    if (k <= 0 || k > (int)nums.size()) return {};  // edge cases

    MaxQueue q;
    vector<int> ans;
    ans.reserve(nums.size() - k + 1);

    for (int i = 0; i < (int)nums.size(); ++i) {
        q.push(nums[i]);

        // First full window ends at i == k-1. After that, record max then pop the leftmost.
        if (i >= k - 1) {
            ans.push_back(q.get_max());
            q.pop();
        }
    }
    return ans;
}
#pragma endregion 

#pragma region TwoPointer
// two pointer to calculate the longest contiguous segment within a budget t
void two_pointer_under_budget() {
    vector<int> vec {1, 3, 2, 5, 2, 3, 3, 1};
    int t = 9;
    int r = -1, sum = 0, ans = 0;
	// sum stores sum of A[l ... r inclusive]
	for (int l = 0; l < vec.size(); sum -= vec[l++]) // before every l++ subtract vec[l] from our budget
    {
		while (r + 1 < vec.size() && sum + vec[r + 1] <= t) sum += vec[++r]; // after ++r, add vec[r] top our budget
		ans = max(ans, r - l + 1); // running tab of the longest segment so far.
	}
    cout << vec << endl;

	cout << "longest subarray within budget " << t << " is of length: " << ans << "\n";
}
// two pointer to calculate the longest contiguous segment with at most K distinct elements
void two_pointer_at_most_k_distinct() {
    vector<int> a {3,2,1,1,1,2,1,1,3,2,1,1,1};
    int K = 2;
    if (K <= 0) return;
    std::unordered_map<int,int> freq;
    int distinct = 0, best = 0, L = 0;

    for (int R = 0; R < (int)a.size(); ++R) {
        distinct += (++freq[a[R]] == 1);

        while (distinct > K) {
            distinct -= (--freq[a[L]] == 0);
            if (freq[a[L]] == 0) freq.erase(a[L]);
            ++L;
        }
        best = std::max(best, R - L + 1);
    }
    cout << a << endl;
    cout << "longest subarray with at most " << K << " distinct numbers is of length: " << best << endl;
}
#pragma endregion


int main() {
    ios::sync_with_stdio(false); // removes runtime checks to ensure consistency with legacy C `printf` and `scanf` functions. You then must only use cin and cout.
    cin.tie(nullptr); // unties cin and cout. Instead of printing answers as inputs come in, the program now reads in all inputs, then prints all outputs.
    
    //prefix_sum();

    // sliding_window_max_queue();

    //sliding_window_monotonic_deque();

    //two_pointer_under_budget();

    two_pointer_at_most_k_distinct();
    return 0;
}