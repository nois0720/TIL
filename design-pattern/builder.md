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
