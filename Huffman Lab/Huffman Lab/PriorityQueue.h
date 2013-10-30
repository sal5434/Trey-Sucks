// PriorityQueue.h - Huffman Code Lab
// Written by Sarah Lakos

#include <iostream>
#include <vector>

using namespace std;

template<typename DATA_TYPE>
class PriorityQueue
{
public:
   PriorityQueue() {}

   // Returns the first element from the queue
   const DATA_TYPE& Top() const;

   // Returns true when the queue is empty
   bool IsEmpty() const;

   // Returns number of elements in the queue
   unsigned Size () const;

   // Pops the first element from the queue and rearranges the QueueData to maintain priority
   void Pop();

   // Pushes a new element into the queue and rearranges the QueueData to maintain priority
   void Push(const DATA_TYPE& newValue);

// private:
   // PriorityQueue: heap packaged into vector
   vector<DATA_TYPE> d_array;
private:
};

// PriorityQueue<int> testQueue;

template<class DATA_TYPE>
const DATA_TYPE& PriorityQueue<DATA_TYPE>::Top() const 
{
	if (IsEmpty())
	{
		throw "Empty queue.";
	}
	return d_array[0];
}

template<typename DATA_TYPE>
bool PriorityQueue<DATA_TYPE>::IsEmpty() const
{
	return d_array.empty();
}

template<typename DATA_TYPE>
unsigned PriorityQueue<DATA_TYPE>::Size() const
{
	return d_array.size();
}

template<typename DATA_TYPE>
void PriorityQueue<DATA_TYPE>::Push(const DATA_TYPE& newValue)
// Pushes a new element into the queue and rearranges the QueueData to maintain priority
{
	d_array.push_back(newValue); // Push new value to the end of the queue

	int child = d_array.size() - 1; // The index of the child node corresponding to the new value
	int parent = (child - 1) / 2; // Determine the index of it's parent

	while( (parent >= 0) && (*d_array[parent] > *d_array[child]) )
	// while we are not at the top and the child is larger than the parent
	{
		swap(d_array[parent], d_array[child]); // Swap the parent and the child to maintain order
		// Parent becomes the child
		child = parent;
		parent = (child-1)/2;
	}
}

template<typename DATA_TYPE>
void PriorityQueue<DATA_TYPE>::Pop()
// removes the last item from the heap and places it at the top and moves the 
// item down the heap until the heap property is restored.
{
	if (d_array.empty())
	{
		throw "ERROR: QUEUE IS EMPTY";
	}

	std::swap(d_array[0], d_array[d_array.size()-1]);
	d_array.pop_back();
	int parent = 0;

	while (true)
	{
		unsigned int left_child = 2 * parent + 1;

		if (left_child >= d_array.size())
		{
			break;
		}

		unsigned int right_child = left_child + 1;
		int min_child = left_child;

		if (right_child < d_array.size() && d_array[left_child] < d_array[right_child])
		{
			min_child = right_child;
		}

		if (*d_array[parent] > *d_array[min_child])
		{
			std::swap(d_array[min_child], d_array[parent]);
			parent = min_child;
		}

		else // array is empty or finished
		{
			break;
		}
	}
}
