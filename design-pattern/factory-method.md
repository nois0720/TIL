# 팩토리 메소드 패턴

팩토리 메소드 패턴에서는 객체를 생성하기 위한 인터페이스를 정의하고, 어떤 클래스의 인스턴스를 생성할지에 대한 결정은 서브클래스가 하도록 만든다. 이러한 인터페이스를 바탕으로 유연성과 확장성이 뛰어난 코드 제작이 가능해진다.

## 예제

```java
Pizza orderPizza(String type) {
	Pizza pizza;

	if(type.equals("cheese")){
		pizza = new CheesePizza();
	} else if(type.equals("greek")){
		pizza = new GreekPizza();
	} else if(type.equals("pepperoni")){
		new PepperoniPizza();
	} 

	pizza.prepare();
	pizza.bake();
	pizza.cut();
	pizza.box();

	return pizza;
}
```

해당 코드에서, if else 구문으로 이루어진 부분은 요구사항에 따라 추가될 수도 있고 제거될 수도 있다. 때문에 이 부분을 팩토리로 캡슐화한다.

```java
public class SimplePizzaFactory {
	public Pizza createPizza(String type) {
		Pizza pizza = null;
		if(pizza.equals("cheese")) pizza = new CheesePizza();
		if(pizza.equals("pepper")) pizza = new PepperoniPizza();
		if(pizza.equals("clam")) pizza = new ClamPizza();
		if(pizza.equals("veggie")) pizza = new VeggiePizza();
		return pizza;
	}
}

// Simple Factory

public class PizzaStore{
	SimplePizzaFactory simplePizzaFactory;

	public PizzaStore(SimplePizzaFactory simplePizzaFactory) {
		this.simplePizzaFactory = simplePizzaFactory;
	}

	public Pizza orderPizza(String type){
		Pizza pizza;

		pizza = simplePizzaFactory.createPizza(type);

		pizza.prepare();
		pizza.bake();
		pizza.cut();
		pizza.box();
		return pizza;
	}
}
```

이러한 간단한 팩토리가 있다고 하면, orderPizza 메소드로 Pizza 객체 생성을 캡슐화 할 수 있다. 하지만 사업이 확장되어 맥도날드처럼 국가별로 다른 스타일의 피자를 만들어야 한다면 어떻게 될까?

