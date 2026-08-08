// ============================================================================
//  PROBLEM 1 — Equal-Endpoint Subarrays Summing to K
// ============================================================================
//
//  You are given an array `a` of n elements (all strictly positive) and a
//  positive integer k.
//
//  Count the number of subarrays (contiguous) such that:
//      (1) the elements of the subarray sum to exactly k, AND
//      (2) the first and last element of the subarray are the same number.
//
//  ----------------------------------------------------------------------------
//  EXAMPLE
//  ----------------------------------------------------------------------------
//
//  idx:    0     1     2     3     4     5     6
//  a  :  [ 1 ] [ 2 ] [ 1 ] [ 3 ] [ 1 ] [ 2 ] [ 1 ]     k = 4
//
//        |<----- 4 ----->|                              ends: 1 .. 1  -> COUNT
//                    |<-- 4 -->|                        ends: 1 .. 3  -> skip
//                          |<-- 4 -->|                  ends: 3 .. 1  -> skip
//                                |<----- 4 ----->|      ends: 1 .. 1  -> COUNT
//
//  answer = 2
//
//  ----------------------------------------------------------------------------
//  NOTES
//  ----------------------------------------------------------------------------
//    * A subarray of length 1 trivially has first == last, so a single element
//      equal to k counts.
//    * All elements are strictly positive (this matters).
//
// ============================================================================

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int count_equal_endpoint_subarrays(vector<int> arr, int k) {
    int n = arr.size();
    int count = 0;
    long long sum = 0;
    int lo = 0;
    for (int hi = 0; hi < n; hi++) {
        sum += arr[hi];
        while (sum > k && lo <= hi) {
            sum -= arr[lo];
            lo++;
        }
        if (sum == k && arr[lo] == arr[hi]) count++;
    }
    return count;
}

int main() {
    vector<int> a = {1, 2, 1, 3, 1, 2, 1};
    cout << count_equal_endpoint_subarrays(a, 4) << "  (expected 2)\n";

    vector<int> b = {4, 4, 4};
    cout << count_equal_endpoint_subarrays(a, 4) << "  (expected 3)\n";

    vector<int> c = {2, 3, 1, 2, 3, 2};
    cout << count_equal_endpoint_subarrays(a, 6) << "  (expected 0)\n";
    return 0;
}