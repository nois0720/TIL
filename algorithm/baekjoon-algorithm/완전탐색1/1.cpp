#include <iostream>
#include <string>
using namespace std;

int main() {
	int E, S, M;
	int year = 0;

	cin >> E; cin >> S; cin >> M;

	while(!(E == S && S == M)) {
		E -= 1; S -= 1; M -= 1;

		if(E == 0) { E = 15; }
		if(S == 0) { S = 28; }
		if(M == 0) { M = 19; }

		year++;
	}
	
	printf("%d\n", year + E);
	return 0;
}