# Duck Typing(덕 타이핑)

덕 타이핑(duck typing)은 Dynamic Typing중 하나로, 객체의 변수 및 메소드의 집합이 객체의 타입을 결정하는 것을 말한다. 클래스 상속이나 인터페이스 구현으로 타입을 구분하는 대신, 덕 타이핑은 객체가 어떤 타입에 걸맞은 변수와 메소드를 지니면 객체를 해당 타입에 속하는 것으로 간주한다. 즉, 어떤 행동을 하느냐에 초점을 맞춘다. '덕 타이핑'이라는 용어는 다음과 같이 표현될 수 있는 덕 테스트에서 유래했다. (덕은 실제 오리를 의미한다.)

	만약 어떤 새가 오리처럼 걷고, 헤엄치고, 꽥꽥거린다면 그 새를 오리라고 부를 것이다.

덕 타이핑에서는, 객체의 타입보다 객체가 사용되는 양상이 더 중요하다. 예를 들면, 덕 타이핑이 없는 프로그래밍 언어로는 오리 타입의 객체를 인자로 받아 객체의 걷기 메소드와 꽥꽥거리기 메소드를 차례로 호출하는 함수를 만들 수 있다. 반면에, 같은 함수를 덕 타이핑이 지원되는 언어에서는 인자로 받는 객체의 타입을 검사하지 않도록 만들 수 있다. 걷기 메소드나 꽥꽥거리기 메소드를 호출 할 시점에서 객체에 두 메소드가 없다면 런타임 에러가 발생하고, 두 메소드가 제대로 구현되어 있다면 함수는 정상적으로 작동한다. 여기에는 인자로 받은 객체가 걷기 메소드와 꽥꽥거리기 메소드를 갖고 있다면 객체를 오리 타입으로 간주하겠다는 암시가 깔려있다. 바로 이 점이 앞에서 인용한 덕 테스트의 사상과 일치하기 때문에 덕 타이핑이라는 이름이 붙었다.

이해를 돕기 위해, iterator예제를 살펴보겠다. 먼저 자바의 예제를 보자.

```java
	class Iterable {	
		// ...
		Iterator iterator() {
			// return Iterator
		}
		// ...
	}

	class MyArray extends Iterable {
		// ...
		int size() {
			// return array size
		}

		Object get(int index) {
			// return array[index] object
		}

		Iterator iterator() {
			// return iterator
		}
		// ...
	}

	class MyBinaryTree extends Iterable {
		// ...
		int size() {
			// ...
		}

		Object get(Object key) {
			// ...
		}

		Iterator iterator() {
			// ...
		}
		// ...
	}
```

위의 예제에서는 MyArray 혹은 MyBinaryTree의 어떤 객체이든 동일한 코드로 순회할 수 있다.

```java
	void printAll(Iterable numbers) {
		itr = numbers.iterator();
		// itr을 순회하면서 출력
	}
```

그런데 실제로 상위 클래스인 Iterable에서는 iterator()를 제대로 구현할 수 없다. 따라서 상위 클래스를 만드는 대신 인터페이스를 이용한다.

```java
interface Interable {
	Iterator iterator();
}

class MyArray implements Iterable {
	// ...
	int size() {
		// return array size
	}

	Object get(int index) {
		// return array[index] object
	}

	Iterator iterator() {
		// return iterator
	}
}

class MyBinaryTree implements Iterable {
	// ...
	int size() {
		// ...
	}

	Object get(Obejct key) {
		// ...
	}

	Iterator iterator() {
		// ...
	} 
}
```

위의 예제 역시 마찬가지로 같은 코드로 순회하면서 출력할 수 있다. 이제 새로운 자료구조를 만들고 Iterable을 구현하여 iterator()를 작성한 후 적절한 iterator를 반환하면 된다. implements Iterable을 추가하지 않고 iterator()를 작성하면 해당 인터페이스를 구현한다고 생각하지 않는다.

그럼 Duck Typing은 어떨까? 아래의 파이썬 코드의 예제를 살펴보자

```python
class MyArray(Object):
	def __len__():
		# return array size
	def __getItem(y):
		# return object in index 'y'
	def __iter__():
		# return iter
```

다음과 같이 배열을 순회할 수 있다.

```python
def printAll(numbers):
	itr = numbers.__iter__()
	for x in itr:
		print x
```

단순히 iter()만 구현했음에도 불구하고 순회 가능한 타입으로 사용될 수 있다.
위의 파이썬 코드는 아래와 같이 사용할 수 있다.

```python
def printAll(numbers):
	for x in numbers
		print x
```

덕 타이핑을 이용하면 더 간결하게 코드를 작성할 수 있다. 그러나 파이썬에서의 덕 타이핑은 실행을 해봐야 문제가 발생하는 지 알 수 있다. 즉, numbers로 넘어오는 오브젝트가 iter()을 정의해 두고 있는지 실행해 보기 전까지는 모른다. 즉 런타임에 오류가 발생한다.

반면, 자바에서는 printAll() 메소드가 Iterable을 구현하는 클래스만 받기 때문에, 컴파일 시에 오류가 난다.
