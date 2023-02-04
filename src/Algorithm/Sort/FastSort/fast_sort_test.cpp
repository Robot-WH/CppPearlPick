
#include "fast_sort.hpp"
#include <iostream>
#include <deque>

int findMid(int a, int b, int c) {
    std::vector<int> nums{a, b, c};
    if (nums[0] > nums[1]) {
        int temp = nums[0];
        nums[0] = nums[1];
        nums[1] = temp; 
    }
    if (nums[1] > nums[2]) {
        int temp = nums[1];
        nums[1] = nums[2];
        nums[2] = temp; 
    }
    if (nums[0] > nums[1] ) {
        int temp = nums[0];
        nums[0] = nums[1];
        nums[1] = temp; 
    }
    return nums[1];  
}

int main() {
std::vector<int> nums{7,2,5,7,2,4,8,9,0,7,5,8,4,7,3,2,7,8,5,4,3,6,7,8,4,3,7,0,8,2};
FastSort fast_sort;
fast_sort.Sort_head_tail_points(nums);
std::cout << "after sort: ";
for (int i : nums) {
    std::cout << i << ", ";
}
std::cout << std::endl;
std::cout << "findMid: " << findMid(4,7,2) <<std::endl;

return 1;
}