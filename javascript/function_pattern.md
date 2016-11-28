# Function Pattern

### 1. 콜백 패턴

함수는 객체이다. 함수는 다른 함수에 인자로 전달할 수 있다. introduceBugs() 함수를 writeCode() 함수의 인자로 전달하면, 아마도 writeCode()는 어느 시점에 introduceBugs()를 호출할 것이다. 이 때 introduceBug()를 콜백 함수 또는 간단하게 콜백이라고 부른다.

```javascript
function writeCode(callback) {
	// 어떤 작업을 수행한다.
	callback();
	// ..
}

function introduceBugs() {
	// 버그를 만든다.
}

writeCode(introduceBugs);
```

introduceBugs()가 writeCode()의 파라미터로 괄호없이 전달된 사실을 눈여겨 보자. 괄호를 붙이면 함수가 실행되는데 이 경우 함수의 레퍼런스만 전달하고, 실행은 추후 적절한 시점에 writeCode()가 해줄 것이기 때문에 괄호를 덧붙이지 않았다.

예제를 통해 살펴보자. 먼저 처음에는 콜백함수를 사용하지 않고, 점차 리팩토링하면서 진행할 것이다. 복잡한 작업을 수행한 후에 그 결과로 대용량의 데이터셋을 반환하는 범용 함수가 있다고 하자. 이 함수는 DOM트리를 탐색하여 필요한 엘리먼트의 배열을 반환한다.

```javascript
var findNodes = function() {
	var i = 100000, // 긴 루프
		nodes = [], // 결과를 저장할 배열
		found; // 노드 탐색 결과

	while (i) {
 		i -= 1;
		// 이 부분에 복잡한 로직이 들어간다.
		nodes.push(found);
	}
	return nodes;
}
```

이 함수는 범용으로 쓸 수 있도록 실제 엘리먼트에는 어떤 작업도 하지 않고 단지 DOM 노드의 배열을 반환하기만 하도록 유지하는 게 좋다. 노드를 수정하는 로직은 다른 함수에 두는 것이 좋다. 예를 들면 페이지에서 노드를 숨기는 로직에 해당하는 hide()라는 함수를 만들었다.

```javascript
var hide = function (nodes) {
	var i = 0, max = nodes.length;
	for (; i < max; i += 1) {
		nodes[i].style,display = "none";
	}
};

hide(findNodes());
```

이 구현 방법은 findNodes()에서 반환된 노드의 배열에 대해서 hide()가 다시 루프를 돌아야하기 때문에 총 두 번 루프를 돌아야 한다. findNodes()에서 노드를 선택하고 바로 숨길 수 있다면 루프를 한 번만 돌게 하여 효율적인 코드가 될 것이다.

하지만 findNodes()안에서 이러한 로직을 구현한다면 탐색과 수정 로직이 결합되고 범용 함수의 의미가 퇴색될 것이다. 바로 이런 경우 콜백 패턴을 사용할 수 있다. 노드를 숨기는 로직의 실행을 콜백 함수에 위임하고 이 함수를 findNode()에 전달한다.

```javascript
var findNodes = function (callback) {
	var i = 100000,
		nodes = [],
		found;

	if(typeof callback !== "function") {
		callback = false;
	}

	while (i) {
		i -= 1;
		// 복잡한 로직 구현한다.
		if(callback) {
			callback(found);
		}

		 nodes.push(found);
	}

	return nodes;
}
```

이 구현 방법은 직관적이다. findNodes()에는 콜백 함수를 확인하고 실행하는 작업 하나만 추가되었다. 콜백은 생략할 수 있기 때문에 findNodes()는 여전히 전과 동일하게 동작하고, 기존의 API에 의존하는 코드를 망가뜨리지 않는다.

hide()의 구현은 노드들을 순회할 필요가 없어져 더 간단해졌다.

```javascript
var hide = function(node) {
	node.style.display = "none";
};

findNodes(hide);
```

이처럼 이미 존재하는 함수를 콜백 함수로 쓸 수도 있지만 findNodes()함수를 호출할 때 익명 함수를 생성하여 쓸 수도 있다. 예를 들어, 동일한 범용의 findNodes()함수를 사용해 노드를 보여주는 방법은 아래와 같다.

```javascript
findNodes(function (node)) {
	node.style.display = "block";
});
```

### 콜백과 scope

이전의 예제에서, 콜백함수는 callback(parameters) 같은 형태로 실행되었다. 이 코드는 간단하기도 하고 대부분 충분히 훌륭하게 동작한다. 그러나 콜백이 일회성의 익명 함수나 전역함수가 아닌 객체의 메서드인 경우도 있다. 만약 콜백메서드가 자신이 속해 있는 객체를 참조하기 위해 this를 사용하면 예상치 않게 동작할 수도 있다.

myapp이라는 객체의 메서드인 paint()함수를 콜백으로 사용한다고 가정해보자. 
```javascript
	var myapp = {};
	myapp.color = "green";
	myapp.paint = function (node) {
		node.style.color = thie.color;
	};
```

그리고 위에서 정의한 findNodes(myapp.paint)를 호출하면 this.color가 정의되지 않아서 예상대로 동작하지 않는다. findNodes()는 전역 함수이기 때문에, 객체 this는 전역 객체를 참조한다. 만약 findNodes()가 객체의 메서드라면, 콜백 내부의 this는 예상과는 달리 myapp이 아닌 해당 객체를 참조하게 된다.

이 문제를 해결하기 위해서, 콜백 함수와 함께 콜백이 속해 있는 객체를 전달하면 된다. 

```javascript
	findNodes(myapp.paint, myapp);
```

전달받은 객체를 바인딩하도록 findNodes()또한 수정한다.

```javascript
var findNodes = function(callack, callback_obj) {
	//...
	if (typeof callback === "function") {
		callback.call(callback_obj, found);
	}
	//...
}
```

콜백으로 사용될 메서드와 객체를 전달할 때, 메서드를 문자열로 전달할 수도 있다. 이렇게 하면 객체를 두 번 반복하지 않아도 된다. 다시 말해서 다음 명령을 

```javascript
// 1
findNodes(myapp.paint, myapp);

// 2
findNodes("paint", myapp);
```

1 혹은 2와 같이 바꿀 수 있다. 

```javascript
	if (typeof callback === "string") {
		callback = callback_obj[callback];
	}
	// ...
	
	if (typeof callback === "function") {
		callback.call(callback_obj, found);
	}
	// ...
```
