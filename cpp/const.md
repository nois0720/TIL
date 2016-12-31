# const 위치에 따른 구문의 의미.

보통 const는 상수 특성을 지정하는 키워드로 알고 있으나 놓인 위치에 따라 약간의 미묘한 의미 차이를 갖는다. 하지만 const가 붙으면 값 변경이 되지 않는다는 원칙은 변하지 않는다.

그럼 const의 위치에 따라 누구의 값이 변경되지 않는가를 찾는 것이 관건이 된다. 아래의 3 가지 예를 보도록 하자.

```cpp
const int **a;	// 1
int* const *a;	// 2
int** const a;	// 3
```

이렇게 3 가지의 자료형이 있다고 하자. const가 붙는 위치가 조금씩 다른데, 이는 사실 다음과 같다.

```cpp
(const int) **a;	// 1
(int* const) *a;	// 2
(int **) const a;	// 3
```

1 번은 const int형에 대한 이중 포인터이다. 즉, int형 상수에 대한 이중 포인터이다.

const int **a라고 선언하였을 때, a는 const int**형이므로 const int**형으로 값 변경이 가능하다. a* 역시 const int*형으로 값 변경이 가능하다. 하지만 **a는 const int형이므로 값 변경이 불가능하다. 아래는 실제 코드이며, **a에 값을 대입하려고 하면 컴파일 에러가 발생함을 확인할 수 있다.

![first-example](/image/const_1)

2번은 int*형이 갖는 주소 값을 상수로 정했다. 즉, int형 상수에 대한 포인터이다.

int* const *a를 선언하였을 때, a는 int* const*형이므로 값 변경이 가능하다. 하지만 *a는 int* const형이므로 값 변경이 불가능하다. 그리고 **a의 경우 int형으로 값 변경이 가능하다.

![first-example](/image/const_2)
