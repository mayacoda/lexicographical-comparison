#include <stdio.h>
#include <assert.h>
#include <string.h>

/**
 * Lexicographical Array Comparison Function
 *
 * Accepts two arrays of any type, size of element type, length of the two arrays,
 * and a comparison function for each element of the two arrays.
 *
 * Returns int provided by comparison function.
 *
 */
int lexicographicalArrayCompare (void * arr1, void * arr2, int elemSize, int size1, int size2, int (*compare) (void *, void *)) {

	// compare first element of array with comparator function
	int result = compare(arr1, arr2);

    // in case the first elements do not match, check the next elements
    // in the array, if they exist
	if (result == 0 && size1 != 0 && size2 != 0) {

		// decrease the size of each array
		size1--;
		size2--;

		// increment pointers to compare the next element
		void * arr1Addr = (char *) arr1 + elemSize;
		void * arr2Addr = (char *) arr2 + elemSize;

        assert(arr1Addr != NULL);
        assert(arr2Addr != NULL);

        // check the next element
		return lexicographicalArrayCompare(arr1Addr, arr2Addr, elemSize, size1, size2, compare);

    } else {

        return result;
    }
}

/**
 * Comparison Function for double
 */
int compareDouble (void * pn, void * pm) {
    double n = *(double *) pn;
    double m = *(double *) pm;

    printf("comparing n = %f, m = %f\n", n, m);

	if (n < m) {
		return -1;
	} else if (n > m) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * Comparison Function for char
 */
int compareChar (void * pn, void * pm) {
    char * n = (char *) pn;
    char * m = (char *) pm;

    return memcmp(n, m, sizeof(char));
}


int main(int argc, char const *argv[]) {

    double a1[] = {1, 2, 3, 4, 5, 8};
    double a2[] = {1, 2, 3, 2, 5, 6};

    printf("comparing a1 and a2 = %d\n", lexicographicalArrayCompare(a1, a2, sizeof(double), 6, 6, compareDouble));

    char str1[] = "asdf";
    char str2[] = "asdf";

    printf("comparing str1 and str2 = %d\n", lexicographicalArrayCompare(str1, str2, sizeof(char), 4, 4, compareChar));

    return 0;
}
