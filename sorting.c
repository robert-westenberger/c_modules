// #include <stdlib.h>
// #include <limits.h>
// #include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"


static void merge(int *arr, int leftIndex, int middleIndex, int rightIndex, int recurseLevel) {
	int i, j, k;

	int n1 = middleIndex - leftIndex + 1;
	int n2 = rightIndex - middleIndex;
	int tempLeftArray[n1];
	int tempRightArray[n2];
	printf("left Index: %d middleIndex: %d rightIndex: %d recurseLevel: %d \n", leftIndex, middleIndex, rightIndex, recurseLevel);
	/* Copy data to temp arrays */
	for (i = 0; i < n1; i++) {
		tempLeftArray[i] = *(arr + leftIndex + i);
	}
	for (j = 0; j < n2; j++) {
		tempRightArray[j] = *(arr + middleIndex + j + 1);
	}
	
	/* Maintain current index of sub-arrays */
	i=0;
	j=0;
	k=leftIndex;

	/* Until we reach either end of either temporary array, pick larger among
	elements in the temp arrays and place them in the correct position in arr */
	while (i < n1 && j < n2) {
		if (tempLeftArray[i] <= tempRightArray[j]) {
			*(arr + k) = tempLeftArray[i];
			i++;
		}
		else {
			*(arr + k) = tempRightArray[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
    are any */
	while (i < n1) {
		*(arr + k) = tempLeftArray[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
    are any */
	while (j < n2) {
		*(arr + k) = tempRightArray[j];
		j++;
		k++;
	}
}
void mergeSort(int *arr, int leftIndex, int rightIndex, int recurseLevel) {
	int i;
  if (leftIndex < rightIndex) {
		/* Same as (leftIndex + r)/2, but avoids overflow for large leftIndex and rightIndex */
		int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
		printf("Array: ");
		for(i = leftIndex; i < rightIndex + 1; i++) {
			printf("%d ", *(arr + i));
		}
		printf("\n");
		mergeSort(arr, leftIndex, middleIndex, recurseLevel + 1);
		mergeSort(arr, middleIndex + 1, rightIndex, recurseLevel + 1);
		merge(arr, leftIndex, middleIndex, rightIndex, recurseLevel);
	}
}