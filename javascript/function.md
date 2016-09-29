# Javascript의 함수

자바스크립트에서는, primitive type을 제외한 모든 것은 객체인데, 함수도 Function객체로, 역시 예외는 아니다.

자바스크립트에서 함수는 first-class object(혹은 citizen, value)인데,
이때 first-class-object는 
* 변수나 data structure안에 담을 수 있다.
* parameter로 전달할 수 있다.
* return value로 사용할 수 있다.
* 런타임에 생성할 수 있다.
* 할당에 사용된 이름과 관계 없이 고유하게 식별할 수 있다.
이러한 조건들을 충족하는 객체이다.

자바의 메소드는 위의 조건들을 만족시키지 못하기 때문에 first-class object라고 할 수 없다.

## 함수와 익명함수

자바스크립트에서 함수를 정의하는 방법은 크게 Function객체를 사용하는 방법, 그리고 연산자인 function을 사용하는 방법이 있는데, 일반적으로 후자를 많이 사용한다.

Function객체를 사용할 경우
```javascript
var add = new Function('a', 'b', 'return a + b');
add(1, 2); // 3을 반환한다.
```

위와 같이 코드가 문자열로 전달되기 때문에 가독성이 떨어지며 메모리 사용이 좋지 못하고, 실행될때마다 매번 동적으로 생성되며, Scope에 문제가 있다고 한다.

그래서 잘 안씀!

그래서 두 번째 방법인 function연산자를 이용한 방법을 많이 쓰는데,
이 방식은 함수 선언(function declaration)과 함수 표현(function expression)으로 나뉜다.

함수 선언(function declaration)은 Function Statement라고도 하는데, 말그대로 함수 문장이라는 의미이다. 즉 실행가능한 코드블럭이 아니라 함수의 정의를 나타내는 문장으로 해석되고, 코드 해석에 따른 수행결과가 존재하지 않는다.

함수 선언(function declaration)은 아래와 같이 사용한다
```javascript
function go() {
	// 실행문
}
```
이와 같은 방식은 자바스크립트 인터프리터가 스크립트를 로딩하는 시점에 바로 초기화하고 이를 VO(variable object)에 저장하기 때문에 함수 위치와 상관없이 소스 내 어느곳에서든 호출이 가능하다.

함수 표현(function expression)은 Function Literal이라고도 한다. 이것은 실행 가능한 코드로 해석되거나 변수나 데이터 구조에 함수가 할당됨을 의미한다! 즉 해당 코드블럭이 실행코드로서 해석되고, 동시에 코드 실행에 따른 결과값을 가지거나 혹은 특정 변수에 할당된 값으로 존재하게 된다.

다시 말해서, 함수 표현(function expression)은 특정 변수에 할당되거나 즉시 실행가능한 코드 블럭으로서 존재하는 함수를 의미한다.

```javascript 
// anonymous function expression (익명 함수 표현식)
// foo(변수)에 할당
var foo = function(){
	console.log('hello');
};

// named function expression(기명 함수 표현식)
// 역시 foo에 할당
var foo = function foo(){
	console.log('hello');
}

// self invoking function expression(즉시 실행 함수 표현식)
// 바로 코드 실행.
(function foo(){
	console.log('hello');
})();
```

위의 코드에서 두 번째 예제인 named function expression의 경우 해당 함수의 이름을 밖에서는 사용할 수 없다는 특징이 있다.
```javascript
var foo = function A(){
	A(); // 실행 가능
}

A(); // syntax error
```
