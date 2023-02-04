
#include <iostream>
#include <vector>

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

void maopaoSort(std::vector<int> &nums) {
    for (int i = nums.size() - 1; i >= 1; --i) {
        for (int j = 0; j <= i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;  
            }
        }
    }
}

class A {
    public:
        A(int a) {
            this->a = a;  
            std::cout << "construct, a : " << a << std::endl;  
        }
        virtual ~A() {}    // 有析构   移动不会自动生存，拷贝可以
        // A(const A& a) = delete;
        // 析构不会影响拷贝
        A(const A& a) {
            std::cout << "copy construct" << std::endl;  
        }
        A(A&& a) {
            std::cout << "move construct" << std::endl;  
        }

        void test(const int& a) {
            std::cout << "test(int a)" << std::endl;  
        }

        void test(const float& a) {
            std::cout << "test(float a)" << std::endl;  
        }

        int a = 0; 
};


int main() {
std::vector<int> nums{7,3,4,7,2,8,0,6,4,6,4,7,3,2,8,9,5,7,3,5,6,8,5,1};
maopaoSort(nums);
std::cout << "after sort: ";
for (int i : nums) {
    std::cout << i << ", ";
}
std::cout << std::endl;

std::vector<A> A_C; 
A_C.push_back(A(8));

int k = 1;
float k_f = 1.001;
if (k_f > k) {
    std::cout << "k_f > k" << std::endl;
}

A T(9);
T.test(1);

return 1;
}