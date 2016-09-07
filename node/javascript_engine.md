<h1> JavaScript 엔진의 최적화 </h1>

소스코드
-> bytecode형태의 중간언어(IR)로  파싱
-> JITC모드냐? interpreter모드냐?
-> JITC면 실행중에 native code로 변경, interpreter면 그냥 bytecode 형태로(IR) 읽음

그냥 단순히 생각하면 native code를 읽는게 당연히 byte code 읽는것보다 빠르니까 JITC가 좋을것 같지만.. 이것 역시 상황에 따라 다름


GCC(GNU Compiler Collection)같은 static compiler라면 native code를 생성할때 많은 최적화 알고리즘을 적용하기때문에 코드의 성능(code quality)이 높지만 JITC는 말 그대로 수행 중에 컴파일을 하기 때문에 이것이 큰 overhead가 되고, 즉 컴파일에 많은 시간을 쏟을 수 없다는 말이 된다.

그래서 Data flow analysis가 필요한 코드 전체를 훑어서 최적화하는 방식은 사용할 수 없고, 최소한의 최적화만 사용하여 native code를 생성해야한다.


그럼에도 불구하고 interpreter 수행시간보다 JITC overhead가 포함되더라도 native code의 수행시간이 월등하기 때문에 Java VM에서는 JITC를 많이 사용한다.


<h3> 그럼 JavaScript에서는? </h3>

JavaScript는 변수의 타입이 런타임에 달라질 수 있고 클래스 대신 object로 상속되는 prototype-based방식을 사용하는 등 매우 동적인 언어이기 때문에 JITC는 모든 예외적인 케이스를 고려해서 코드를 생성해야 한다는 문제가 있다.

이런 많은 예외 때문에 많은 native code가 생성되는 것을 막기 위해 helper function을 호출하는데, 이 helper function은 interpreter모드에서 쓰는 코드와 같다.

그리고 JavaScript로 구현된 코드 특성이 연산이 많은 Java프로그램과는 달리, 웹페이지의 레이아웃을 건드리거나, 유저 인풋에 반응하는 방식의 프로그램이 많다. 즉 JavaScript는 자주 반복되어 수행되는 구간(hotspot)이 상대적으로 매우 적다.


hotspot이 적은 경우 native code를 수행하는 시간에 비해서 native code를 만드는 시간이 길다. 다시 말해 compile overhead가 상대적으로 커진다.

그래서 사실 JIT compiler로 native code를 수행한다고 해도 많은 부분이 interpreter와 별반 차이가 없게 된다. 여기에 compilation overhead가 더해지므로 hotspot이 별로 없는 JavaScript에서는 interpreter보다 JITC가 훨씬 비효율적이다.

근데 최근 JavaScript도 단순히 web에서 이벤트 처리 용도로만 사용되는게 아니라 compute-intensive한 프로그램 구현에도 점차 요구되고 있기 때문에 JITC를 완전히 버릴 수 없었다.


그럼 고전적인 방식의 JavaScript코드와 compute-intensive한 코드들의 수행 성능을 모두 만족시킬 방법은 없나?


<h2> Adaptive JIT Compilation </h2>

그래서 최근 JavaScript엔진들은 Adaptive JIT Compilation 방식을 택하고 있다고 함!

이 방식은 모든 코드를 일괄적으로 같은 수준으로 최적화 하지 않고, 반복 수행 정도에 따라 유동적으로 서로 다른 최적화 수준을 적용한다.


처음에는 모든 코드 interpreter로 수행
-> hotspot 발견
-> 그 부분에 대해서 JITC적용 -> native code로 수행

최근 엔진들은 JITC도 여러 단계로 나누어서 적용.
처음에는 최소한의 최적화(baseline-JITC)만 적용해서 컴파일하고, 더 자주 반복되는 코드에는 더 많은 최적화(Optimizing_JITC) 적용하여 code quality가 높은 코드 생성.

공통적으로 Adaptive JITC를 사용하는 엔진은 runtime profiler가 있고 얘가 함수 수행 빈도를 기록. 뿐만 아니라 profiler는 사용되는 변수의 타입이나 값을 profile해두었다가 optimizing JIT를 적용할 때 이들 정보를 이용하여 예전에 JITC에서 생성했던 예외 처리 루틴들을 대폭 생략한 효율적인 코드를 생성.

근데 이런 경우에도 예외가 있을 수 있음.
예를들면 loop를 100만번 수행하는 동안 x가 integer였다가 갑자기 다음 iteration에서 갑자기 string으로 바뀌는 경우.
이 경우에는 optimiziong JITC로 생성된 코드가 더 이상 유효하지 않기 때문에 다시 예전에 baseline-JITC로 생성한 코드로 수행하게 된다. 이런 예외가 발생하면 오버헤드가 엄청나게 커지지만, 이런 경우가 드물다고 가정을 둔 최적화 방식이다.


<h3> 요약 </h3>
* Hotspot이 별로 없는 고전적인 JavaScript 프로그램들에는 interpreter가 JITC보다 효율이 좋다.
* 최근 많이 사용되는 compute-intensive한 JavaScript 프로그램들에는 JITC가 좋다.
* 두 가지 성향의 코드에 대한 성능을 모두 만족하기 위해 최근 엔진들은 adaptive JITC를 채용한다.
* Adaptive JITC는 type profiling을 수행하므로, 변수의 type이 변하지 않는다면 높은 성능을 얻을 수 있다.
