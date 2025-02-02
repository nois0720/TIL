<h1> Node.js란? </h1>

<h3> Node.js </h3>

Node.js는 구글의 V8 자바스크립트 엔진을 바탕으로 한 개발 프레임워크로서 자바스크립트로 Node.js코드를 작성하고 나면 이 코드가 실행될 수 있게 V8이 기계어로 컴파일한다. 웹 서버와 서버 측 스크립트, 그리고 지원되는 모든 웹 애플리케이션 기능을 포함한 대부분의 서버 측 코드를 Node.js로 작성할 수 있다.

웹 서버와 이를 지원하는 웹 애플리케이션 스크립트가 동일한 서버 측 애플리케이션에서 함께 실행되므로 웹 서버와 스크립트를 훨씬 견고하게 통합할 수 있다.

<h3> V8 Engine </h3>

V8 자바스크립트 엔진(V8 JavaScript Engine)은 구글에서 개발된 오픈 소스 JIT 가상 머신형식의 자바스크립트 엔진이며 구글 크롬 브라우저와 안드로이드 브라우저에 탑재되어 있다. V8로 줄여 불리기도 하며, 현재 라스 백이 책임 프로그래머이다.

V8은 자바스크립트를 바이트코드(bytecode)로 컴파일하거나 인터프리트(interpret)하는 대신 실행하기 전 직접적인 기계어(x86, ARM, 또는 MIPS)로 컴파일(compile)하여 성능을 향상시켰다(JIT Complie). 또한 추가적인 속도향상을 위해 인라인 캐싱(inline caching)과 같은 최적화 기법을 적용하였다.

Node.js 프레임워크의 특징
* JavaScript End-To-End(단대단 자바스크립트) : Node.js의 가장 큰 장점은 자바스크립트의 서버측 스크립트와 클라이언트 측 스크립트를 둘 다 작성할 수 있다는 점이다. 로직을 클라이언트 스크립트에 작성할지 아니면 서버 스크립트에 작성할지를 정하는 일이 문제였는데, Node.js를 사용할 경우에는 자바스크립트를 클라이언트에 작성할 수 있고 서버에 맞게 쉽게 적용할 수도 있다. 또한 그 반대 방향으로도 가능하다. 또 다른 장점은 클라이언트 개발자와 서버 개발자가 동일한 언어를 사용한다는 점이다
* Event-driven scalability(이벤트 기반 규모 조절성) : Node.js는 웹 요청을 처리하기 위해 여러 스레드가 기다리게 하는 대신 기본 이벤트 모델을 이용해서 웹 요청을 동일한 스레드에서 처리한다. 이는 Node.js 웹 서버가 기존 웹 서버들보다 효율적인 방식으로 동작할 수 있게 한다.
* Extensibility(기능 확장성) : Node.js는 많은 개발자들과 개발 커뮤니티에 의해 기능이 확장되고 새로운 모듈이 제공되고 있다. 또한 이러한 모듈들을 설치하고 추가하는 방법도 간단하다.
* Fast Implementation(빠른 구현 속도)
