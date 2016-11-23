# javascript 작성 시 기본 패턴

## 단일 var 패턴
함수 상단에서 var 선언을 한 번만 쓰는 패턴은 꽤나 유용하여 쓸만한데, 아래와 같은 이점이 있다.

* 함수에서 필요로 하는 모든 지역 변수를 한군데서 찾을 수 있다.
* 변수를 선언하기 전에 사용할 때 발생하는 로직상 문제를 막는다.(hoisting)
* 변수를 먼저 선언한 후에 사용해야 한다는 사실을 상기시키기 떄문에 전역 변수를 최소화하는 데 도움이 된다.
* 코드량이 줄어든다.

```javascript
function func() {
	var a = 1,
		b = 2,
		sum = a + b;
		...
	// function 본문
}
```

위의 코드를 보면, var를 한 번만 선언하고 여러 개의 변수를 쉼표로 연결하여 선언했다. 변수를 선언할 때 초기 값을 주어 초기화하는 것 역시 좋은 습관이다. 이는 문법 오류를 막을 수 있고(초기 값 없이 선언된 변수들은 모두 undefined로 초기화된다.) 가독성도 향상된다.

## for loop

for loop 안에서는 보통 배열이나 arguments 등의 배열과 비슷한 객체를 순회한다. 일반적인 for loop 패턴은 다음과 같다.

```javascript
for(var i = 0; i < myarray.length; i++) {
	// myarray[i]를 다루는 코드
}
```

이 패턴의 문제점은 루프를 순회할 때 마다 배열의 length에 접근한다는 것이다.(myarray.length) 이러한 형태로 DOM객체 등에 접근할 경우, 굉장히 비용이 커진다. 따라서 for loop를 좀 더 최적화하기 위해서, 아래와 같이 배열의 length를 캐시해야 한다!

```javascript
for(var i = 0; max = myarray.length; i < max; i++) {
	// myarray[i]를 다루는 코드
}
```

이렇게 하면 length를 한 번만 구하고, 루프를 수행하는 동안 이 값을 사용하게 된다. 실제로 HTMLCollection을 loop할 때 length를 캐시하면, 브라우저에 따라 적어도 2배에서 190배정도의 성능 향상을 기대할 수 있다고 한다.

물론 루프 내에서 DOM element를 추가하는 등 콜렉션에 대한 변경을 의도한다면 length값을 갱신해주어야 한다.

## for-in loop

for-in loop는 배열이 아닌 객체를 순회할 때만 사용해야 한다. for-in으로 루프를 도는 것을 enumeration이라고도 한다.

자바스크립트에서 배열 역시 객체이기 때문에 기술적으로는 배열을 순회할 때도 for-in loop를 사용할 수도 있지만, 배열 객체에 사용자가 정의한 기능이 추가되었다면 오류가 발생할 수도 있기 때문에 권장하지 않는다. 또한 for-in에서는 property를 열거하는 순서가 정해져있지 않다. 따라서 배열에는 일반적인 for loop를 사용하고, 객체에만 for-in loop를 사용하는 것을 추천한다.

객체의 프로퍼티를 순회할 때에는 프로토타입 체인을 따라 상속되는 프로퍼티들을 걸러내기 위해서 hasOwnProperty()메서드를 사용해야 한다.

다음 예제를 보자

```javascript
// 객체
var man = {
	hands: 2,
	legs: 2,
	heads: 1
}

// 코드의 다른 부분에서 모든 객체에 메서드 하나가 추가되었다면?
if(typeof Object.prototype.clone === "undefined") {
	Object.prototype.clone = function() {};
}
```

이 예제는 객체 리터럴을 사용하여 man이라는 이름의 간단한 객체를 정의했다. man을 정의하기 전이나 후, 어디선가 Object프로토타입네 clone()이라는 이름의 메서드가 편의상 추가되었다면 어떻게 될까.

프로토타입 체인의 변경 사항은 실시간으로 반영된다. 따라서 모든 객체가 새롭게 추가된 이 메서드를 사용할 수 있게 된다. man을 열거할 떄, clone()메서드가 나오지 않게 하려면 프로토타입 프로퍼티를 걸러내기 위해 hasOwnProperty()를 호출해야 한다. 이렇게 걸러내지 않으면 clone()이 나오게 되는데, 대부분 이러한 경우 원치 않은 결과를 초래한다.

```javascript
for (var i in man) {
	if(man.hasOwnProperty(i)) { // 프로토타입 프로퍼티를 걸러낸다.
		console.log(i, ":", man[i];
	}
}

/*
출력 결과
hands : 2
legs : 2
heads : 1
*/
```

만약 hasOwnProperty를 사용하지 않으면 어떻게 될까?

```javascript
for (var i in man) {
	console.log(i, ":", man[i];
}

/*
hands : 2
legs : 2
heads : 1
clone : function()
*/
```

이러한 것을 막기 위해서, Object.prototype에서 hasOwnProperty()를 호출하는 것도 하나의 패턴이 될 수 있다.

```javascript
for (var i in man) {
	if(Object.prototype.hasOwnProperty.call(man, i)) {
		console.log(i, ":", man[i]);
	}
}
```

이 방법은 man객체가 hasOwnProperty를 재정의하여 덮어썼을 경우에도 활용할 수 있다는 장점이 있다. 프로퍼티 탐색이 Object까지 거슬러 올라가지 않게 하려면, 지역변수를 사용하여 이 메서드를 캐시하는 방법을 사용할 수 있다.

## 암묵적 타입 캐스팅 피하기

자바스크립트는 변수를 비교할 때 암묵적으로 타입캐스팅을 실행한다. 때문에 false == 0 이나 "" == 0과 같은 비교가 true를 반환한다!

암묵적 타입캐스팅으로 인한 혼동을 막기 위해서, 항상 표현식의 값과 타입을 모두 확인하는 ===연산자와 !==연산자를 사용해야 한다

```javascript
var zero = 0;
if(zero === false) {
	// 실행되지 않는 블록
}

if(zero == false) {
	// 실행된다!
}
```

## parseInt

parseInt()를 사용하면 문자열로부터 Number 값을 얻을 수 있다. 이 함수는 두 번째 매개변수로 숫자의 기수를 받는데, ES3의 경우 0으로 첫 번쨰 파라미터에 해당하는 스트링이 시작하는 경우 8진수로 간주하여 예측을 벗어나는 결과를 얻을 수도 있다.

## 중괄호

자바스크립트에서는 보통 if문과 함께, 여는 중괄호의 위치를 if문과 같은 라인에 둔다. 이는 단순 취향 문제처럼 보일 수 있다. 하지만 그렇지 않다.

자바스크립트는 세미콜론을 생략할 수 있다. 이러한 동작 방식은 함수의 반환 값이 객체 리터럴이고, 이 객체의 여는 중괄호가 다음 행에 올 경우 문제를 일으킬 수 있다.

```javascript
function func() {
	return
	{
		name: "Batman"	
	};
}
```

이 함수가 name 프로퍼티를 가진 객체를 반환할 것이라고 예상할 수 있겠지만, 자동으로 추가된 세미콜론 때문에 이 함수는 undefined를 반환한다. 위의 코드는 다음 코드와 동일하다.

```
function func() {
	return undefined;
	{
		name: "Batman"
	};
}
```


