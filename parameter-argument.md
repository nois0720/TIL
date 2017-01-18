# Parameter와 Argument

Parameter와 Argument는 굉장히 비슷하다고 느낄 수 있는 용어이고, 두 용어를 잘못 혼용하는 경우도 많다. 사실 두 단어는 명확히 다른데, C Programming Language에서는 이 두 용어를 다음과 같이 설명하고 있다.

We well generally use parameter for a variable named in the parenthesized list in a function definition, and argument for the value used in a call of the function. (Parameter는 함수를 선언할 때 변수의 이름을 의미하고 Argument는 함소를 호출하면서 전달하는 값을 의미한다.)

* int function(int a, char b) { } 에서 a, b는 Parameter
* int a = function(10, 'a'); 에서 10, a는 Argument
