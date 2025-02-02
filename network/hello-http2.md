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

## Hello HTTP2

자 이제 그럼 HTTP/2를 만나보도록 하자! HTTP2는 앞서 설명한 SPDY http2 작업그룹이 2012년 10월 부터 시작한 HTTP2 프로토콜 구현을 위한 프로젝트이다. http2 공식 github 페이지의 서문을 보자.

“HTTP/2 is a replacement for how HTTP is expressed “on the wire.” It is not a ground-up rewrite of the protocol; HTTP methods, status codes and semantics are the same, and it should be possible to use the same APIs as HTTP/1.x (possibly with some small additions) to represent the protocol.

The focus of the protocol is on performance; specifically, end-user perceived latency, network and server resource usage. One major goal is to allow the use of a single connection from browsers to a Web site.”

내용은 다음과 같다. 
"HTTP/2는 HTTP가 wire 위에서 표현되는 방법을 대체합니다. 이 것은 프로토콜의 재작성을 의미하지 않습니다. HTTP 메소드, 상태 코드 및 의미는 동일하며 프로토콜을 나타내기 위해 HTTP/1.x와 동일한 API (일부 작은 추가 기능 포함)를 사용할 수 있어야합니다.

HTTP/2의 초점은 성능에 있습니다. 특히 최종 사용자가 대기 시간, 네트워크 및 서버 리소스 사용을 인식합니다. 주요 목표 중 하나는 브라우저에서 웹 사이트로의 단일 연결을 허용하는 것입니다."

다시 말해서, 새로운 프로토콜이 아니라 기존의 HTTP의 성능 향상에 초점을 둔 프로토콜이라고 명시하고 있다.

그럼 HTTP/2가 어떻게 성능 향상을 이끌어내는지 알아보도록 하자.

### Multiplexed Streams

![http2_ms](/image/multiplexed-streams.png)
	
stream은 간단히 정의하자면 Request를 보내고 그에 해당하는 하나의 Response를 받을 수 있는 단위라고 생각할 수 있다.

하지만 HTTP2에서는 하나의 TCP Connection으로 동시에 여러개의 메세지를 주고 받을 수 있으며, 응답은 순서에 상관없이 stream으로 주고 받는다. 

물론 기존의 HTTP/1.1에서도 하나의 connection에 여러 개의 Request를 보낼 수 있는 Keep-Alive 구조가 있다. 하지만 이는 request에 따라 순서대로 response를 보내야한다. 따라서 만약 하나의 response의 사이즈가 크거나, 처리속도가 오래 걸린다면 이는 전체적인 속도의 저하를 일으킨다.(HOLB)

### Stream Prioritization
HTML문서안에 CSS파일 1개와 Image파일 2개가 존재하고, 이를 클라이언트가 각각 요청하였다고 하자. 만약 Image파일보다 CSS파일의 수신이 늦어지는 경우 브라우저의 렌더링이 늦어지는 문제가 발생한다. 반면 HTTP/2의 경우 리소스간 의존관계(priority)를 설정하여 이런 문제를 해결한다.

### Server Push

HTTP2요청에 대해서 서버는 클라이언트가 요청하지 않은 리소스를 마음대로 보내주기도 한다. 이게 무슨 소린가 싶겠지만 설명을 보도록 하자.

예를 들어, 어떤 html파일이 있다고 하자. 이 파일은 보통 css나 js파일을 필요로 할 것이다. 그리고 웹 브라우저는 html파일을 읽어보기 전까지는 어떤 리소스가 필요한지 모르기 때문에, html을 요구하고 기다렸다가 html파일이 도착하면 읽고 분석한 후 여러개의 connection을 생성해서 css, js, image등의 리소스 파일을 요청할 수 있다.

서버에서는 server push 기능을 이용해서 필요한 리소스 파일을 미리 보내어 request에 드는 비용을 줄이고 이런 처리에 드는 delay를 없앤다.

### Header Compression
앞에서 HTTP1.1에 대해서 설명하면서, 헤더 구조의 복잡함에 대해서 이야기했었다. HTTP2에서는 이를 해결하기 위해서, 헤더의 크기를 줄이기 위해 두 가지 방법을 활용한다.

* Huffman Coding
* Header Tables

서버가 헤더 'Date:Wed, 07 Dec 2016 00:00:00 GMT'를 클라이언트에게 전송한다고 하자. HTTP2는 먼저, 헤더 값에 Huffman coding을 적용시킨다. 이때 헤더의 크기는 34에서 29가 된다.

Index | Header Name | Header Value
1 	|	:authority	| 
... |	...			| ...
33 	|	date		| 
... |	...			| ...
61	| 	www-authenticate |

다음으로, Static Header Table에서 'date'을 찾아 이 값을 static header table의 index로 변경시킨다. 여기까지 적용이 되면, 헤더의 크기는 24가 된다. 기존의 크기에서 약 2/3로 줄어들었다. 그리고 이와 동시에, Dynamic Header Table에 'Date:Wed, 07 Dec 2016 00:00:00 GMT'를 저장한다. 

Index	| Header Name	| Header Value
62		| date			| 'Date:Wed, 07 Dec 2016 00:00:00GMT'

만약 또 서버에서 'Date:Wed, 07 Dec 2016 00:00:00GMT'라는 값을 보낸다면, 헤더 필드를 Dynamic Header Table에서 'Date:Wed, 07 Dec 2016 00:00:00GMT'에 해당하는 index로 대체한다. 이 경우 헤더의 크기는 1이 된다..!

### HTTP1.1과 HTTP2의 성능 비교

두 프로토콜의 객관적인 성능비교 지표는 테스트마다 외부 요인의 영향으로 정확하게 알 수는 없지만, 일반적으로 HTTP/2를 사용만 해도 응답 속도가 HTTP/1.1에 비해 15~50%가 향상 된다고 한다.

다음 페이지는 http/1.1과 http2를 비교해볼 수 있는 사이트이다.
[https://http2.akamai.com/demo](https://http2.akamai.com/demo)
