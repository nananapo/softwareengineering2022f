#include <iostream>
#include <bits/stdc++.h>
#include "common.h"
#include <chrono>
#include <vector>
#include <random>
#define RANGE (1000*1000*10)
using namespace std;

std::vector<int> Input;         
std::vector<int> OriginalInput; 

Measure measure;

void init(int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Usage: ./program datasize" << std::endl;
    exit(0);
  }
  int size = atoi(argv[1]);

  for(int i = 0; i < size; i++) {
    OriginalInput.push_back(i);
  }
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(OriginalInput.begin(), OriginalInput.end(), engine);
}

void resetInput()
{
  Input.clear();
  for(int i = 0; i < (int)OriginalInput.size(); i++) {
    int value = OriginalInput[i]; 
    Input.push_back(value);
  }
}

void iCannotBelieve()
{
  std::vector<int>& array = Input;
  // begin
  resetInput();

  measure.start();
  for (int i = 0; i < (int)array.size(); i++) {
    printf("[%d  ] ",i);
    for (int i = 0; i < (int)array.size(); i++) {
      printf("%d ", array[i]);
    } printf("\n");
    for (int j = 0; j < (int)array.size(); j++) {    
      if (array[i] < array[j]) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
        
        printf("[%d:%d] ",i,j);
        for (int k = 0; k < (int)array.size(); k++) {
          printf("%d ", array[k]);
        } printf("\n");

      }
    }
  }
  
  measure.end();
  check_vec(array);
  measure.print_elapsed_time("ICan'tBelieveItCanSort: ");
}

void insertSort()
{
  std::vector<int>& array = Input;
  // begin
  resetInput();
  measure.start();

  for (int i = 0; i < (int)array.size(); i++)
  {
    int mindex = i;
    for (int j = i+1; j < (int)array.size(); j++)
    {
      if (array[j] < array[mindex])
        mindex = j;
    }
    // swap!
    int tmp = array[mindex];
    array[mindex] = array[i];
    array[i] = tmp;
  }

  // end
  measure.end();
  check_vec(array);
  measure.print_elapsed_time("Insert: ");
}

// A utility function to swap two elements
void swap(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

// A utility function to print an array
void print(int arr[], int n)
{
  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (std::vector<int>& arr, int low, int high)
{
	int	tmp;
	int x = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (arr[j] <= x)
		{
			i += 1;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	arr[high] = arr[i+1];
	arr[i+1] = x;

/*
	// DEBUG
	printf("%d:%d(pivot=%d, index=%d) ", low, high, x, i+1);
	for (int j = low; j <= high; j++)
		printf("%d ", arr[j]);
	printf("\n");
*/

	return (i+1);
}

/* The main function that implements QuickSort
arr[] --> Input to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(std::vector<int>& arr, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(arr, low, high);
		quickSort(arr, low, pivot-1);
		quickSort(arr, pivot+1, high);
	}
}

void quickSortStart() {
  vector<int>& arr = Input;
  resetInput();
  measure.start();

  quickSort(arr, 0, arr.size() - 1);

  measure.end();
  check_vec(arr);
  measure.print_elapsed_time("Quick: ");
}

// The main function that sort
void countSort()
{
  vector<int>& arr = Input;
  resetInput();
  int* output = new int[arr.size()];
 
  // Create a count array to store count of individual
  // number and initialize count array as 0
  int* count = new int[RANGE + 1];
  memset(count, 0, sizeof(int) * (RANGE+1));

  measure.start();

  for (int i = 0; i < arr.size(); i++)
	count[arr[i]]++;

  int i = 0;
  for (int j = 0; j < RANGE + 1; j++)
	for (int k = 0; k < count[j]; k++)
		arr[i++] = j;

  measure.end();

  free(count);
  free(output);
  check_vec(arr);
  measure.print_elapsed_time("Count: ");
}

// K桁目に関して安定ソートする
void stableSortK(std::vector<int>& arr, int k)
{
	int p	= std::pow(10,k-1);
	int p2	= p * 10;
	// insertion sort
	for (int i = 0; i < arr.size(); i++)
	{
		int mindex = i;
		for (int j = i+1; j < arr.size(); j++)
		{
			if ((arr[mindex]%p2)/p > (arr[j]%-p2)/p)
				mindex = j;
		}
		int tmp = arr[i];
		arr[i] = arr[mindex];
		arr[mindex] = tmp;
	}
}

void radixSort()
{
  std::vector<int>& array = Input;
  // begin
  resetInput();
  measure.start();

  int l10 = 0;
  for (int b = 1; b <= RANGE; b*=10) l10 += 1;
  
  for (int i = 1; i < l10; i++)
	stableSortK(array, i);

  // end
  measure.end();
  check_vec(array);
  measure.print_elapsed_time("Radix: ");
}

// A utility function to get maximum value in arr[]
int getMax(std::vector<int>& arr, int n)
{
  int mx = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}


void defaultSort()
{
  vector<int>& arr = Input;
  resetInput();
  measure.start();
  std::sort(arr.begin(), arr.end());
  measure.end();
  check_vec(arr);
  measure.print_elapsed_time("std::sort: ");
}

int main(int argc, char *argv[])
{
  init(argc, argv);

  insertSort();
  quickSortStart();  
  defaultSort();
  countSort();
  radixSort();

  return 0;
}
