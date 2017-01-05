# Smart Pointer

[http://ootips.org/yonat/4dev/smart-pointers.html](http://ootips.org/yonat/4dev/smart-pointers.html)

글을 시작하기에 앞서, 이 문서에는 스마트 포인터에 대한 설명 및 장점. 왜 사용해야 하는가에 대한 설명이 자세히 되어 있다. 하지만 문서에 등장하는 예들은 모두 문서를 작성한 분이 직접 개발한 라이브러리로 cpp 표준도 아니고 직접 사용하기엔 애매한 부분이 있으니 이 부분은 가려서 보도록 하자.

## 목차
* [스마트 포인터란?](https://github.com/nois0720/TIL/blob/master/cpp/smart-pointer.md#스마트-포인터란-도대체-뭘까)
* [왜 사용하는가?](https://github.com/nois0720/TIL/blob/master/cpp/smart-pointer.md#왜-사용하는가?)
* [장점](https://github.com/nois0720/TIL/blob/master/cpp/smart-pointer.md#장점)

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

* 새로운 copy를 생성한다 - p가 가리키는 객체의 복사본을 새로 생성하여 q가 가리키도록 하는 전략
* 소유권을 이전한다 - p와 q가 동일한 객체를 가리키도록 한다. 그러나 해제에 대한 쇼유권을 p에서 q로 이전한다.
* Reference Counting - 동일한 객체를 가리키는 스마트 포인터의 갯수를 유지하는 전략으로, 이 값이 0이 되는 순간 객체를 삭제한다. 이 방법을 통해 q = p문을 실행시키면 p가 가리키는 객체의 카운트 값을 1 증가시킨다.
* Reference Linking - 위의 방식과 비슷하지만 count를 사용하지 않고 객체를 가리키는 스마트포인터들을 circular doubly linked list로 연결한다.
* COW (Copy on Write) - Reference Counting, Reference Linking은 모두 객체가 수정되지 않는 동안 사용된다. 반면 이 방식은 수정이 필요하면 새로운 복사본을 생성한 후 수정하는 방식이다.

위의 방법은 dangling 포인터로 생기는 문제를 해소하는 데 도움이 된다. 각각의 장단점이 분명하기 때문에 상황에 맞게 구현할 필요가 있겠다. 

## 장점

#### 메모리 관리

다음의 예를 살펴보자

```cpp
void test()
{	
	TestClass* p(new TestClass);
	p->Do();
	delete p;
}	
```

이러한 코드가 있다고 하자. 만약 p->Do()에서 Exception이 발생될 경우 어떻게 될까? 이 경우 p->Do() 이후에 있는 코드들은 수행되지 않으므로 바로 아래에 있는 delete p;는 호출되지 않는다. 즉 메모리 누수가 발생하며 TestClass의 소멸자가 호출되지 않는다.

하지만 스마트 포인터를 사용하는 경우 p의 Scope를 벗어나는 경우 자동으로 소멸자가 호출된다. 정상적으로 종료될 때 뿐만 아니라 Exception이 발생하여도 소멸자가 항상 호출되므로 위에서의 문제를 해결할 수 있다.

아래 코드처럼 스마트 포인터를 사용하지 않아도 안전하게 코드를 작성할 수 있지만 그냥 스마트 포인터를 사용하면 된다. 또한 코드가 간결해진다는 장점도 챙길 수 있다.

```cpp
void test()
{
	TestClass* p;
	try {
		p = new TestClass;
		p->Do();
		delete p;
	}
	catch(...) {
		delete p;
		throw;
	}
}
``` 

많은 언어들은 GC(Garbage Collection) 기능을 제공하지만 cpp는 제공하지 않는다. 스마트 포인터는 이런 면에서 GC의 역할을 어느정도 수행한다고 볼 수 있다.

가장 단순한 GC기법은 Reference counting이나 Reference Linking이다. 스마트 포인터를 이용하는 경우 이러한 GC를 좀 더 정교하게 이용할 수 있다.

#### 효율성

스마트 포인터는 사용 가능한 메모리를 좀 더 효율적으로 사용할 수 있게 하고 또한 메모리 allocation, free시간을 단축시킨다.

메모리를 좀 더 효율적으로 사용할 수 있는 방법에는 COW(Copy on Write)가 있다. 즉, 하나의 객체가 수정되지 않는 동안 COW포인터가 해당 객체를 가리킬 수 있도록 하고, 해당 객체가 수정되는 경우(write하는 경우) COW포인터가 객체를 카피(Copy)한 후에 복사본을 수정한다. 일반적으로 standard string 클래스 역시 COW방법을 사용하여 구현한다.

```cpp
string str("hello");

string str2 = str;
str2 += " Ryan~";
```

객체가 할당되거나 사용되는 환경에 대해 추측이 어느정도 가능하다면 최적화된 할당 계획이 가능하다. 예를 들어, 모든 객체의 크기가 동일하다거나 단일 쓰레드에서만 사용될 수 있다는 등의 가정이 있겠다. 이런 경우, 클래스에 특화된 new, delete 연산자를 이용하여 최적화된 할당 계획을 세울 수 있다.

하지만 스마트 포인터를 사용하면 이런 가정 자체를 무시할 수 있다. 따라서 서로 다른 환경이나 프로그램이 변경되더라도 클래스 전체 코드를 변경하지 않고 항상 최적의 할당계획을 만들 수 있다.

내일은 이러한 스마트 포인터를 어디에 사용하면 좋을지 고민.
