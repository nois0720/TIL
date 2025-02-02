# 자바스크립트 부동 소수점

대부분의 프로그래밍 언어는 여러 종류의 숫자형 데이터를 가진다.
하지만 자바스크립트는 number라는 형을 통해서 정수와 부동 소수점 숫자를 표현한다.

자바스크립트 내의 모든 숫자는 [IEEE](https://ko.wikipedia.org/wiki/%EC%A0%84%EA%B8%B0_%EC%A0%84%EC%9E%90_%EA%B8%B0%EC%88%A0%EC%9E%90_%ED%98%91%ED%9A%8C) 754 표준에서 정의한 64비트로 인코딩된 double-precision의 부동 소수점 숫자이다. Integer의 경우 53비트까지의 정확도로 double값으로 표현할 수 있다. 따라서 자바스크립트에서 integer연산도 별도의 integer형 없이도 완벽하게 가능하다.

그래서 대부분의 산술 연산자는 정수형이나 실수 또는 이 둘의 조합으로 동작한다 

```javascript
0.1 * 1.9 // 실수와 실수간 연산
-99 + 100; // 정수와 정수간 연산
21 - 12.3; // 정수와 실수간 연산
2.5 / 5; // 실수와 정수간 연산
```

비트단위 연산자는 조금 특별한데, 인자들을 암묵적으로 32비트 정수로 변환하여 사용한다.

```javascript
8 | 1; // 9
```

이 표현식은 단순하지만 내부적으로 몇 가지 단계를 거치게 된다.
자바스크립트에서 숫자 8, 1은 항상 double형인데 비트연산자를 만나면 32비트 정수형으로 표현된다.

숫자 8은 다음과 같은 형태가 된다
```javascript
00000000000000000000000000001000
```

반면, 숫자 1을 32비트 정수형으로 표현하면 다음과 같다.
```javascript
00000000000000000000000000000001
```

그래서 연산의 결과는
00000000000000000000000000001001으로 9를 나타낸다.

모든 비트단위 연산자는 이처럼 입력 값을 정수형으로 변환하고 정수 비트 연산을 수행하고나서 이 값을 다시 자바스크립트 부동 소수점 숫자 값으로 변환하여 결과를 돌려주는 방식으로 동작한다.
숫자가 부동 소수점으로 저장되기 때문에 자바스크립트 엔진에서는 이것을 반드시 정수형으로 변환되고 다시 부동 소수점으로 되돌려야 한다.

부동 소수점 숫자는 부정확하기로 악명 높은데, 다음과 같은 간단해 보이는 연산에서도 기대하지 않은 결과값을 도출하기도 한다.

```javascript
0.1 + 0.2; // 0.3000000000000004
```
 
64비트의 정확도는 충분히 크지만 실수가 표현할 수 있는 수에 비해서 여전히 유한한 숫자 범위만 표현할 수 있다. 즉 부동 소수점 산술 연산은 근사값만을 만들어 낼 수 있으며, 표현할 수 있는 수 중에서 가장 가까운 값으로 반올림한다. 계속 연산을 수행하다보면 이런 오류가 누적되어 더욱 부정확한 결과를 낳는다.

정확도가 중요한 산술이라면, 자바스크립트의 숫자가 이처럼 double의 정확도를 가진 부동 소수점 숫자라는 것을 명심해야할 것이다.
