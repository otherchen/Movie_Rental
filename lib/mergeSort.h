#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>

using namespace std;

class MergeSort{
  public:
    template <class T>
    static vector<T> sort (vector<T> a) {
      //sort code here
      int start = 0;
      int end = a.size()-1;
      merge_sort(a, start, end);
      return a;
    }

    template <class T>
    static void merge_sort(vector<T> & a, int low, int high)
    {
        int mid;
        if (low < high)
        {
            mid=(low+high)/2;
            merge_sort(a,low,mid);
            merge_sort(a,mid+1,high);
            merge(a,low,high,mid);
        }
        return;
    }

    template <class T>
    static void merge(vector<T> & a, int low, int high, int mid)
    {
        int i, j, k;
        T c[50];
        i = low;
        k = low;
        j = mid + 1;
        while (i <= mid && j <= high)
        {
            if (a[i] < a[j])
            {
                c[k] = a[i];
                k++;
                i++;
            }
            else
            {
                c[k] = a[j];
                k++;
                j++;
            }
        }
        while (i <= mid)
        {
            c[k] = a[i];
            k++;
            i++;
        }
        while (j <= high)
        {
            c[k] = a[j];
            k++;
            j++;
        }
        for (i = low; i < k; i++)
        {
            a[i] = c[i];
        }
    }

};

#endif