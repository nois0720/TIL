# Boxing과 Unboxing

boxing은 value타입을 object타입 또는 이 value타입에서 구현된 임의의 인터페이스 형식으로 변환하는 프로세스이다. C#에서 CLR은 value타입을 boxing할 때 값을 System.Object 내부에 래핑하고 managed heap에 저장한다. 반면 unboxing하면 개체에서 value타입이 추출된다. 

```csharp
int i = 123;	// i는 value type
Object o = i;	// boxing
int j = (int)o;	// unboxing
```

## Boxing
위의 예제를 보았을 때, 문제가 있다고 할 수 있을까? 프로그래밍을 하다보면 value타입을 object타입으로 형변환을 할 때가 많다. 근데 이게 왜 문제가 될까?

