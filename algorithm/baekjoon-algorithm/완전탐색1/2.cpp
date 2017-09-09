#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int get_fst_number(int number);

int N;
int broken_count;
int* broken_numbers;

int main() {
	cin >> N;
	cin >> broken_count;

	broken_numbers = (int*)malloc(sizeof(int) * broken_count);
	for(int i = 0; i < broken_count; i++) {
		cin >> broken_numbers[i];
	}

	int temp_N = N; int N_len = 0;
	while(temp_N != 0) {
		temp_N /= 10;
		N_len++;
	}

	temp_N = N;
	int first_num = 0;
	int adjacent = 0;
	for(int i = N_len; i > 0; i--) {
		int divider = pow(10, i - 1);
		int num = temp_N / divider;

		if(i == N_len) {
			first_num = get_fst_number(num);
			adjacent += first_num * divider;
		} else if(first_num > num) {
			
		} else {

		}

		temp_N -= divider * num;
	}
}

int get_fst_number(int number) {
	int value = 1;
	int multiplier = 0;
	printf("input number: %d\n", number);

	for(int i = 0; i < broken_count; i++) {
		for(int j = 0; j < broken_count; j++) {
			if(broken_numbers[j] == number) {
				multiplier = pow(-1, i);
				number += multiplier * value;
				value++;
				printf("number : %d\n", number);
				break;
			}
		}
	}

	return number;
}