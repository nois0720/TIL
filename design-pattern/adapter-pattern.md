# Adapter Pattern

어댑터 패턴 개념은 일상에서도 자주 볼 수 있다.

![Adapter_1](/image/adapter_1.jpg)

	US의laptop이 요구하는 인터페이스(직류 12V)와, 유럽에서 사용하는 플러그의 인터페이스가 다르므로, 어댑터를 이용하는 것을 볼 수 있다.

어댑터 패턴도 이와 마찬가지이다.

![Adapter_2](/image/adapter_2.jpg)

어댑터 패턴(Adapter pattern)은 클래스의 인터페이스를 사용자가 기대하는 다른 인터페이스로 변환하는 패턴이다. 즉, 어댑터를 이용하여 호환성이 없는 인터페이스 때문에 함께 동작할 수 없는 클래스들이 함께 작동하도록 할 수 있다.

따라서 클라이언트와 구현된 인터페이스를 분리시킬 수 있고, 향후 인터페이스가 변경되더라도 그 변경 내역은 어댑터에 캡슐화 되기 때문에 클라이언트는 변경이 필요 없다. 다음은 어댑터 패턴 클래스 다이어그램이다.

![class-diagram](/image/Adapter_pattern_cd.png)

클래스 다이어그램에 보면, Target(타겟)과 Adaptee(어댑티)라는 용어가 등장하는데, 먼저 이를 설명하고 넘어가려고 한다.

* Client : Target의 메소드를 이용해서 일을 수행한다. (노트북에 해당한다.)
* Target : 지금 필요한 메소드를 결정한다. (노트북을 작동시키기 위한 직류 12V에 해당한다.)
* Adaptee : 단어의 뜻 그대로, Adaptee(Adapt되는 쪽)이다. 즉, 이미 준비되어 있는 메소드를 가지고 있다. (유럽의 AC전원에 해당한다) 
* Adapter : Adaptee 역할의 메소드를 잘 변환시켜 Target이 사용할 수 있도록 만드는 역할을 한다.

이해를 돕기 위해서 코드를 보자.

```java
public interface Duck {
	public void quack();
	public void fly();
}

public class MallardDuck implement Duck {
	@Override
	public void quack() {
		System.out.println("Quack");
	}

	@Override
	public void fly() {
		System.out.println("I'm flying");
	}
}

public interface Turkey {
	public void gobble();
	public void fly();
}

public class WildTurkey implements Turkey{
	@Override
	public void gobble() {
		System.out.println("Gobble gobble");
	}

	@Override
	public void fly() {
		System.out.println("I'm flying short distance");
	}
}
```

만약에, Turkey 객체를 Duck객체로 대신 사용해야 하는 상황이라고 가정하자.

하지만 두 클래스가 구현하는 인터페이스가 다르기 때문에 Turkey 객체를 바로 Duck처럼 사용할 수 없다. 이러한 경우 어댑터를 만든다.

```java
public class TurkeyAdapter implements Duck {
	Turkey turkey

	public TurkeyAdapter(Turkey turkey) {
		this.turkey = turkey;
	}

	@Override
	public void quack() {
		turkey.gobble();
	}

	@Override
	public void fly() {
		turkey.fly();
	}
}
```

그럼 이제 신나게 테스트를 해보자!

```java
public class DuckTest {
	public static void main(String[] args){
		MallardDuck duck = new MallardDuck();

		WildTurkey turkey = new WileTurkey();
		Duck turkeyAdapter = new TurkeyAdapter(turkey);

		System.out.println("The turkey says..");
		turkey.gobble();
		turkey.fly();
		// "Gobble gobble"
		// "I'm flying short distance"

		System.out.println("The Duck says...");
		testDuck(duck);
		// "Quack"
		// "I'm flying"

		System.out.println("The TurkeyAdapter says...");
		testDuck(turkeyAdapter);
		// "Gobble gobble"
		// "I'm flying short distance"
	}

	public static void testDuck(Duck duck){
		duck.quack();
		duck.fly();
	}
}
```

## 어댑터의 종류

어댑터는 객체 어댑터와 클래스 어댑터의 두 종류로 나뉜다.

클래스 어댑터 패턴을 쓰려면 다중 상속이 필요한데, 자바에서는 다중 상속이 불가능하다. 그래서 이 경우 extends와 implements를 동시에 사용함으로서 이를 구현한다. 두 어댑터 클래스 다이어 그램을 보면 이해가 수월하다.

1. 객체 어댑터
* composition을 사용한다
* Adaptee뿐만 아니라 해당 서브 클래스에 대해서도 어댑터 역할을 할 수 있다는 장점이 있다.

![object_adapter](/image/object-adapter.png)

Adapter는 Target에게서만 상속을 받고, Adaptee는 객체 참조만 한다.

