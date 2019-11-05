#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <numeric>

using namespace std;

void insertionSort(vector<int> list)
{
    int temp;
    for(int i = 1; i < list.size(); i++)
    {
        temp = list[i];
        int j;
        for(j = i-1; j >= 0 && list[j] > temp; j--)
        {
            list[j+1] = list[j];
        }
        list[j+1] = temp;
    }
}

//swap function for selectionSort and bubbleSort
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// check the effect of &
void selectionSort(vector<int> arr)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < arr.size()-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < arr.size(); j++)
        if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void bubbleSort(vector<int> arr)
{
    int i, j;
    for (i = 0; i < arr.size()-1; i++)

    // Last i elements are already in place
    for (j = 0; j < arr.size()-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}


void merge(vector<int>left, vector<int> right, vector<int> bars)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR)
    {
        if (left[j] < right[k]) {
            bars[i] = left[j];
            j++;
        }
        else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}

void mergeSort(vector<int> bar) {
    if (bar.size() <= 1) return;

    int mid = bar.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(bar[j]);
    for (size_t j = 0; j < (bar.size()) - mid; j++)
        right.push_back(bar[mid + j]);

    mergeSort(left);
    mergeSort(right);
    merge(left, right, bar);
}

int partition(vector<int> &values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex];
    int i = left, j = right;
    int temp;
    while(i <= j) {
        while(values[i] < pivotValue) {
            i++;
        }
        while(values[j] > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(vector<int> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        quickSort(values, left, pivotIndex - 1);
        quickSort(values, pivotIndex, right);
    }
}

void heapify(vector<int> &arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(vector<int> &arr)
{
    // Build heap (rearrange array)
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        heapify(arr, arr.size(), i);

    // One by one extract an element from heap
    for (int i=arr.size()-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


int main()
{
    vector<int> v(100000);
    iota(v.begin(), v.end(), 1);

    vector<int> vr = v;
    sort(vr.begin(), vr.end(), greater<int>());

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    vector<int> vrand = v;
    shuffle(vrand.begin(), vrand.end(), std::default_random_engine(seed));

    // Find the min element
    cout << "\nMin Element = "
             << *min_element(v.begin(), v.end());

    // Find the max element
    cout << "\nMax Element = "
             << *max_element(v.begin(), v.end()) << endl;
    double total = 0;
    double max = 0;
    double min = 10e7;

    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        insertionSort(vrand);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Insertion Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Insertion Sort: random" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        insertionSort(v);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Insertion Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Insertion Sort: sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        insertionSort(vr);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Insertion Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Insertion Sort: reverse sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        selectionSort(vrand);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Selection Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Selection Sort: random" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        selectionSort(v);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Selection Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Selection Sort: sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        selectionSort(vr);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Selection Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Selection Sort: reverse sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        bubbleSort(vrand);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Bubble Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Bubble Sort: random" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        bubbleSort(v);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Bubble Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Bubble Sort: sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        bubbleSort(vr);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Bubble Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Bubble Sort: reverse sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        mergeSort(vrand);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Merge Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Merge Sort: random" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        mergeSort(v);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Merge Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Merge Sort: sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        mergeSort(vr);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Merge Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Merge Sort: reverse sorted" << endl;
    cout << "Average execution time: " << total/10/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        vector<int> vrand1 = vrand;
        auto t1 = chrono::high_resolution_clock::now();
        quickSort(vrand1, 0, vrand1.size() - 1);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Quick Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Quick Sort: random" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        quickSort(v, 0, v.size() - 1);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Quick Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Quick Sort: sorted" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        vector<int> vr1 = vr;
        auto t1 = chrono::high_resolution_clock::now();
        quickSort(vr1, 0, vr1.size() - 1);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Quick Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Quick Sort: reverse sorted" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        vector<int> vrand2 = vrand;
        auto t1 = chrono::high_resolution_clock::now();
        heapSort(vrand2);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Heap Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Heap Sort: random" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        auto t1 = chrono::high_resolution_clock::now();
        heapSort(v);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Heap Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Heap Sort: sorted" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";

    total = 0;
    max = 0;
    min = 10e7;
    for(int i=0;i<10;i++) {
        vector<int> vr2 = vr;
        auto t1 = chrono::high_resolution_clock::now();
        heapSort(vr2);
        auto t2 = chrono::high_resolution_clock::now();
        //Calculate the running time of the function given
        double duration = chrono::duration_cast<chrono::milliseconds>( t2 - t1 ).count();
        //Output the duration in microseconds
        cout << "Duration of Heap Sort is: " << duration/1000 << " seconds" << endl;
        if(duration > max) {
            max = duration;
        }
        if(duration < min) {
            min = duration;
        }
        total += duration;
    }
    cout << "Heap Sort: reverse sorted" << endl;
    cout << "Average execution time: " << (total/10)/1000 << " seconds" << endl;
    cout << "Maximum execution time: " << max/1000 << " seconds" << endl;
    cout << "Minimum execution time: " << min/1000 << " seconds" << endl << "\n";


    /*
    //To check if the data didn't change after it got executed.
    cout << "vrand: " << endl;
    copy(begin(vrand), end(vrand),ostream_iterator<int>(std::cout, "\n"));
    cout << "v" << endl;
    copy(begin(v), end(v),ostream_iterator<int>(std::cout, "\n"));
    cout << "vr" << endl;
    copy(begin(vr), end(vr),ostream_iterator<int>(std::cout, "\n"));
    */

    return 0;
}



