/* You are managing a tennis court and you have n groups of people who want to play. The i’th group wants
to book the court from a starting time si to an ending time ei. The groups are very polite, so they will
vacate the court immediately at the end of their booking and therefore you are able to slot in groups
immediately after each other (i.e. with the ending time of the previous group equal to the starting time
of the next one).
  
Your boss requires that you slot in at least k groups of people. However, it might not be possible to
achieve this, due to overlaps between bookings! Your only option is to shorten some of the bookings, that
is, keep their starting t`ime the same but change their ending time to be earlier. It’s bad to reduce any
single group’s time by too much, so what’s the most you need to reduce from any group in order to slot
in k groups without overlaps?

n = 5, k = 3
(0, 20)
(1, 10)
(7, 14)
(9, 17)
(20, 30)


(1, 10)
(9, 17)
(20, 30)
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


// 1 tennis courts
// n books: each booking is from a start time to an end time
// I need to pick k bookins, so that they don't overlap
// 
// given an instance, I have 2 choices:
//     - first option: reduce 3 of them, each by time 10 (optimal)
//     - second option: reduce one of them by time 11      (not optimal)
// precondition: truncatedBookings is sorted by end time
bool is_possible_to_satisfy(int k, vector<pair<int, int>> &bookings) {
    // sort by end time
    sort(bookings.begin(), bookings.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

  
    // early exit
    if (bookings.size() <= 1) {
        return true;
    }
  
    // linear
    int count = 0;
      int curEndTime = bookings[0].first - 1;
    
      for (auto booking : bookings) {
          int start = booking.first;
        int end = booking.second;
      
          if (start >= curEndTime) {
            count++;
              curEndTime = end;
        }
    }

      return count >= k;
}



int min_time_to_reduce(int n, int k, vector<pair<int, int>> &bookings) {
    // sort ascending by start time
    sort(bookings.begin(), bookings.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    
    int lo = 0;
    int hi = 0;
    for (auto booking : bookings) hi = max(booking.second - booking.first, hi);
    int bestSoFar = -1;
    
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        
        vector<pair<int, int>> truncatedBookings;
        for (auto booking : bookings) {
            int oldStart = booking.first;
            int oldFinish = booking.second;
            
            int newFinish = max(oldStart, oldFinish - mid);

            truncatedBookings.push_back({ oldStart, newFinish });
        }
        
        bool cond = is_possible_to_satisfy(k, truncatedBookings);
        
        if (cond) {
            hi = mid - 1;
            bestSoFar = mid;
        } else {
            lo = mid + 1;
        }
    }

    return bestSoFar;
}

int main() {
    // 
}
