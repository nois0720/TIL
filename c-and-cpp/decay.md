# Decay

## 변수, 포인터

먼저 c의 Decay에 대해서 알아보기 전에, 변수와 포인터, 배열에 대해 정리해보자. 

```c
int a = 8;
```

위와 같은 C의 문장이 있다고 하자. 'a'는 컴파일 과정에서 0x1234와 같은 주소로 변경된다. 따라서 위의 문장은 `int 0x1234 = 8`과 같은 의미를 지니는데, '메모리 0x1234 번지에 4byte(int)의 공간에 8이라는 값을 넣어라' 라는 의미를 가진다고 해석할 수 있다.

```c
int a = 8; // 0x1234
int b = 2; // 0x5678

a = b;
```

그리고, 또 다른 변수인 b가 있을 때, `int b = 2`가 `int 0x5678 = 2`와 같이 된다고 하자. 그럼 마지막 줄인 `a = b`는 0x1234 번지에 0x5678에 있는 2라는 값을 넣어라 라고 할 수 있겠다.

이번에는 포인터의 예를 들어보자. 포인터도 a, b와 같이 메모리에 저장공간을 가지는 변수이다. 하지만 '*'를 붙여 정의한다는 점, 값을 주소로 가진다는 점에서 차이가 있다.

```c
int *ptr = &a;
```

위 문장을 컴파일하면 `int* 0x2345 = $0x1234`와 같이 된다. a의 주소 앞에 $가 보이는데, 이는 주소값을 지칭할때 사용한다고 한다. 즉, a의 값 8을 의미하는게 아니라 0x1234주소 자체를 의미한다. 그래서 위의 문장은 `0x2345에 int* 주소를 저장할 공간이 있다. 거기에 주소값 0x1234를 넣어라`라는 의미가 된다.

## array

```c
int arr1[5] = {1, 2, 3, 4, 5};
```

이 문장을 컴파일하면 arr1은 0x3456, {1, 2, 3, 4, 5}는 0x3456의 주소를 시작으로 연속으로 값을 저장한다.

#### 변수로서의 array

a, b의 int타입 간에는 `a = b;`는 문제가 없었는데, `arr1 = arr2`은 어떨까?

```
int arr1[5] = {1, 2, 3, 4, 5};
int arr2[5] = {6, 7, 8, 9, 0};

arr1 = arr2;
```

그냥 일반적으로 생각하기에 arr1 = {6, 7, 8, 9, 0}이 될 것 같지만 불가능하다. 왜냐하면 C에서는 array 변수는 unmodifiable lvalue로서 일종의 constant variable로 취급하기 때문이다. 즉, array가 정의된 이후로는 `arr1 = xxx;`와 같은 형식으로 array를 수정할 수 없다. arr1을 arr2로 복사하고싶다면, C library의 memcpy, strcpy등을 사용할 수 있다.

제일 처음 `int a = 8` 이라는 문장에서, a는 int형이고 8 역시 int 값이다. 따라서 대입에 문제가 없다. `int *ptr = &a;`의 포인터 또한 마찬가지이다. 포인터 변수를 이용한 dereferencing(`*(&a)`은 a와 같다),  그리고 포인터 연산(*(&arr1[0] + 1)은 arr1[4]와 같다)도 동일하게 적용된다.

arr1 (array 변수)는 컴파일러에 의해 포인터 상수로 취급된다. 따라서 포인터 변수와 같이 포인터 연산도 가능하다. (*(arr + 1)은 arr[1]와 같다) 하지만, 포인터 상수. 즉 포인터 변수가 아니므로 `printf("%p", arr);`와 `printf("%p", &arr)`은 같은 값을 나타낸다. 

#### function parameter로의 array

그럼 array를 함수의 argument로 넘기려면 어떻게 해야할까? array 변수는 포인터 상수로 취급되므로 함수 argument로 반드시 *ptr와 같은 포인터타입이 되어야 할 것 같지만 아래와 같이 작성하여도 컴파일은 가능하다.

```c
...
int main(...) {
	int arr1[5] = {1, 2, 3, 4, 5};
	printf("sizeof arr1 is %lu\n", sizeof(arr1));
	test(arr1);
}
...
void array_test(int arr[]) {
	printf("sizeof arr1 argument is %lu\n", sizeof(arr));
}
```

자 그럼, 위의 코드에서 main함수에서 출력한 arr1의 크기와 array_test에서 출력한 arr2의 크기는 과연 같을까? 결과는 다음과 같다.

sizeof arr1 is 20
sizeof arr1 argument is 8

놀랍게도, 둘의 크기가 다르다. 사실 위의 코드를 gcc 컴파일 시 다음과 같은 메시지를 확인할 수 있다.

```bash
test.c:23:48: warning: sizeof on array function parameter will return size of 'int *' instead of 'int []' [-Wsizeof-array-argument]
	printf("sizeof arr1 argument is %lu\n", sizeof(arr));
```

이유는 array가 함수인자로 사용되면 컴파일러가 array를 포인터로 변경하기 때문이다. 

| 변수 타입 | argument로서의 array |
| int arr[5] | int *arr |
| int arr[5][6] | int (*arr)[6] |
| int arr[5][6][7] | int (*arr)[6][7] |
