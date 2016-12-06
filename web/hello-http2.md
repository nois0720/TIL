# HTTP2

HTTP는 HyperText Transfer Protocol의 약자로, 웹에서 정보를 주고 받는데 사용되는 프로토콜이다. 1996년 처음 1.0버전이 릴리즈되고 1999년 우리가 가장 많이 사용하는 1.1버전이 출시된 이후 15년간 발전없이 사용되고 있었다.

현재의 웹은 많은 양의 멀티미디어 리소스를 처리해야하고 웹페이지 하나를 구성하기 위해 다수의 비동기 요청이 발생된다. 이를 처리하기에 HTTP1.1은 느리고 비효율적이였다. 특히 모바일 환경에서는 더욱 그러하다.

그럼 HTTP/1.1 의 동작 방식에 대해서 알아보도록 하자

## HTTP/1.1의 동작 방식

다시 말하지만 HTTP는 웹상에서 클라이언트(Browser)와 서버(웹서버)간 통신을 위한 프로토콜이다. HTTP 1.1 프로토콜은 클라이언트와 서버 간 통신을 위해서 다음과 같은 과정을 거치게 된다.

![http1.1](/image/http1-1.png)

그림에 대해서 설명이 굳이 필요 없을 정도로 간단한데, HTTP/1.1은 기본적으로 connection 하나당 하나의 요청만을 처리하도록 설계되었다. 그래서 그림과 같이 단일 전송만 가능하고 요청과 응답은 순차적으로 이루어진다. 즉, 동시에 여러 요청을 전송할 수 없다. 

이 때문에 HTTP문서 내에 포함된 다수의 리소스(이미지, CSS, JS)등을 요청하기 위해 리소스 양에 비해서 Latency(대기 시간)은 길어진다.

## HOL(Head Of Line) Blocking

웹 환경에서 HOLB는 두 종류가 존재한다.

* HTTP의 HOL Blocking
* TCP의 HOL Blocking

이 글에서는 HTTP에 대해서 설명하고 있으니 TCP의 HOL Blocking에 대해서는 다음에 글을 추가하도록 하고 HTTP의 HOL Blocking에 대해서 알아보도록 하자.

HTTP/1.1의 Req-Res는 항상 순서를 기준으로 수행된다. 하나의 TCP 연결에서 3 개의 이미지(1.png, 2.png, 3.png)를 얻으려고 할 때, HTTP의 요청 순서는 다음과 같다.

 ----- 1.png -----
				
                  ----- 2.png -----

   					 			   ----- 3.png -----

이미지를 요청하고, 응답받고 나서야 다음 이미지를 요청하게 된다. 그런데 만약 첫 번째 이미지를 요청하고 응답이 지연될 경우, 그 다음 요청할 이미지는 첫 번째 이미지에 대한 응답이 완료되기까지 기다려야 하며 이를 HTTP의 Head of Line Blocking이라고 한다.

## RTT(Round Trip Time) 증가

앞서 말한것처럼 HTTP/1.1은 하나의 connection에 대해 하나의 요청만을 처리한다.(일반적으로 그렇고 keep-alive, pipe lining기법이 있긴 함) 그래서 매 요청마다 connection을 만들게 되고 TCP 위에서 동작하는 HTTP의 특성 상 3-way Handshake가 반복적으로 일어나 불필요한 RTT가 증가하고 네트워크 성능이 저하된다.

## 복잡한 헤더 구조

HTTP/1.1의 헤더에는 많은 메타데이터들이 저장된다. 그런데 사용자가 방문한 웹 페이지는 다수의 http요청이 발생하고, 이 경우 매 요청마다 중복된 헤더값을 전송하게 되며(특히 domain sharding 하지 않은 경우) 또한 해당 도메인에 설정된 쿠키정보도 매 요청시마다 헤더에 포함된다. 이런 복잡한 헤더 구조 때문에 전송하려는 값보다 헤더가 큰 경우도 생긴다.

## 그래서 해결 방법은?

그래서 이러한 HTTP/1.1의 문제점을 극복하기 위해서 여러가지 기술이 도입되었는데
* Domain Sharding
* Image Spriting
* Minify css/JS
* Data URI Schema
* Load Faster
등이 있다.

### Domain sharding

![http1.1](/image/domain-sharding.png)

최신 버전의 브라우저들은 HTTP/1.1의 단점을 극복하기 위해 다수의 connection을 생성해서 병렬로 요청을 보낸다.(그림의 왼쪽 예) 하지만 이러한 connection의 max값이 존재하고 너무 많은 도메인을 이용할 경우 DNS검색과 TCP handshake에서 발생하는 시간때문에 오히려 역효과를 발생할 수도 있다.

### Image Spriting

웹페이지를 구성하는 작은 이미지 파일의(주로 아이콘) 요청 횟수를 줄이기 위해서, 이를 하나의 큰 이미지로 만든 다음 CSS에서 해당 이미지의 좌표 값을 지정해 표시하도록 한다.

### Minify CSS / JS

전송하는 데이터를 줄이기 위해 CSS, JS파일을 축소하여 적용하기도 한다. 방법에 대해서는 [How to minify CSS, JS & HTML files](http://technumero.com/internet/minify-javascript-and-css/3007)에서 다루고 있다.

### Data URI Scheme

Data URI Scheme은 HTML문서내에 이미지와 같은 외부 데이터를 URI로 표현하는 방법이다. 보통 HTML에서 이미지를 표현할 때에는 img element의 src 속성 값으로 이미지 경로를 입력하지만, Data URI Scheme을 이용하면 src 속성 값으로 Base64로 인코딩된 이미지 데이터를 직접 입력할 수 있다. 이렇게 하면 이미지와 같은 외부 데이터를 별도의 파일로 두지 않고, 하나의 HTML 파일로 관리할 수 있다. 파일이 하나가 되면서 HTTP 헤더 정보나 TCP 패킷 크기가 맞지 않아서 발생할 수 있는 오버헤드가 발생하지 않는다. 그 결과 요청을 줄이고 빠른 전송 효과를 기대할 수 있게 된다. 

하지만 HTML파일에 포함되다보니 캐시가 되지 않는다는 단점이 있다. 또한 base-64로 데이터를 인코딩하면서 크기가 증가한다. 용량 측면에서 HTTP헤더에서 이득을 보았다고 하더라도 600바이트가 넘어가는 이미지의 경우 base-64 인코딩때문에 손해를 보게 된다.


이런 눈물겨운 노력에도 불구하고 HTTP/1.1의 단점을 근본적으로는 해결할 수 없었고, 구글은 더 빠른 웹을 구현하기 위해서 throughput관점이 아니라 Latency 관점에서 HTTP를 고속화한 SPDY라 불리는 새로운 프로토콜을 구현하였다. SPDY는 HTTP를 대치하는 프로토콜은 아니고 HTTP를 통해 전송을 재정의하는 형태로 구현되었다. SPDY는 HTTP/1.1에 비해서 상당한 성능 향상을 보여줬고, 이는 HTTP/2 초안의 참고 규격이 되었다. 참고로 구글은 SPDY를 올해 말까지만 지원한다고 한다. 곧 http/2로 변경될 예정이라고 함.)

다음 페이지는 http/1.1과 http2를 비교해볼 수 있는 사이트이다.
[http2-test](https://http2.akamai.com/demo)
