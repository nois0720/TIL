# Builder

빌더 패턴은 객체의 생성 단계들을 추상화하여 생성 단계의 구현이 달라지면 객체의 다른 표현이 나오도록 하는 데에 그 목적이 있다. 빌더 패턴은 composite 패턴에 따라 제품을 생성하기 위해 사용된다.

즉, 복잡한 객체의 생성을 표현으로부터 분리시켜 같은 생성과정에서 다른 표현을 만들어 낼 수 있게 된다.

![builder](builder.png)

	Builder : 객체(제품)를 생성하는 추상 인터페이스
	Concrete Builder : Builder의 구현 클래스. 다른 객체를 생성할 수 있도록 하는 구체적인 클래스이다. 객체를 만들기 위해 부분을 생성하고 조립한다.
	Director : Director 클래스는 객체 생성의 순서를 다루는 부분에 책임이 있다. 이 클래스는 ConcreteBuilder를 인자로 받아서 필요한 동작을 수행한다.
	Product - Builder를 이용해서 Director가 만들어낸 최종 객체.

## 특징

	* 빌더는 복잡한 객체를 한단계 한단계씩 생성하는데에 초점을 맞춘다. 추상 팩토리는 제품 객체들의 집단(군)을 강조한다.(생성되는 객체가 단일 객체이던지, 복잡한 객체이던지는 상관없다.) 빌더는 제품을 마지막 단계에 반환하지만, 추상 팩토리가 하는 것처럼 제품을 곧바로 얻어낸다.
	* 빌더는 주로 복잡한 객체(Composite)를 생성한다.
	* 종종, 설계는 팩토리 메서드를 사용해서 시작하지만 설계자가 어느 부분에 있어서 더 많은 유연성이 필요하냐를 발견함에 따라 추상 팩토리, 프로토타입 또는 빌더 등으로 발전하게 된다.
	* 가끔 생성 패턴은 상호 보완적이다. : 빌더는 어떤 컴포넌트가 만들어지는지 정하기 위해 다른 패턴들 중 하나를 사용할 수 있다. 추상 팩토리, 빌더, 프로토타입은 싱글톤을 구현에 사용할 수 있다.
	* 빌더는 fluent interface의 좋은 지원자이다.

## 예제 코드

	```cpp
	// Implementation in C++.

#include <iostream>
#include <memory>
#include <string>

	// Product
	class Pizza
{
	private:
		std::string dough;
		std::string sauce;
		std::string topping;

	public:
		Pizza() { }
		~Pizza() { }

		void SetDough(const std::string& d) { dough = d; };
		void SetSauce(const std::string& s) { sauce = s; };
		void SetTopping(const std::string& t) { topping = t; }

		void ShowPizza()
		{
			std::cout << " Yummy !!!" << std::endl
				<< "Pizza with Dough as " << dough
				<< ", Sauce as " << sauce
				<< " and Topping as " << topping
				<< " !!! " << std::endl;
		}
};

// Abstract Builder
class PizzaBuilder
{
	protected:
		std::auto_ptr<Pizza> pizza;
	public:
		PizzaBuilder() {}
		virtual ~PizzaBuilder() {}
		std::auto_ptr<Pizza> GetPizza() { return pizza; }

		void createNewPizzaProduct() { pizza.reset (new Pizza); }

		virtual void buildDough()=0;
		virtual void buildSauce()=0;
		virtual void buildTopping()=0;
};

// ConcreteBuilder
class HawaiianPizzaBuilder : public PizzaBuilder
{
	public:
		HawaiianPizzaBuilder() : PizzaBuilder() {}
		~HawaiianPizzaBuilder(){}

		void buildDough() { pizza->SetDough("cross"); }
		void buildSauce() { pizza->SetSauce("mild"); }
		void buildTopping() { pizza->SetTopping("ham and pineapple"); }
};

// ConcreteBuilder
class SpicyPizzaBuilder : public PizzaBuilder
{
	public:
		SpicyPizzaBuilder() : PizzaBuilder() {}
		~SpicyPizzaBuilder() {}

		void buildDough() { pizza->SetDough("pan baked"); }
		void buildSauce() { pizza->SetSauce("hot"); }
		void buildTopping() { pizza->SetTopping("pepperoni and salami"); }
};

// Director
class Waiter
{
	private:
		PizzaBuilder* pizzaBuilder;
	public:
		Waiter() : pizzaBuilder(NULL) {}
		~Waiter() { }

		void SetPizzaBuilder(PizzaBuilder* b) { pizzaBuilder = b; }
		std::auto_ptr<Pizza> GetPizza() { return pizzaBuilder->GetPizza(); }
		void ConstructPizza()
		{
			pizzaBuilder->createNewPizzaProduct();
			pizzaBuilder->buildDough();
			pizzaBuilder->buildSauce();
			pizzaBuilder->buildTopping();
		}
};

// A customer ordering a pizza.
int main()
{ 
	Waiter waiter;

	HawaiianPizzaBuilder hawaiianPizzaBuilder;
	waiter.SetPizzaBuilder (&hawaiianPizzaBuilder);
	waiter.ConstructPizza();
	std::auto_ptr<Pizza> pizza = waiter.GetPizza();
	pizza->ShowPizza();

	SpicyPizzaBuilder spicyPizzaBuilder;
	waiter.SetPizzaBuilder(&spicyPizzaBuilder);
	waiter.ConstructPizza();
	pizza = waiter.GetPizza();
	pizza->ShowPizza();

	return EXIT_SUCCESS;
}
```

이번에 정리하고자하는 내용은 챕터 2의 2항목인 "생성자의 매개변수가 많을 때는 빌더(builder)를 고려하자"이다.

블로그 작성 목적은 복습과 이 책을 다 읽고자하는 다짐으로 시작한다.



1. 생성자와 Static 팩토리 메소드의 제약

매개변수가 많아질 경우 해당 클래스의 객체를 생성하려면 신축성 있게 처리하지 못한다.



2. 해결방법

가. 텔리스코핑 생성자 패턴

고전적인 방법으로 텔리스코핑 생성자(telescoping constructor) 패턴이 있다.

생성자를 오버로딩하여 사용하는 방법으로 코드로 표현해보면 아래와 같다.



public class Rects {
	private final int width;
	private final int height;
	private final int margin;
	private final int padding;
	public Rects(int width, int height){
		this(width, height, 0, 0);
	}
	public Rects(int width, int height, int margin){
		this(width, height, margin, 0);
	}
	public Rects(int width, int height, int padding){
		this(width, height, 0, padding);
	}
	public Rects(int width, int height, int margin, int padding){
		this.width = width;
		this.height = height;
		/..생략../
	}
}


위 클래스에서 width,height는 필수필드고 margin,padding은 선택필드이나 생성자를 오버로딩하여 작성했고 이 클래스의 객체(인스턴스)를 생성해보면 아래 코드와 같다.



Rects rect = new Rects(200,200,5,0);


텔리스코핑 생성자 패턴에서의 문제점은 객체를 생성하기 위해서 사용하지 않는 선택필드(위에서 padding을 0)의 값도 세팅을 해야만 하며 매개변수의 수가 증가하면 무척 번거로워진다는 것이다.



나. 자바빈즈(JavaBeans) 패턴

이 패턴은 생성자 호출 후 Setter 메소드를 이용하여 각각의 필수&선택 값을 지정한다.

흔히 사용하는 getter setter 클래스라고 생각하면 된다.



public class Rects {
	private final int width = 1;
	private final int height = 1;
	private final int margin = 0;
	private final int padding = 0;
	public Rects(){  }
	public void setWidth(int width){ this.width = width; }
	public void setHeight(int height ){ this.height = height ; }
	public void setMargin(int margin ){ this.margin = margin ; }
	public void setPadding(int padding ){ this.padding = padding ; }
}


위 자바빈즈 패턴 클래스의 객체(인스턴스)를 생성하는 코드는 아래와 같다.

Rects rect = new Rects();
rect.setWidth(200);
rect.setHeight(100);
rect.setMargin(5);


코드가 길어지기는 객체 생성이 간단하며 가독성이 좋다.

하지만 여기서 큰 단점이 있다.

객체 생성 시에 해당 객체가 완전하게 생성됨(책에서는 동결(freezing))을 보장할 수 없다.

예를 들어 Rects클래스의 객체 생성 시 width, height의 필수값이 세팅이 되어야 하지만



Rects rect = new Rects();
rect.setWidth(200);


위와 같이 width값만 생성 후 사용가능하다. 즉 동결시키는 메소드를 객체 사용 전에 호출했는지 컴파일러는 확인할 수 없기 때문이다.



다. 빌더(builder) 패턴

앞서 설명한 텔리스코핑 생성자 패턴과 자바빈즈 패턴을 결합한 빌더(builder) 패턴이 있다.

객체는 필수 매개변수를 갖는 생성자로 얻어낸 후 나머지 선택필드는 setter 메소드로 값을 세팅한다.

그리고 마지막으로 build 메소드를 호출하여 불변 객체를 생성한다.

(불변객체란 객체생성 후 상태가 변하지 않는다.)



	public class Rects {
		private final int width;
		private final int height;
		private final int margin;
		private final int padding;

		public static class Builder {
			private final int width;
			private final int height;
			private int margin;
			private int padding;

			public Builder(int width, int height){
				this.width = width;
				this.height = height;
			}
			public Builder margin(int margin){
				this.margin = margin;
				return this;
			}
			public Builder padding(int padding){
				this.padding = padding;
				return this;
			}
			public Rects build(){
				return new Rects(this);
			}
		}

		public Rects(Builder builder){
			width = builder.width;
			height = builder.height;
			margin = builder.margin;
			padding = builder.padding;
		}
		Builder 클래스의 setter 메소드를 통해 선택필드 값을 세팅하고 생성자에서 Rects 클래스의 생성자를 호출하여 값을 세팅하게 된다.

			해당 클래스의 객체(인스턴스)를 생성하는 코드는 아래와 같다.

			Rects rect = new Rects.Builder(200,100).margin(5).padding(10).build();


		흡사 jquery의 메소드 체이닝 방법과 유사(?!)해 보인다. 위 Builder클래스의 setter 메소드를 보아도 선택필드의 값을 세팅 후 this를 리턴하고 있다. Javascript에서도 이와 같은 방법으로 메소드 체이닝 방법을 구현한다.

			이 패턴의 장점으로는 코드의 작성이 쉽고 가독성이 좋다. 그리고 자바빈즈 패턴의 단점이던 매개변수의 불변규칙을 적용할 수 있다.



			결론

			생성자나 static 팩토리 메소드에서 많은 매개변수를 갖게 되는 클래스를 설계할 때는 필더 패턴이 좋은 선택이다.
