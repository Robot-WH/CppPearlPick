
#pragma once 
#include <iostream>
#include <vector>

class FastSort {
public:
    // 首尾指针法
    void Sort_head_tail_points(std::vector<int> &nums) {
        int len = nums.size();
        sort(nums, 0, len - 1);
    }

    // 快慢指针法
    void Sort_fast_slow_points(std::vector<int> &nums) {
    }

    void sort(std::vector<int> &nums, int left, int right) {
        if (left >= right) 
            return;  
        setPivot(nums, left, right);
        int pivot = left;
        int head = left + 1;
        int tail = right; 

        while(true) {
            // 从左到右找到pivot大的元素   
            while (head <= tail && nums[head] <= nums[pivot]) {
                head++;
            }
            while (head < tail && nums[tail] >= nums[pivot]) {
                tail--;  
            }
            if (head >= tail) 
                break;
            swap(nums, head, tail); 
        }
        swap(nums, pivot, head - 1);    // head 指向比 pivot大的第一个元素
        sort(nums, left, head - 2);
        sort(nums, head, right);
    }

    // 取头尾中间三个元素，将中间大小的元素放置到头
    void setPivot(std::vector<int> &nums, int left, int right) {
        int mid = (left + right) / 2;
        if (nums[left] > nums[mid]) swap(nums, left, mid);
        if (nums[right] > nums[mid]) swap(nums, mid, right);   // 此时 mid为最大的元素
        if (nums[right] > nums[left]) swap(nums, left, right);   
    }

    void swap(std::vector<int> &nums, int left, int right) {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;  
    }
}; 
