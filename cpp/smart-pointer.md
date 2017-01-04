# Smart Pointer

[http://ootips.org/yonat/4dev/smart-pointers.html](http://ootips.org/yonat/4dev/smart-pointers.html)

글을 시작하기에 앞서, 이 문서에는 스마트 포인터에 대한 설명 및 장점. 왜 사용해야 하는가에 대한 설명이 자세히 되어 있다. 하지만 문서에 등장하는 예들은 모두 문서를 작성한 분이 직접 개발한 라이브러리로 cpp 표준도 아니고 직접 사용하기엔 애매한 부분이 있으니 이 부분은 가려서 보도록 하자.

## 스마트 포인터란 도대체 뭘까?

그냥 이름으로 추측해보자면 똑똑한 포인터인데 그럼 어디가 어떻게 똑똑하다는 것일까? 스마트 포인터는 마치 포인터처럼 사용된다. 즉 포인터의 인터페이스라고 할 수 있는 '*' operator와 '->' operator를 똑같이 지원한다. 이처럼 실제로 서로 다른 무언가를 동일하게 보이게 하는 객체를 디자인패턴에서는 Proxy객체 혹은 Proxy라고 부른다. Proxy패턴에 대해서는 빠른 시일 내에 문서를 정리해봐야겠다.

그럼 똑같은부분은 됐고 뭐가 다른데? 라는 생각이 스쳐지나간다. cpp에서 가장 많이 발생하는 버그 중 하나는 포인터와 포인터의 메모리에 대한 부분이다. dangling pointer, 메모리 누수, 할당 실패 등이다. 이것들을 스마트 포인터를 이용하여 줄일 수 있다.

스마트 포인터의 가장 대표격인 std::auto_ptr을 살펴보자. std::auto_ptr은 cpp standard library에 포함되어 있다. 실제 헤더파일에서 구현부를 살펴보면 다음과 같다.

```cpp
template <class T> class auto_ptr
{
	T* ptr;

public:
	explicit auto_ptr(T* p = 0) : ptr(p) { }
	~auto_ptr()	{ delete ptr; }
	T& operator*()	{ return *ptr; }
	T* operator->()	{ return ptr; }
	// ...
};
```

auto_ptr은 일반 포인터를 래핑하는 단순한 클래스이다. 스마트 포인터의 가장 큰 장점은 소멸자로부터 나온다. 소멸자는 포인터를 delete하는 역할을 담당한다. 포인터를 사용하는 경우 반드시 명시적으로 프로그래머가 delete를 해주어야 하지만 auto_ptr을 사용한다면 delete를 명시적으로 호출할 필요가 없게된다.

```cpp
void pointerExam()
{
	TestClass* p(new TestClass);
	p->Do();
	delete p; // 명시적으로 delete하여 메모리 해제를 해야함.
}

void smartPointerExam()
{
	auto_ptr<TestClass> p(new TestClass);
	p->Do();
	// 명시적으로 delete 호출하지 않음.
}
```

## 그럼 왜 사용할까?

위에서 코드로 살펴보았듯이 스마트 포인터는 여러 방법으로 구현할 수 있으며 이에 따라 용도가 조금씩 다를 수 있다. 하지만 공통적으로 다음과 같은 장점이 있다.

* 메모리 해제를 알아서 해준다.
* NULL로 초기화 할 필요가 없다.
* 때문에 버그가 적게 발생한다.

포인터를 사용하면서 가장 자주 겪는 실수는 Dangling 포인터이다. 이미 삭제된 객체를 가리키고 있는 포인터를 의미하는데, 코드를 보도록 하자.

```cpp
 void DanglingExam()
{
	TestClass* p1(new TestClass);
	TestClass* p2 = p1;
	
	delete p1;

	p->Do(); // p는 dangling이다.
	p = NULL; // 이제 p는 dangling이 아님.
	q->Do(); // q는 여전히 dangling.
}
```

하지만 auto_ptr는 복사되는 경우 자동으로 NULL로 설정하도록 구현되어있다.

```cpp
template <class T>
auto_ptr<t>& auto_ptr<T>::operator=(auto_ptr<T>& rhs)
{
	if(this != &rhs) {
		delete ptr;
		ptr = rhs.ptr;
		rhs.ptr = NULL;
	}
	return *this;
}
```

auto_ptr이 위와 같이 구현하였지만, 다른 스마트 포인터는 다르게 구현하였을 수도 있다. 예를 들자면 다른 스마트 포인터에서 q = p를 수행한다고 했을때 p, q가 동일한 스마트 포인터일 경우 아래와 같은 방법으로 구현할 수도 있다.

* 새로운 copy를 생성한다
* 소유권을 이전한다.
* Reference Counting
* Reference Linking
* COW (Copy on Write)

위의 방법은 dangling 포인터로 생기는 문제를 해소하는 데 도움이 된다. 각각의 장단점이 분명하기 때문에 상황에 맞게 구현할 필요가 있겠다. 내일은 이러한 방법의 장단점을 알아보자. 
