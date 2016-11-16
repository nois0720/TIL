# javascript 작성 시 기본 패턴

## 단일 var 패턴
함수 상단에서 var 선언을 한 번만 쓰는 패턴은 꽤나 유용하여 쓸만한데, 아래와 같은 이점이 있다.

* 함수에서 필요로 하는 모든 지역 변수를 한군데서 찾을 수 있다.
* 변수를 선언하기 전에 사용할 때 발생하는 로직상 문제를 막는다.(hoisting)
* 변수를 먼저 선언한 후에 사용해야 한다는 사실을 상기시키기 떄문에 전역 변수를 최소화하는 데 도움이 된다.
* 코드량이 줄어든다.

'''javascript
function func() {
	var a = 1,
		b = 2,
		sum = a + b;
		...
	// function 본문
}
'''

위의 코드를 보면, var를 한 번만 선언하고 여러 개의 변수를 쉼표로 연결하여 선언했다. 변수를 선언할 때 초기 값을 주어 초기화하는 것 역시 좋은 습관이다. 이는 문법 오류를 막을 수 있고(초기 값 없이 선언된 변수들은 모두 undefined로 초기화된다.) 가독성도 향상된다.

## for loop

for loop 안에서는 보통 배열이나 arguments 등의 배열과 비슷한 객체를 순회한다. 일반적인 for loop 패턴은 다음과 같다.

'''javascript
for(var i = 0; i < myarray.length; i++) {
	// myarray[i]를 다루는 코드
}
'''

이 패턴의 문제점은 루프를 순회할 때 마다 배열의 length에 접근한다는 것이다.(myarray.length) 이러한 형태로 DOM객체 등에 접근할 경우, 굉장히 비용이 커진다. 따라서 for loop를 좀 더 최적화하기 위해서, 아래와 같이 배열의 length를 캐시해야 한다!

'''javascript
for(var i = 0; max = myarray.length; i < max; i++) {
	// myarray[i]를 다루는 코드
}
'''

이렇게 하면 length를 한 번만 구하고, 루프를 수행하는 동안 이 값을 사용하게 된다. 실제로 HTMLCollection을 loop할 때 length를 캐시하면, 브라우저에 따라 적어도 2배에서 190배정도의 성능 향상을 기대할 수 있다고 한다.

물론 루프 내에서 DOM element를 추가하는 등 콜렉션에 대한 변경을 의도한다면 length값을 갱신해주어야 한다.

## for-in loop

for-in loop는 배열이 아닌 객체를 순회할 때만 사용해야 한다. for-in으로 루프를 도는 것을 enumeration이라고도 한다.

자바스크립트에서 배열 역시 객체이기 때문에 기술적으로는 배열을 순회할 때도 for-in loop를 사용할 수도 있지만, 배열 객체에 사용자가 정의한 기능이 추가되었다면 오류가 발생할 수도 있기 때문에 권장하지 않는다. 또한 for-in에서는 property를 열거하는 순서가 정해져있지 않다. 따라서 배열에는 일반적인 for loop를 사용하고, 객체에만 for-in loop를 사용하는 것을 추천한다.


