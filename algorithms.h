#ifndef ALGORITHMS
#define ALGORITHMS

#include <vector>

enum { Bubble, Quick, Merge, Combined };

template <typename T>
class Sort
{
private:
	static void swap(T& x, T& y)
	{
		T t = x;
		x = y;
		y = t;
	}

	static void quick_sort(std::vector<T>& arr, int left, int right)
	{
		if (left < right)
		{
			int pivot = partition(arr, left, right);
			quick_sort(arr, left, pivot);
			quick_sort(arr, pivot + 1, right);
		}
	}

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

	static void quick_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		quick_sort(arr, 0, arr.size() - 1);
	}

	static void bubble_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		bubble_sort(arr, 0, arr.size() - 1);
	}

	static void merge_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		merge_sort(&arr[0], arr.size());
	}

	static void combined_sort(std::vector<T>& arr)
	{
		if (arr.size() < 2) return;

		combined_sort(arr, 0, arr.size() - 1);
	}

};

#endif /* ALGORITHMS */