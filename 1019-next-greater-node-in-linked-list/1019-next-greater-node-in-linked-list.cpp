#define ll long long
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        // Step 1: Convert linked list to array
        vector<int> nums;
        while (head) {
            nums.push_back(head->val);
            head = head->next;
        }

        ll n = nums.size();
        vector<int> ans(n, 0);
        stack<int> st; // store indices

        // Step 2: Monotonic stack (traverse backwards)
        for (ll i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                ans[i] = nums[st.top()];
            }
            st.push(i);
        }

        return ans;
    }
};