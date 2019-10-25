#include <iostream>

using namespace std;

struct data
{
    int low;
    int high;
    int mid;
};
int * arr;
int size_arr;
void read_data();
void merge(int low, int mid, int high);
void merge_sort(int low, int high);
void* merge_sort(void* arg);

int main()
{
    read_data();
    merge_sort(0,size_arr -1);
    cout << "array after sorting" << endl;
    for(int i = 0; i < size_arr; i++)
    {
        cout<< arr[i];
        cout << " ";
    }
    cout << endl;
    return 0;
}

void merge(int low, int mid, int high)
{
    // create 2 arrays with size of each part
    // which we need to merge them
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];

    // size1 is size of left part and size2 is size
    // of right part
    int size1 = mid - low + 1;
    int size2 = high - mid;
    int i;
    int j;

    // storing values in left part
    for (i = 0; i < size1; i++)
        left[i] = arr[i + low];

    // storing values in right part
    for (i = 0; i < size2; i++)
        right[i] = arr[i + mid + 1];

    int k = low;
    i = j = 0;

    // merge left and right in ascending order
    while (i < size1 && j < size2)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < size1)
    {
        arr[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < size2)
    {
        arr[k++] = right[j++];
    }
}
// merge sort function
void merge_sort(int low, int high)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high)
    {
        // create 2 threads
        // one for each half of the array
        pthread_t t1;
        pthread_t t2;
        // save the bounds of first half of the array in struct
        // and create a thread to apply  merge sort on the new array
        data* d=new data();
        d->low = low;
        d->high = mid;
        pthread_create(&t1, NULL, merge_sort, (void*)(d));
        // save the bounds of second half of the array in struct
        // and create a thread to apply  merge sort on the new array
        data* d1 = new data();
        d1->low = mid +1 ;
        d1->high = high;
        pthread_create(&t2, NULL, merge_sort, (void*)(d1));
        // wait untill 2 threads finish their work to apply merge
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);

        merge(low, mid, high);


    }
}

// thread function for multi-threading
void* merge_sort(void* arg)
{
    struct data* param;
    param=(data*)arg;
    // calculating mid point of array
    int mid = param->low + (param->high - param->low) / 2;
    if (param->low < param->high)
    {
        // create 2 threads each time we divide the array
        // each one to apply the same again on the new array
        pthread_t t1;
        pthread_t t2;
        // save the bounds of first half of the array in struct
        // and create a thread to apply merge sort on the new array
        data* d=new data();
        d->low = param->low;
        d->high = mid;
        pthread_create(&t1, NULL, merge_sort, (void*)(d));
        // save the bounds of second half of the array in struct
        // and create a thread to apply  merge sort on the new array
        data* d1 = new data();
        d1->low = mid +1 ;
        d1->high = param->high;
        pthread_create(&t2, NULL, merge_sort, (void*)(d1));
        // wait untill 2 threads finish their work to apply merge
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        merge(param->low, mid, param->high);
    }
}

// read array and its size from file
void read_data()
{
    freopen("merge-sort-readme.txt","r",stdin);

    cin >> size_arr;

    arr = new int[size_arr];


    for(int i = 0 ; i < size_arr ; i++)
    {
        cin >> arr[i];
    }

    cout <<"array before sorting" << endl;
    // print the array before sorting
    for(int i = 0 ; i < size_arr ; i++)
    {
        cout << arr[i];
        cout << " ";
    }
    cout << endl;

}
