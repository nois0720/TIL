# SOLID - 객체지향 개발 5대 원리

우리들은 모두 어떠한 원리/원칙 아래에서 생활하고 있다. 그럼 우리는 왜 이런 원칙들 아래에서 생활하고 있는 걸까? 완전히 답을 내릴 수는 없지만 아마도 그런 원칙들이 효율적이고 효과적이기 때문일 것이다.

마찬가지로 객체지향 개발에 있어서도 검증된 디자인 원리를 사용하면 좀 더 유연하고 확장이 쉬운 소프트웨어를 만들 수 있다. 이 원리들은 패턴에 비하면 훨씬 그 규모가 작지만, 표준화부터 아키텍쳐 설계에 이르기까지 다양하게 적용되는 원칙이다. 

## 1. SRP (Single Responsibility Principle, 단일 책임의 원칙)

	There should never be more than one reason for a class to change

### 정의

작성된 클래스는 하나의 기능만 가지며, 클래스가 제공하는 모든 서비스는 그 하나의 책임을 수행하는 데 집중되어 있어야 한다는 원칙. 이 말은 어떤 변화에 의해 클래스를 변경해야 하는 이유는 오직 하나뿐이여야 한다는 뜻이다.

SRP principle을 적용하면 책임 영역이 확실해지기 때문에 하나의 responsibility변경에서 다른 responsibility 변경으로의 연쇄작용에서 자유로워진다. 또한 책임을 적절하게 분배하여 코드의 가독성이 향상되고, 유지보수가 용이해지며 뒤에서 소개할 다른 원리들을 적용하는 기초가 된다.

이 원리는 다른 원리들에 비해 개념은 단순하지만 실제로 적용해서 클래스를 설계하는것은 쉽지 않다.

### 적용 방법

책 리팩토링(Refactoring)에서 소개하는 대부분의 위험상황에 대한 해결방법은 직/간접적으로 SRP원리와 관련이 있으며, 이는 항상 코드를 최상으로 유지한다는 리팩토링의 근본정신도 항상 객체들의 책임을 최상의 상태로 분배한다는 것에서 비롯되기 때문이다.

* 여러 원인에 의한 변경 (Divergent change): Extract Class를 통해 혼재된 각 책임을 각각의 개별 클래스로 분할하여 클래스당 하나의 책임만을 맡도록 하는 것이다. 이 방법에서 가장 중요한 점은 책임만 분리하는 것이 아니라 분리된 두 클래스간의 관계의 복잡도를 줄이도록 설계하는 것이다. 만약 Extract Class된 각각의 클래스들이 유사하고 비슷한 책임을 중복해서 갖고 있다면 Extract Superclass를 사용할 수 있다. 이것은 Extract된 각각의 클래스들의 공유되는 요소를 부모 클래스로 정의하여 부모 클래스에 위임하는 기법이다. 따라서 각각의 Extract Class들의 유사한 책임들은 부모에게 명백히 위임하고 다른 책임들은 각자에게 정의할 수 있다.

* 산탄총 수술(Shotgun surgery): Move Field와 Move Method를 통해 책임을 기존의 어떤 클래스로 모으거나, 적당한 클래스가 없다면 새로운 클래스를 만들어 해결할 수 있다. 즉 산발적으로 여러 곳에 분포된 책임들을 한 곳에 모으면서 설계를 명확하게 한다. 한마디로 Cohesion(응집성)을 높이는 작업이다.

### 적용 사례

```java
// before apply SRP
class Guitar() {
	public Guitar(String serialNumber, double price, Maker maker, Type type, String model, Wood backWood, Wood topWood, int stringNum){
		this.serialNumber = serialNumber;
		this.price = price;
		this.maker = maker;
		this.type = type;
		this.model = model;
		this.backWood = backWood;
		this.topWood = topWood;
		this.stringNum = stringNum;
	}

	private String serialNumber;
	private double price;
	private Maker maker;
	private Type type;
	private String model;
	private Wood topWood;
	private Wood backWood;
	private int stringNum;

	//...
}
```

위의 자바코드를 보자. serialNumber의 경우, 한 번 정해지면 바뀌지 않는 고유번호이다. 반면, price, maker, type.. 등은 모두 변경이 발생할 수 있는 부분이다. 따라서 특정 정보에 변화가 발생하면, 항상 해당 클래스를 수정해야하는 부담이 발생한다. 따라서 이 부분은 SRP를 적용할 수 있는 대상이라고 할 수 있다.

다음 자바 코드는 SRP를 적용하여, 특성에 대한 변경이 일어나면 GuitarSpec클래스만 변경하면 된다. 보기에도 좋고 변화에 의해 변경되는 부분을 한 곳에서 관리할 수 있게 되었다.

```java
class Guitar() {
	public Guitar(String serialNumber, GuitarSpec spec){
		this.serialNumber = serialNumber;
		this.spec = spec;
	}
	
	private STring serialNumber;
	private GuitarSpec spec;

	//...
}

class GuitarSpec(){
	double price;
	Maker maker;
	Type type;
	String model;

	//...
}
```

### 적용 이슈

클래스는 클래스 자신의 이름에 해당하는 일을 해야 한다. 잘 지은 이름은 해당 클래스가 어떤 책임을 지고 있는지 알 수 있는 가장 좋은 방법 중 하나이다. 각각의 클래스는 하나의 개념을 나타내어야 한다. 사용되지 않는 속성이 있다면, 그것은 하나의 개념을 나타내지 않는다는 증거가 될 수 있다. 

무조건 책임을 분리한다고 해서 SRP를 적용한다고는 할 수 없다. 각 개체간 Cohesion이 있다면 개체간 병합이 오히려 바람직한 경우도 있다. (Coupling이 있다면 분리가 바람직하다.)

## 2. OCP (Open Close Principle, 개방폐쇄의 원칙)

	You Should be able to extend a classes behavior, without modifying it

### 정의

버틀란트 메이어(bertrand Meyer)박사가 1998년 객체지향 소프트웨어 설계라는 책에서 정의한 내용으로, 소프트웨어의 구성 요소(Component, Class, Module, Funcion)의 확장에는 열려있고, 변경에는 닫혀있어야 한다는 원리이다. 즉, 변경을 위한 비용은 최소화하고 확장을 위한 비용은 극대화해야 한다는 의미로서, 요구사항에 대한 변경이나 추가사항이 발생하더라도, 기존의 구성요소에 수정이 일어나지 않도록 해야하며, 기존 구성요소를 쉽게 확장해서 재사용할 수 있어야 한다는 뜻이다. 로버트 C. 마틴은 OCP는 관리가 가능하고 재사용 가능한 코드를 만드는 기반이며, OCP를 가능하게 하는 중요 메커니즘은 추상화와 다형성이라고 말한다. 따라서, OCP는 객체지향의 장점을 극대화하는 중요한 원리라고 할 수 있다.

### 적용 방법

1. 변경될 것과 변경되지 않을 것을 구분한다.
2. 이 두 모듈이 만나는 지점에 인터페이스를 정의한다.
3. 구현에 의존하지 않고, 정의한 인터페이스에 의존하도록 코드를 짠다.

### 적용사례
```java
class Guitar() {
	public Guitar(String serialNumber, GuitarSpec spec){
		this.serialNumber = serialNumber;
		this.spec = spec;
	}

    private STring serialNumber;
	private GuitarSpec spec;
			    
	public String getSerialNumber(){
		//...
	}
}
					  
class GuitarSpec(){
	double price;			
	Maker maker;						       
	Type type;			
	String model;	
	//...		
}
```

이 코드는 SRP를 설명할 때 사용했던 코드이다. 겉으로 보기에는 큰 문제가 없어 보인다. SRP원리를 적용하여 Guitar에서 변경이 예상되는 부분들을 GuitarSpec이라는 새로운 클래스를 만들어 한 군데로 모았기 때문이다. 하지만, 여기에서도 변경이 발생될 수가 있다. 예를 들어, Guitar외에 Violin, Cello와 같은 다른 악기들을 다루게 된다면 어떻게 해야 할까?

```java
class Violin(){
	public Violin(String serialNumber, ViolinSpec spec) {
		this.serialNumber = serialNumber;
		this.spec = spec;
	}

	private ViolinSpec spec;
}

class ViolinSpec(){
	//...
}
```

OCP를 적용하지 않으면, 위의 코드처럼 매번 새로운 악기가 필요할 때마다 이러한 코드를 생성해야 할 것이다.

변화 자체를 막을 수는 없다. 그래서 우리는 변화에 대응해야한다. OCP를 적용시켜 이런 변화에 대응해보자.

먼저, Guitar를 포함해서 추가될 악기를 추상화 해야한다. 추가될 악기들의 공통 속성을 모두 담을수 있는 InstrumentAttribute라는 인터페이스를 만들어 보자. InstrumentAttribute는
