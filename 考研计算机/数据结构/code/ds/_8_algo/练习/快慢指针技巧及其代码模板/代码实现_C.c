void partition(int nums[], int n) {
    int pivot = nums[n - 1];

    int slow = 0, fast = 0;
    while (fast < n - 1) {
        if (nums[fast] < pivot) {
            swap(&nums[slow], &nums[fast]);
            slow++;
        }
        fast++;
    }
    swap(&nums[slow], &nums[fast]);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}