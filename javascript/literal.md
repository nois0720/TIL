# literal

리터럴이란, 소스 코드의 고정된 값을 대표하는 용어로, 고정된 값을 가질 수 있는 변수나 변경되지 않는 상수가 있다.

## 객체 리터럴

자바스크립트에서 객체라고 하면 단순히 name-value pair의 해시 테이블을 생각하면 된다. 여기서 value는 primitive type과 object 모두 가능하다. 자바스크립트에서는 함수 역시 객체이므로 역시 value에 해당될 수 있다.

자바스크립트에서 생성한 객체는 언제라도 변경할 수 있으며, 내장 네이티브 객체의 프로퍼티들 역시 대부분 변경이 가능하다. 또한 빈 객체를 정의해놓고 기능을 추가해나갈 수도 있다. 객체 리터럴 표기법은 이처럼 필요에 따라 객체를 생성할 때 이상적이다.

```javascript
var dog = {};

dog.name = "navi";

dog.getName = function() {
	return dog.name;
};
```

이 예제는 빈 객체에서 프로퍼티와 메서드를 추가하는 예제이다. 프로그램의 생명주기 중 어느 때라도 다음과 같은 일을 할 수 있다.

* 프로퍼티와 메서드 값을 변경할 수 있다.
```javascript
dog.getName = function() {
	return "Fido";
}
```

* 프로퍼티나 메서드를 완전히 삭제한다.
```javascript
	delete dog.name;
```

* 다른 프로퍼티나 메서드를 추가한다.
```javascript
	dog.say = function() {
		return "Woof!";
	};
	dog.fleas = true;
```

이러한 일들은 반드시 빈 객체를 생성한 후에 시작해야 하는 것은 아니다. 객체 리터럴 표기법을 쓰면 다음 예제처럼 생성 시점에 객체에 기능을 추가할 수 있다.
```javascript
var dog = {
	name: "Benji",
	getName: function() {
		return this.name;
	}
}
```

## 생성자 함수로 객체 생성하기

자바스크립트에는 클래스가 없다. 그러나 자바스크립트에도 클래스 기반 객체 생성과 비슷한 문법을 가지는 생성자 함수가 존재한다. 객체를 생성할 때에는 직접 만든 생성자 함수를 사용할 수도 있고, Object(), Date(), String()등 내장 생성자를 사용할 수도 있다.

다음 예제는 동일한 객체를 생성하는 두 가지 방법을 보여준다.
```javascript
// 리터럴 사용
var car = {goes: "far"};
```

```javascript
// 내장 생성자 Object() 사용
var car = new Object();
car.goes = "far";
```

위의 예제 코드에서도 확인할 수 있듯이 객체 리터럴 표기법의 명백한 이점은 더 짧다는 것이다. 또한 클래스로부터 객체를 instanciate하지 않아도 되는 것임을 보여준다. 이 역시 리터럴로 객체를 생성하는 패턴의 장점 중 하나이다.

리터럴 표기법을 사용하면 유효범위 판별 작업도 발생하지 않는다. 생성자 함수를 사용했다면 유효범위에 동일한 이름의 생성자가 있을 수 있기 때문에 Object()를 호출한 위치에서 전역 Object 생성자에 이르기까지 인터프리터는 이를 거슬러 올라가며 검색해야한다.

## 객체 생성자의 함정

객체 리터럴을 사용할 수 있는 상황에서는 new Object() 생성자를 쓸 이유가 없다. 하지만 Legacy code를 물려받을 수도 있기 때문에 이 생성자의 기능 하나를 알아둘 필요가 있다. (하지만 이것은 결국 생성자를 써서는 안되는 이유가 되기도 한다.)

문제의 기능은 Object() 생성자가 파라미터를 받을 수 있다는 점이다. 파라미터로 전달되는 값에 따라 생성자 함수가 다른 내장 생성자에 객체 생성을 위임할 수도 있고, 기대한 것과는 다른 객체가 반환되기도 한다.

다음은 new Object()에 숫자, 문자열, boolean값을 전달한 몇 가지 예이다. 예상한 바와 다른 생성자로 생성된 객체가 반환된다.

```javascript
// 모두 안티패턴이다!

// 빈 객체
var o = new Object();
console.log(o.constructor === Object); // true

// number 객체
var o = new Object(1);
console.log(o.constructor === Number); // true
console.log(o.toFixed(2)); // "1.00"

// string 객체
var o = new Object("I am a string");
console.log(o.constructor === String); // true
// 일반적인 객체에는 substring()이라는 메서드가 없지만 문자열 객체에는 존재한다.
console.log(typeof o.substring); // "function"

// boolean 객체
var o = new Object(true);
console.log(o.constructor === Boolean); // true
```

Object() 생성자의 이 같은 동작 방식 때문에, 런타임에 결정하는 동적인 값이 생성자의 인자로 전달될 경우, 예기치 않은 결과가 반환될 수 있다. 결론적으로 new Object를 사용하지 말고 더 간단하면서 안정적인 객체 리터럴을 사용하자.

## 사용자 정의 생성자 함수
객체 리터럴 패턴이나 내장 생성자 함수를 쓰지 않고, 직접 생성자 함수를 만들어 객체를 생성할 수도 있다.

```javascript
var john = new Person("john");
john.say(); // "I am john"
```

이 패턴은 마치 Person이라는 클래스를 이용하여 객체를 생성하는 것 처럼 보인다. 그러나 문법은 비슷해도 자바스크립트에선 클래스가 없으며 Person은 그저 일반적인 함수일 뿐이다.

다음은 Person 생성자 함수를 정의한 예이다.
```javascript
var Person = function(name) {
	this.name = name;
	this.say = function() {
		return "I am " + this.name;
	};
};
```

new와 함께 생성자 함수를 호출하면 함수 안에서 다음과 같은 일이 일어난다.

* 빈 객체가 생성된다. 이 객체는 'this'로 참조할 수 있고 해당 함수의 프로토타입을 상속받는다.
* this로 참조되는 객체에 프로퍼티와 메서드가 추가된다.
* 마지막에 다른 객체가 명시적으로 반환되지 않으면, this로 참조된 이 객체가 반환된다.

즉 이면에서는 다음과 같이 진행된다고 할 수 있다.

```javascript
var Person = function (name) {
	// 객체 리터럴로 새로운 객체 생성.
	// var this = {};
	
	// 프로퍼티와 메서드를 추가한다.
	this.name = name;
	this.say = function() {
 		return "I am " + this.name;
	};
}
```

이 예제에서는 간단히 say()라는 메서드를 this에 추가했다. 결과적으로 new Person()을 호출할 때마다 메모리에 새로운 함수가 생성된다. say()라는 메서드는 인스턴스별로 달라지지 않으므로 이런 방식 보다는 Person의 프로토타입에 추가하는 것이 낫다.

```javascript
Person.prototype.say = function(){
	return "I am " + this.name;
}
```

이 내용은 프로토타입에 대한 내용을 따로 다룰때 더 자세히 작성하고, 여기서는 메서드와 같이 재사용되는 멤버를 프로토타입에 추가한다는 점만 작성한다. 다음으로 넘어가기 전에, 다시 언급하자면 생성자 내부에서는 다음과 같은 일이 벌어진다.

```javascript
	//var this = {};
```

이것이 다가 아니라, 사실 '빈'객체라는 것은 사실 텅 빈것이 아니라 Person프로토타입을 상속받는다. 즉 다음 코드와 더 가깝다.

```javascript
	//var this = Object.create(Person.prototype);
```

## 생성자의 반환 값

생성자 함수를 new와 함께 호출하면 항상 객체가 반환된다. 기본값은 this로 참조되는 객체이다. 생성자 함수 내에서 아무런 프로퍼티나 메서드를 추가하지 않았다면 빈 객체가 반환될 것이다.

함수 내에 return문을 쓰지 않았더라도 생성자는 암묵적으로 this를 반환한다. 그러나 반환 값이 될 객체를 따로 정할 수도 있다. 다음 예제에서는 새로운 객체를 생성하여 that으로 참조하고 반환하는 것을 볼 수 있다.

```javascript
var Objectmaker = function() {		
	// 생성자가 다른 객체를 대신 반환하기로 결정하였다
	this.name = "This is it";
	// 이 name 프로퍼티는 무시된다.

	// 새로운 객체를 생성하여 반환한다.
	var that = {};
	that.name = "And that's that";
	return that;
};

//테스트
var o = new Objectmaker();
console.log(o.name); // "And that's that"
```

이와 같이 생성자에서는 어떤 객체라도 반환할 수 있다. (객체이기만 하다면..) 객체가 아닌 것을 반환하려고 시도하면(예를 들면 string, number 등) 에러가 발생하지는 않지만 무시되고 this에 의해 참조된 객체가 대신 반환된다!

## 'new'를 강제하는 패턴

앞에서 언급했듯이 생성자란 new와 함께 호출될 뿐 여전히 별다를 것 없는 함수에 불과하다. 그렇다면 생성자를 호출할 때 new를 빼먹으면 어떻게 될까..?

답은 다음과 같다. syntax error 혹은 runtime error는 발생하지 않지만, 예기치 못한 결과를 초래할 수 있다. 왜냐하면 new를 뺴먹으면 생성자 내부의 this가 전역 객체를 가리키게 되기 때문이다.

생성자 내부에 this.member와 같은 코드가 있고 이 생성자를 new 없이 호출하면, 실제로는 전역 객체에 member라는 새로운 프로퍼티가 생성된다. 이 프로퍼티는 window.member 또는 member를 통해 접근할 수 있다. 전역 네임스페이스를 사용하게 되므로 이러한 방식은 바람직하지 않다.

```javascirpt
// 생성자
function Waffle() {
	this.tastes = "yummy";
}

// 새로운 객체
var good_morning = new Waffle();
console.log(typeof good_morning); // "Object"
console.log(good_morning); // "yummy"

// anti-pattern
var good_morning = Waffle();
console.log(typeof good_morning); // "undefined"
console.log(window.tastes); // "yummy"
```

ES5에서는 이러한 동작 방식의 문제를 해결하기 위해, strict모드에서는 this가 전역 객체를 가리키지 않도록 하였다. strict모드를 사용할 수 없다면 생성자 함수가 new 없이 호출되어도 항상 동일하게 동작하도록 보장하는 방법을 사용해야한다.
