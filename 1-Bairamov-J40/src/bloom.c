#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable : 4996)

#define ARR_SIZE 1023
#define ARR_EL_SIZE 8
#define ACCURACY 1000

typedef struct {
	char* bits;
	int m;
	int hashesNumber;
} bloomFilter_t;

bloomFilter_t createBloomFilter(int m);
void destroyBloomFilter(bloomFilter_t* bloomFilter);
void add(bloomFilter_t* bloomFilter, int element);
int contains(bloomFilter_t* bloomFilter, int element);
void ithHash(int i, int m, int element, int* hasValues);

int main(int argc, char* argv[]) {
	bloomFilter_t bloomFilter = createBloomFilter(ARR_SIZE);
	char command;
	int key = 0;
	while (scanf("%c", &command) >= 1) {
		if (command != 'q') {
			scanf("%i", &key);
		}

		switch (command) {
		case 'a':
			add(&bloomFilter, key);
			break;
		case 'f':
			if (contains(&bloomFilter, key)) {
				puts("yes");
			}
			else {
				puts("no");
			}

			break;
		case 'q':
			destroyBloomFilter(&bloomFilter);
			return 0;
		}
	}

	return 0;
}

bloomFilter_t createBloomFilter(int m) {
	bloomFilter_t bloomFilter;
	bloomFilter.m = ARR_SIZE;
	bloomFilter.hashesNumber = (int)log2(ACCURACY);
	bloomFilter.bits = (char*)calloc(ARR_SIZE, sizeof(char));
	if (bloomFilter.bits == NULL) {
		printf("Error allocating memory to bits\n");
		exit(1);
	}

	return bloomFilter;
}

void destroyBloomFilter(bloomFilter_t* bloomFilter) {
	free(bloomFilter->bits);
}

void add(bloomFilter_t* bloomFilter, int element) {
	for (int i = 0; i < bloomFilter->hashesNumber; i++) {
		int hashValues[2];
		ithHash(i, bloomFilter->m, element, hashValues);
		bloomFilter->bits[hashValues[0]] |= 1 <<  hashValues[1];
	}
}

int contains(bloomFilter_t* bloomFilter, int element) {
	for (int i = 0; i < bloomFilter->hashesNumber; i++) {
		int hashValues[2];
		ithHash(i, bloomFilter->m, element, hashValues);
		if (((bloomFilter->bits[hashValues[0]] >> hashValues[1]) & 1) == 0) {
			return 0;
		}
	}

	return 1;
}

void ithHash(int i, int m, int element, int* hasValues) {
	hasValues[0] = (i + element) % m;
	hasValues[1] = (i + element) % ARR_EL_SIZE;
}