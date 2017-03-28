# This Pointer

This Pointer란 객체가 멤버함수를 호출할 때, 자동으로 멤버함수에게 전달되는 포인터로, 호출한 객체를 가리키는 포인터를 말한다.

흔히 자기 참조 포인터라고 불리우며, 멤버 함수에게만 this pointer가 전달된다.(Friend 함수는 멤버 함수가 아니므로, this pointer가 전달되지 않는다. static함수도 마찬가지이다.)

예제를 보자

```cpp
#include <iostream>
using namespace std;

class Person
{
public:
	Person* GetThis() {
		return this; // this 포인터 리턴.
	}
}

int main()
{
	Person *p1 = new Person();
	cout<<"pointer p1 : "<<p1<<endl;	// pointer p1 : 007D7760
	cout<<"p1's this : "<<p1->GetThis()<<endl<<endl;	// p1's this : 007D7760

	Person *p2 = new Person();
	cout<<"pointer p2 : "<<p2<<endl; // 007D7790
	cout<<"p2's this : "<<p2->GetThis()<<endl; 007D7790

	return 0;
}
```

결과를 보면 알 수 있듯, This 포인터는 멤버 함수를 소유한 객체를 가리키고 있다. 다시 말해서 멤버 함수를 호출할 때 사용한 객체를 가리키고 있다. 그럼 이런 this pointer의 타입은 어떻게 되는것일까? 일단 객체를 가리키는 것이므로 Person 클래스의 포인터 타입이 여기서 this의 리턴 타입이라고 할 수 있다.(Person* 타입)

# Frined

일반적으로, 클래스의 private멤버는 외부에서 접근할 수 없다. private변수 및 함수는 멤버 함수에서만 접근이 가능하다. 그런데, 멤버함수가 아닌 외부에서 접근해야할 경우가 발생할 수 있다. 그래서 friend문법이 등장하게 되었다. 이 경우 클래스에서 friend함수로 선언해 주면 외부함수이면서 클래스의 비공개 멤버에 접근할 수 있는 권한을 가지게 된다.
