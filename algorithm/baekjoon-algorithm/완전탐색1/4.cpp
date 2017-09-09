#include <algorithm>
#include <iostream>
using namespace std;

int main() {
	int n;
	int numbers[8];
    cin >> n;

    for(int i = 0; i < n; i++) {
    	cin >> numbers[i];
    }

    sort(numbers, numbers + n);

    int result = 0;
    if(n % 2 == 0) {
    	for(int i = n - 1; i >= n/2; i--) {
    		if(i == n/2) {
				result += numbers[i];
    		} else {
    			result += numbers[i] * 2;
    		}
    	}

    	for(int i = n/2 - 1; i >= 0; i--) {
    		if(i == n/2 - 1) {
				result -= numbers[i];
    		} else {
    			result -= numbers[i] * 2;
    		}
    	}
    } else {
    	for(int i = n - 1; i > n/2; i--) {
    		if(i == n/2) {
    			printf("1 %d\n", numbers[i]);
				result += numbers[i];
    		} else {
    			printf("2 %d\n", numbers[i]);
    			result += numbers[i] * 2;
    		}
    	}

    	for(int i = n/2; i >= 0; i--) {
    		if(i == n/2) {
    			printf("3 %d\n", numbers[i]);
				result -= numbers[i];
    		} else {
    			printf("4 %d\n", numbers[i]);
    			result -= numbers[i] * 2;
    		}
    	}
    }
    printf("%d\n", result);
    return 0;
}