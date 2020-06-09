///	\file
///	\brief This file contains definition and implementation of class Sort
#ifndef ALGORITHMS
#define ALGORITHMS

#include <vector>

///	\brief Class with sorting functions
/// \details This is template class with static functions. You can sort your vector in different ways:
/// Bubble, Merge, Quick and Combined sorts.
/// \tparam T Type of data that you wanna sort
/// \warning Type T must be comparable
template <typename T>
class Sort
{
private:
	/// \brief Swaps two values
	/// \param[in,out] x First value
	/// \param[in,out] y Second value
	static void swap(T& x, T& y)
	{
		T t = x;
		x = y;
		y = t;
	}

	/// \brief Quick sort function
	/// \details Function that recursive sorts left and right parts of vector. Sorting is on interval [left; right].
	/// \param[in,out] arr Our vector
	/// \param[in] left Left sorting border 
	/// \param[in] right Right sorting border
	static void quick_sort(std::vector<T>& arr, int left, int right)
	{
		if (left < right)
		{
			int pivot = partition(arr, left, right);
			quick_sort(arr, left, pivot);
			quick_sort(arr, pivot + 1, right);
		}
	}

	/// \brief Quick sort helpful function
	/// \details Function that get middle value from interval [left; right] as pivot. Changes order on this interval.
	/// Values from [left; pivot) are <= than pivot and values from (pivot; right] are >= than pivot.
	/// This function using in \ref quick_sort() and \ref combined_sort() functions.
	/// \param[in,out] arr Our vector
	/// \param[in] left Left sorting border
	/// \param[in] right Right sorting border
	/// \return Index of pivot value
	static size_t partition(std::vector<T>& arr, int left, int right)
	{
		size_t mid = left + (right - left) / 2;
		if (arr[left] < arr[mid])
			swap(arr[left], arr[mid]);

		if (arr[right] > arr[left])
			swap(arr[right], arr[left]);

		if (arr[right] > arr[mid])
			swap(arr[right], arr[mid]);

		T pivot = arr[mid];
		int i = left, j = right;
		while (true)
		{
			do
			{
				++i;
			} while (arr[i] > pivot);
			do
			{
				--j;
			} while (arr[j] < pivot);

			if (i >= j) return j;
			swap(arr[i], arr[j]);
		}
	}

	/// \brief Bubble sort function
	/// \details Function that sorts vector on interval [left; right].
	/// \param[in,out] arr Our vector
	/// \param[in] left Left sorting border 
	/// \param[in] right Right sorting border
	static void bubble_sort(std::vector<T>& arr, size_t left, size_t right)
	{
		bool swaped;
		size_t i = left;

		while (true)
		{
			i++;
			swaped = false;

			for (size_t j = right; i <= j; --j)
			{
				if (arr[j - 1] < arr[j])
				{
					swap(arr[j - 1], arr[j]);
					swaped = true;
				}
			}
			if (!swaped) return;
		}
	}

	/// \brief Merge sort function
	/// \details Recursive function that sorts vector on interval [0; size - 1].
	/// \param[in,out] ptr_arr Pointer to the first element of sorting interval
	/// \param[in] size Size of sorting interval
	static void merge_sort(T* ptr_arr, size_t size)
	{
		if (size > 1)
		{
			size_t i = size / 2;
			merge_sort(ptr_arr, i);
			merge_sort(ptr_arr + i, size - i);
			merge(ptr_arr, i, size);
		};
	}

	/// \brief Merge sort helpful function
	/// \details Merge two sorted subarrays [0; i) and [i; size - 1].
	/// \param[in,out] ptr_arr Pointer to the first element of sorting interval
	/// \param[in] partition Middle of current interval
	/// \param[in] size Size of sorting interval
	static void merge(T* ptr_arr, size_t partition, size_t size)
	{
		T* pa = new T[size];
		for (size_t i = 0; i < size; ++i)
		{
			pa[i] = ptr_arr[i];
		}

		size_t i = 0, j = 0, k = partition;
		for (; i < size && j < partition && k < size; ++i)
		{
			ptr_arr[i] = (pa[j] > pa[k] ? pa[j++] : pa[k++]);
		}

		while (j < partition)
		{
			ptr_arr[i++] = pa[j++];
		}

		while (k < size)
		{
			ptr_arr[i++] = pa[k++];
		}

		delete[] pa;
	}

	/// \brief Combined sort function
	/// \details Function that combines bubble sort and quick sort. When size of subarray less equal than 10
	/// we use bubble sort.
	/// \param[in,out] arr Our vector
	/// \param[in] left Left sorting border 
	/// \param[in] right Right sorting border
	static void combined_sort(std::vector<T>& arr, int left, int right)
	{
		if (left < right)
		{
			if (right - left <= 10)
			{
				bubble_sort(arr, left, right);
				return;
			}

			int pivot = partition(arr, left, right);
			combined_sort(arr, left, pivot);
			combined_sort(arr, pivot + 1, right);
		}
	}

public:

	/// \brief Quick sort interface
	/// \param[in,out] arr Our vector
	static void quick_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		quick_sort(arr, 0, arr.size() - 1);
	}

	/// \brief Bubble sort interface
	/// \param[in,out] arr Our vector
	static void bubble_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		bubble_sort(arr, 0, arr.size() - 1);
	}

	/// \brief Merge sort interface
	/// \param[in,out] arr Our vector
	static void merge_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		merge_sort(&arr[0], arr.size());
	}

	/// \brief Combined sort interface
	/// \param[in,out] arr Our vector
	static void combined_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		combined_sort(arr, 0, arr.size() - 1);
	}
};

#endif /* ALGORITHMS */