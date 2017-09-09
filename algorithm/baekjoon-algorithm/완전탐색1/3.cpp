#include <iostream>
#include <string>
using namespace std;

int get_value(int index);

int values[10];

int main() {
	fill_n(values, 10, -1);
	values[0] = 1;
	values[1] = 2;
	values[2] = 4;
	
	int n;
	cin >> n;
	
	int* numbers = (int*)malloc(sizeof(int) * n);

	for(int i = 0; i < n; i ++) {
		cin >> numbers[i];
	}
	
	for(int i = 0; i < n; i++) {
		printf("%d\n", get_value(numbers[i] - 1));
	}

	return 0;
}

int get_value(int index) {
	if(index <= 2) return values[index];

	if(values[index] < 0) {
		values[index] = get_value(index - 1) + get_value(index - 2) + get_value(index - 3);
	}

	return values[index];
}