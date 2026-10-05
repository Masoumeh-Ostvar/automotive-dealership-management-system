#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

struct order_struct
{
    string Service_Name;
    string Agency_Name;
    string Customer_Name;
    int Immediacy_Level;
};

struct PriorityQueue
{
private:
    vector<order_struct> A;

    int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    int LEFT(int i)
    {
        return (2 * i + 1);
    }

    int RIGHT(int i)
    {
        return (2 * i + 2);
    }

    void heapify_down(int i)
    {
        int left = LEFT(i);
        int right = RIGHT(i);
        int largest = i;
        if (left < size() && A[left].Immediacy_Level > A[i].Immediacy_Level)
        {
            largest = left;
        }

        if (right < size() && A[right].Immediacy_Level > A[largest].Immediacy_Level)
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(A[i], A[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i)
    {
        if ((i != 0) && (A[PARENT(i)].Immediacy_Level < A[i].Immediacy_Level))
        {
            swap(A[i], A[PARENT(i)]);
            heapify_up(PARENT(i));
        }
    }

public:
    unsigned int size()
    {
        return A.size();
    }

    bool empty()
    {
        return size() == 0;
    }

    void push(order_struct key)
    {
        A.push_back(key);

        int index = size() - 1;
        heapify_up(index);
    }

    void pop()
    {        
        A[0] = A.back();
        A.pop_back();
        heapify_down(0);
    }

    order_struct top()
    {
        return A.at(0);
    }
};
