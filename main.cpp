//
//  main.cpp
//  Sorting Algorithms
//
//  Created by Ira Xavier Porchia on 6/25/20.
//  Copyright © 2020 Ira Xavier Porchia. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 10;

class node{
    friend class LL;
    friend class Array;
private:
    int _data;
    node *_next;
public:
    node(int data):
    _data(data), _next(nullptr){}
};

class LL{
private:
    node *_head;
public:
    LL():
    _head(nullptr){}
    
    ~LL(){
        node *temp;
        while(_head != nullptr){
            temp = _head;
            _head = _head->_next;
            temp->_next = nullptr;
            delete temp;
        }
    }
    
    void insert(int data){
        node *temp = _head;
        _head = new node(data);
        _head->_next = temp;
    }
    
    
    
    void display(){
        node *temp = _head;
        while(temp != nullptr){
            cout << temp->_data << " ";
            temp = temp->_next;
        }
        cout << endl << endl;
    }
    
    node *head(){
        return _head;
    }
};

class Array{
private:
    int _arr[MAX];
    int _index;
public:
    Array(){
        for(int i = 0; i < MAX; i++){
            _arr[i] = 0;
        }
        _index = 0;
    }
    
    void insert(int data){
        if(_index == MAX - 1){
            cout << "Full array." << endl << endl;
            return;
        }
        _arr[_index] = data;
        _index++;
    }
    
    void print(){
        if(_index == 0){
            return;
        }
        for(int i = 0; i < _index; i++){
            cout << _arr[i] << " ";
        }
        cout << endl << endl;
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void swap(int &a, int &b){
        int temp = a;
        a = b;
        b = temp;
    }
    //Just keep swapping until max is at the end
    void bubbleSort(){
        int n = _index;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n - i - 1; j++){
                if(_arr[j] > _arr[j + 1]){
                    swap(_arr[j], _arr[j + 1]);
                }
            }
        }
    }
    //Puts the smallest element at the end and goes from there
    void bubbleSort2(){
        int n = _index;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n - i - 1; j++){
                if(_arr[j] < _arr[j + 1]){
                    swap(_arr[j], _arr[j + 1]);
                }
            }
        }
        
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    //Find the min of the array
    void selectionSort(){
        int n = _index;
        for(int i = 0; i < n; i++){
            int min = i;
            for(int j = i + 1; j < n; j++){
                if(_arr[j] < _arr[min]){
                    min = j;
                }
            }
            if(min != i){
                swap(_arr[i], _arr[min]);
            }
        }
    }
    
    void selectionSort2(){
        int n = _index;
        for(int i = 0; i < n; i++){
            int max = i;
            for(int j = i + 1; j < n; j++){
                if(_arr[j] > _arr[max]){
                    max = j;
                }
            }
            if(max != i){
                swap(_arr[i], _arr[max]);
            }
        }
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    //Split into sorted and unsorted array, then repeat until unsorted is empty
    void insertionSort(){
        int n = _index;
        for(int i = 1; i < n; i++){
            int currentNumber = _arr[i];
            int j = i;
            while(_arr[j - 1] > currentNumber && j > 0){
                _arr[j] = _arr[j - 1];
                j--;
            }
            _arr[j] = currentNumber;
        }
    }
    
    void insertionSort2(){
        int n = _index;
        for(int i = 1; i < n; i++){
            int currentNumber = _arr[i];
            int j = i;
            while(_arr[j - 1] < currentNumber && j > 0){
                _arr[j] = _arr[j - 1];
                j--;
            }
            _arr[j] = currentNumber;
        }
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    void Max(int &max){
        max = -10000;
        for(int i = 0; i < _index; i++){
            if(max < _arr[i]){
                max = _arr[i];
            }
        }
    }
    
    // Put the numbers into buckets and then merge them back together
    void bucketSort(){
        
        //Get the max value of the array and also the number of buckets
        int numOfBuckets = ceil(sqrt(_index));
        int maxValue;
        Max(maxValue);
        
        //Create an array of linked lists for the buckets
        LL buckets[numOfBuckets];
        
        //insert the values into each bucket
        for(int i = 0; i < _index; i++){
            int bucketNumber = ceil((_arr[i] * numOfBuckets)/static_cast<double>(maxValue));
            buckets[bucketNumber - 1].insert(_arr[i]);
        }
        
        //put each bucket in order
        for(int i = 0; i < numOfBuckets; i++){
            node *head = buckets[i].head();
            node *p = head;
            node *q = nullptr;
            while(p != nullptr){
                q = p;
                p = p->_next;
                if(p != nullptr){
                    if(p->_data < q->_data){
                        int temp = p->_data;
                        p->_data = q->_data;
                        q->_data = temp;
                    }
                }
            }
        }
        
        //bring all the buckets together
        int a = 0;
        for(int i = 0; i < numOfBuckets; i++){
            node *head = buckets[i].head();
            while(head != nullptr){
                _arr[a] = head->_data;
                head = head->_next;
                a++;
            }
        }
        
    }
    
    void bucketSort2(){
        int numOfBuckets = ceil(sqrt(_index));
        int maxValue;
        Max(maxValue);
        
        LL buckets[numOfBuckets];
        
        for(int i = 0; i < _index; i++){
            int bucketNumber = ceil((_arr[i] * numOfBuckets)/static_cast<double>(maxValue));
            buckets[bucketNumber - 1].insert(_arr[i]);
        }
        
        // Order the buckets from greatest to least.
        for(int i = 0; i < numOfBuckets; i++){
            node *head = buckets[i].head();
            node *p = head;
            node *q = nullptr;
            while(p != nullptr){
                q = p;
                p = p->_next;
                if(p != nullptr){
                    if(p->_data > q->_data){
                        int temp = p->_data;
                        p->_data = q->_data;
                        q->_data = temp;
                    }
                }
            }
        }
        
        //Start from the last bucket instead of the first
        int a = 0;
        for(int i = numOfBuckets - 1; i >= 0; i--){
            node *head = buckets[i].head();
            while(head != nullptr){
                _arr[a] = head->_data;
                head = head->_next;
                a++;
            }
        }
    }
    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    void mergeSort(){
        mergeSortUtil(_arr, 0, _index - 1);
    }
    
    void mergeSortUtil(int arr[], int l, int r){
        if(l < r){
            int m = (l + r)/2;
            mergeSortUtil(arr, l, m);
            mergeSortUtil(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }
    
    void merge(int arr[], int l, int m, int r){
        //Create two new arrays
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1];
        int R[n2];
        
        //Fill in the arrays with values from the original array
        for(int i = 0; i < n1; i++){
            L[i] = arr[l + i];
        }
        for(int i = 0; i < n2; i++){
            R[i] = arr[m + 1 + i];
        }
        
        // Maintain current index of sub-arrays and main array
        int i = 0;
        int j = 0;
        int k = l;
        
        // Until we reach either end of either L or R, pick larger among
        // elements L and M and place them in the correct position at A[l..r]
        while(i < n1 && j < n2){
            if(L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        // When we run out of elements in either L or R,
        // pick up the remaining elements and put in A[l..r]
        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    
    void mergeSort2(){
        mergeSortUtil2(_arr, 0, _index - 1);
    }
    
    void mergeSortUtil2(int arr[], int l, int r){
        if(l < r){
            int m = (l + r)/2;
            mergeSortUtil2(arr, l, m);
            mergeSortUtil2(arr, m + 1, r);
            merge2(arr, l, m, r);
        }
    }
    
    void merge2(int arr[], int l, int m, int r){
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1];
        int R[n2];
        
        for(int i = 0; i < n1; i++){
            L[i] = arr[l + i];
        }
        for(int i = 0; i < n2; i++){
            R[i] = arr[m + 1 + i];
        }
        
        int i = 0;
        int j = 0;
        int k = l;
        
        //Flip the sign to from <= to >
        while(i < n1 && j < n2){
            if(L[i] > R[j]){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    /* This function takes last element as pivot, places
    the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
    to left of pivot and all greater elements to right
    of pivot */
    int partition(int arr[], int low, int high){
        int pivot = arr[high];
        int i = (low - 1); // Index of smaller element
        
        for(int j = low; j < high; j++){
            // If current element is smaller than the pivot
            if(arr[j] < pivot){
                i++; // increment index of smaller element
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    
    void quickSort(){
        quickSortUtil(_arr, 0, _index - 1);
    }
    
    void quickSortUtil(int arr[], int low, int high){
        if(low < high){
            int pi = partition(arr, low, high);
            
            quickSortUtil(arr, low, pi - 1);
            quickSortUtil(arr, pi + 1, high);
        }
    }
    
    //Flip the < into >
    int partition2(int arr[], int low, int high){
        int pivot = arr[high];
        int i = (low - 1);
        
        for(int j = low; j < high; j++){
            if(arr[j] > pivot){
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
    
    void quickSort2(){
        quickSortUtil2(_arr, 0, _index - 1);
    }
    
    void quickSortUtil2(int arr[], int low, int high){
        if(low < high){
            int pi = partition2(arr, low, high);
            
            quickSortUtil2(arr, low, pi - 1);
            quickSortUtil2(arr, pi + 1, high);
        }
    }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // To heapify a subtree rooted with node i which is
    // an index in arr[].
    void heapify(int arr[], int size, int i){
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        // If left child is larger than root
        if(left < size && arr[left] > arr[largest]){
            largest = left;
        }
        
        // If right child is larger than largest so far
        if(right < size && arr[right] > arr[largest]){
            largest = right;
        }
        
        // If largest is not root
        if(largest != i){
            swap(arr[i], arr[largest]);
            
            // Recursively heapify the affected sub-tree
            heapify(arr, size, largest);
        }
    }
    
    void heapSort(){
        heapSortUtil(_arr, _index);
    }
    
    void heapSortUtil(int arr[], int size){
        // Build heap (rearrange array)
        for(int i = size/2 - 1; i >= 0; i--){
            heapify(arr, size, i);
        }
        
        // One by one extract an element from heap
        for(int i = size - 1; i > 0; i--){
            // Move current root to end
            swap(arr[0], arr[i]);
            
             // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }
    
    void heapify2(int arr[], int size, int i){
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if(left < size && arr[left] < arr[smallest]){
            smallest = left;
        }
        
        if(right < size && arr[right] < arr[smallest]){
            smallest = right;
        }
        
        if(smallest != i){
            swap(arr[i], arr[smallest]);
            
            heapify2(arr, size, smallest);
        }
    }
    
    void heapSort2(){
        heapSortUtil2(_arr, _index);
    }
    
    void heapSortUtil2(int arr[], int size){
        for(int i = size/2 - 1; i >= 0; i--){
            heapify2(arr, size, i);
        }
        
        for(int i = size - 1; i > 0; i--){
            swap(arr[0], arr[i]);
            
            heapify2(arr, i, 0);
        }
    }

};

int main(int argc, const char * argv[]) {
    Array arr;
    arr.insert(50);
    arr.insert(30);
    arr.insert(20);
    arr.insert(10);
    arr.insert(40);
    arr.print();
    arr.heapSort();
    arr.print();
    arr.heapSort2();
    arr.print();
    return 0;
}
