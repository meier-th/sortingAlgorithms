#include <iostream>
#include <string>

using namespace std;

int array[15] = {3, 7, 1, -15, 71, 2, 2, 6, 5, -8, 0, 4, -5, 6, 1};

void print_array(string type) {
    cout<<"Array after "<<type<<":"<<endl;
    for (int i = 0; i < 15; ++i){
        cout<<array[i]<<", ";
    }
    cout<<endl;
}

void bubble_sort() {
    bool changed_flag;
    do {
        changed_flag = false;
        for (int i = 0; i < 14; ++i) {
            if (array[i] > array[i+1]) {
                int temp = array[i+1];
                array[i+1] = array[i];
                array[i] = temp;
                changed_flag = true;
            }
        }
    } while (changed_flag);
}

void merge(int* array, int start, int middle, int end) {
    if (start == end) {
        return;
    }
    int result[end-start+1];
    int iterator = 0;
    int* pointer_1 = array + start;
    int* pointer_2 = array + middle;
    bool on_first;
    while (pointer_1 != array+middle && pointer_2 <= array+end) {
        if (*pointer_1 > *pointer_2) {
            result[iterator] = *pointer_2;
            iterator++;
            pointer_2++;
            on_first = false;
        } else {
            result[iterator] = *pointer_1;
            iterator++;
            pointer_1++;
            on_first = true;
        }
    }
    if (on_first) {
        while (pointer_2 <= array + end) {
            result[iterator] = *pointer_2;
            iterator++;
            pointer_2++;
        }
    } else {
        while (pointer_1 != array + middle) {
            result[iterator] = *pointer_1;
            iterator++;
            pointer_1++;
        }
    }
    for (int i = start, j = 0; i <= end; ++i, ++j) {
        array[i] = result[j];
    }
}

void merge_sort(int start, int end) {
    if (end - start > 1) {
        int middle = start + (end - start)/2;
        merge_sort(start, middle);
        merge_sort(middle + 1, end);
        merge(array, start, middle + 1, end);
    } else 
        merge(array, start, end, end);
}

void insertion_sort() {
    for (int i = 1; i < 15; ++i) {
        int pointer = i;
        while (pointer != 0 && array[pointer] < array[pointer - 1]) {
            int temp = array[pointer];
            array[pointer] = array[pointer - 1];
            array[pointer - 1] = temp;
            pointer--;
        }
    }
}

int partition(int start, int end) {
    int pivot = array [end];
    int lesser_pointer = start-1;
    for (int i = start; i < end; ++i) {
        if (array[i] < pivot) {
            lesser_pointer++;
            int temp = array[i];
            array[i] = array[lesser_pointer];
            array[lesser_pointer] = temp;
        }
    }
    array[end] = array[lesser_pointer+1];
    array[lesser_pointer+1] = pivot;
    if (end - start < 2)
        return -1;
    return lesser_pointer+1;
}

void quicksort(int start, int end) {
    if (end > start) {
        int pivot_pos = partition(start, end);
        if (pivot_pos != -1) {
            quicksort(start, pivot_pos-1);
            quicksort(pivot_pos+1, end);
        }
    }
}

void restore_array() {
    array[0] = 3;
    array[1] = 7;
    array[2] = 1;
    array[3] = -15;
    array[4] = 71;
    array[5] = 2;
    array[6] = 2;
    array[7] = 6;
    array[8] = 5;
    array[9] = -8;
    array[10] = 0;
    array[11] = 4;
    array[12] = -5;
    array[13] = 6;
    array[14] = 1;
}

void heapify(int size, int root) {
    int left_child = root*2+1;
    int right_child = root*2+2;
    int largest = root;
    if (left_child < size && array[left_child] > array[largest]) {
        largest = left_child;
    }
    if (right_child < size && array[right_child] > array[largest]) {
        largest = right_child;
    }
    if (largest != root) {
        int temp = array[root];
        array[root] = array[largest];
        array[largest] = temp;
        heapify(size, largest);
    }
}

void heap_sort(int size) {
    for (int i = size/2-1; i >= 0; i--) {
        heapify(size, i);
    }
    for (int i = size-1; i >= 0; --i) {
        int temp = array[i];
        array[i] = array[0];
        array[0] = temp;
        heapify(i, 0);
    }
}

void counting_sort(int range_start, int range_end, int size) {
    int range[range_end - range_start + 1] = { 0 };
    for (int i = 0; i < size; ++i) {
        range[array[i]-range_start]++;
    }
    for (int i = 1; i < range_end - range_start + 1; ++i) {
        range[i]+=range[i-1];
    }
    int output_times = 0;
    int current = 0;
    int write_iterator = 0;
    while (output_times != size) {
        if (range[current] - output_times > 0) {
            int num = range[current] - output_times;
            for (int i = 0; i < num; ++i) {
                array[write_iterator] = current + range_start;
                write_iterator++;
                output_times++;
            }
        }
        current++;
    }
}

int main() {
    bubble_sort();
    print_array("bubble sort");
    restore_array();
    merge_sort(0, 14);
    print_array("merge sort");
    restore_array();
    insertion_sort();
    print_array("insertion sort");
    restore_array();
    quicksort(0, 14);
    print_array("quicksort");
    restore_array();
    heap_sort(15);
    print_array("heap sort");
    restore_array();
    counting_sort(-15, 71, 15);
    print_array("counting sort");
    return 0;
}