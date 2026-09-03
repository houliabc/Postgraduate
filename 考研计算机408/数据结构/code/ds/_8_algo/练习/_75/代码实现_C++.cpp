public:
    // 三路快排 (一趟扫描)
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    void sortColors(vector<int>& nums) {
        int zero = 0;
        int two = nums.size() - 1;
        int i = 0;
        while (i <= two) {
            if (nums[i] == 0) {
                swap(nums[i], nums[zero]);
                i++;
                zero++;
            } else if (nums[i] == 2) {
                swap(nums[i], nums[two]);
                two--;
            } else {
                i++;
            }
        }
    }

    // 计数排序 (两趟扫描)
    // 时间复杂度：O(n)
    // 空间复杂度：O(1)
    void sortColors1(vector<int>& nums) {
        // 1. 计数
        int* count = new int[3];
        for (int num : nums) {
            count[num]++;
        }

        // 2. 排序
        int k = 0;
        for (int i = 0; i <= 2; i++) {
            int num = count[i];
            for (int j = 1; j <= num; j++) {
                nums[k++] = i;
            }
        }
    }