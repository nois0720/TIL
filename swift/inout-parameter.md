# inout 파라미터

기본적으로, 함수의 파라미터로 값을 전달할 때에는 보통 call by value로 전달된다. 하지만, value가 아닌 reference로 전달하기 위해서는 inout parameter를 사용한다. 이는 C의 포인터와 유사하다.

아래의 예제를 보자

```swift
func refSwap(inout a: Int, inout b: Int) {
	let temp = a;
	a = b;
	b = temp;
}

var value1 = 3;
var value2 = 4;

refSwap(&value1, &value2);
print(value1);
print(value2);
```

실행 시켜보면 바뀌어있는 value1, 2를 확인할 수 있다.

