# REST API

## REST API의 탄생

REST는 Representational State Transfer의 약자로서, 2000년도에 로이 필딩 (Roy Fielding)의 박사학위 논문에서 최초로 소개되었습니다. 로이 필딩은 HTTP의 주요 저자 중 한 사람으로 그 당시 웹(HTTP) 설계의 우수성에 비해 제대로 사용되어지지 못하는 모습에 안타까워하며 웹의 장점을 최대한 활용할 수 있는 아키텍처로서 REST를 발표했다고 합니다.

## REST의 구성

REST는 다음과 같이 구성되어있습니다.
# 리소스(Resource) - URI
# 행위(Verb) - HTTP METHOD
# 표현(Representations)

## REST의 특징

#### 1 Uniform (유니폼 인터페이스)

Uniform Interface는 URI로 지정한 리소스에 대한 조작을 통일되고 한정적인 인터페이스로 수행하 는 아키텍처 스타일을 말합니다.

#### 2 Stateless (무상태성)

REST는 무상태성 성격을 갖습니다. 다시 말해 작업을 위한 상태정보를 따로 저장하고 관리하지 않습 니다. 세션 정보나 쿠키정보를 별도로 저장하고 관리하지 않기 때문에 API 서버는 들어오는 요청만을 단순히 처리하면 됩니다. 때문에 서비스의 자유도가 높아지고 서버에서 불필요한 정보를 관리하지 않음으로써 구현이 단순해집니다.

#### 3 Cacheable (캐시 가능)

REST의 가장 큰 특징 중 하나는 REST는 무상태성 성격을 갖는다는 것입니다. 다시 말해 작업을 위한 상태정보를 따로 저장하고 관리하지 않습니다. 세션 정보나 쿠키정보를 별도로 저장하고 관리하지 않기 때문에 API 서버는 들어오는 요청만을 단순히 처리하면 됩니다. 때문에 서비스의 자유도가 높아지고 서버에서 불필요한 정보를 관리하지 않음으로써 구현이 단순해집니다.

#### 4 Self-descriptiveness (자체 묘사)

REST의 또 다른 큰 특징 중 하나는 REST API 메시지만 보고도 이를 쉽게 이해 할 수 있는 자체 표현구조로 되어 있다는 것입니다.

#### 5 Client-Server Architecture

REST 서버는 API 제공, 클라이언트는 사용자 인증이나 컨텍스트(세션, 로그인 정보)등을 직접 관리하 는 구조로 각각의 역할이 확실히 구분되기 때문에 클라이언트와 서버에서 개발해야할 내용이 명확해지고 의존성이 줄어들게 됩니다.

#### 6 Layered Architecture

REST 서버는 다중 계층으로 구성될 수 있으며 보안, 로드 밸런싱, 암호화 계층을 추가해 구조상의 유연성을 둘 수 있고 PROXY, 게이트웨이 같은 네트워크 기반의 중간매체를 사용할 수 있게 합니다.

## REST API 디자인 가이드

REST API설계 시에 가장 중요한 점을 다음 두 가지로 요약할 수 있습니다.

1. URI는 정보의 자원을 표현해야 한다 (리소스 명은 동사보다는 명사를 사용하자)

```html
GET /members/delete/1
```

위와 같은 방식은, REST를 제대로 적용하지 않은 URI입니다. URI는 자원을 표현하는데 중점을 두어야 하지, delete와 같은 행위에 대한 표현이 들어가서는 안됩니다.

2. 자원에 대한 행위는 HTTP Method(GET, POST, PUT, DELETE)로 표현한다.

그래서 위의 잘못된 URI를 HTTP Method를 통해 수정해보면

```html
DELETE /menbers/1
```
으로 수정할 수 있다. 회원정보를 가져올 때에는 GET, 회원 추가 시의 행위를 표현하고자 할 때에는 POST Method를 사용하여 표현합니다.

회원정보를 가져오는 URI

```html
GET /members/show/1    (x)
GET /members/1         (o)
```

회원을 추가할 때
```html
GET /members/insert/2  (x) - GET 메서드는 리소스 생성에 맞지 않음.
POST /members/2        (o)
```

### HTTP METHOD의 알맞은 역할
POST, GET, PUT, DELETE 이 네 가지의 메서드로 CURD를 할 수 있습니다.

METHOD | 역할
POST | URI를 요청하면 리소스를 생성합니다.
GET | 해당 리소스를 조회합니다. 리소스를 조회하고 해당 document에 대한 정보를 가져옵니다.
PUT | 해당 리소스를 수정합니다.
DELETE | 해당 리소스를 삭제합니다

이러한 방식으로 URI는 자원을 표현하는데 집중하고, 행위에 대한 정의는 HTTP Method를 통해 하는것이 REST한 API를 설계하는 메인 아이디어입니다.

### URI 설계 시 주의할 점

1. '/'는 계층 관계를 나타낼 때 사용

http://restapi.example.com/houses/apartments

http://restapi.example.com/animals/mammals/whales

2. URI 마지막 문자로 슬래시(/)를 포함하지 않는다.

URI에 포함되는 모든 글자는 리소스의 유일한 식별자로 사용되어야 하며 URI가 다르다는 것은 리소스 가 다르다는 것이고, 역으로 리소스가 다르면 URI도 달라져야 합니다. REST API는 분명한 URI를 만 들어 통신을 해야 하기 때문에 혼동을 주지 않도록 URI 경로의 마지막에는 슬래시(/)를 사용하지 않습니다.

http://restapi.example.com/houses/apartments/ (X)

http://restapi.example.com/houses/apartments  (0)

3. 하이픈(-)은 URI 가독성을 높히는데 사용한다.

URI를 쉽게 읽고 해석하기 위해, 불가피하게 긴 URI경로를 사용하게 된다면 하이픈을 사용해 가독성을 높일 수 있습니다.

4. 밑줄(_)은 URI에 사용하지 않는다.

글꼴에 따라 다르긴 하지만 밑줄은 보기 어렵거나 밑줄 때문에 문자가 가려지기도 합니다. 이런 문제를 피하기 위해 밑줄 대신 하이픈(-)을 사용하는 것이 좋습니다.(가독성)

5. URI 경로에는 소문자가 적합하다.

URI 경로에 대문자 사용은 피하도록 해야 합니다. 대소문자에 따라 다른 리소스로 인식하게 되기 때문 입니다. RFC 3986(URI 문법 형식)은 URI 스키마와 호스트를 제외하고는 대소문자를 구별하도록 규정하기 때문입니다.

RFC 3986 is the URI (Unified Resource Identifier) Syntax document

6. 파일 확장자는 URI에 포함시키지 않는다.

http://restapi.example.com/members/soccer/345/photo.jpg (X)

REST API에서는 메시지 바디 내용의 포맷을 나타내기 위한 파일 확장자를 URI 안에 포함시키지 않습니다. Accept header를 사용하도록 합시다.

GET / members/soccer/345/photo HTTP/1.1 Host: restapi.example.com Accept: image/jpg

### 리소스간 관계를 표현하는 방법

REST 리소스간에는 연관 관계가 있을 수 있고, 이런 경우 다음과 같은 표현방법으로 사용합니다.

/리소스명/리소스ID/관계가 있는 다른 리소스명

ex) GET : /users/{userid}/devices (일반적으로 'has'의 관계를 표현하기 위해)

만약에 관계명이 복잡하다면 이를 서브 리소스에 명시적으로 표현하는 방법이 있습니다. 예를 들면 사용자가 "좋아하는" 디바이스 목록을 표현해야 할 경우 다음과 같은 형태로 사용될 수 있습니다.

GET : /users/{userid}/likes/devices (관계명이 애매하거나 구체적 표현이 필요한 경우)

### 자원을 표현하는 Collection과 Document

Collection과 Document에 대해 알면 URI 설계가 한 층 더 쉬워집니다. DOCUMENT는 단순히 문 서로 이해해도 되고, 한 객체라고 이해하셔도 될 것 같습니다. 컬렉션은 문서들의 집합, 객체들의 집합 이라고 생각하시면 이해하시는데 좀더 편하실 것 같습니다. 컬렉션과 도큐먼트는 모두 리소스라고 표 현할 수 있으며 URI에 표현됩니다. 예를 살펴보도록 하겠습니다.

http://restapi.example.com.sports/soccer

위 URI를 보시면 sports라는 컬렉션과 soccer라는 도큐먼트로 표현되고 있다고 생각하면 됩니다. 좀 더 예를 들어보자면

http:// restapi.example.com/sports/soccer/players/13

sports, players 컬렉션과 soccer, 13(13번인 선수)를 의미하는 도큐먼트로 URI가 이루어지게 됩니 다. 여기서 중요한 점은 컬렉션은 복수로 사용하고 있다는 점입니다. 좀 더 직관적인 REST API를 위해 서는 컬렉션과 도큐먼트를 사용할 때 단수 복수도 지켜준다면 좀 더 이해하기 쉬운 URI를 설계할 수 있습니다.

## HTTP 응답 상태 코드

마지막으로 응답 상태코드를 간단히 살펴보도록 하겠습니다. 잘 설계된 REST API는 URI만 잘 설계된 것이 아닌 그 리소스에 대한 응답을 잘 내어주는 것까지 포함되어야 합니다. 정확한 응답의 상태코드만 으로도 많은 정보를 전달할 수가 있기 때문에 응답의 상태코드 값을 명확히 돌려주는 것은 생각보다 중 요한 일이 될 수도 있습니다. 혹시 200이나 4XX관련 특정 코드 정도만 사용하고 있다면 처리 상태에 대한 좀 더 명확한 상태코드 값을 사용할 수 있기를 권장하는 바입니다.상태코드에 대해서는 몇 가지만 정리하도록 하겠습니다.

상태코드 | 
200 | 클라이언트의 요청을 정상적으로 수행함
201 | 클라이언트가 어떠한 리소스 생성을 요청, 해당 리소스가 성공적으로 생성됨(POST를 통한 리소스 생성 작업 시)
400 | 클라이언트의 요청이 부적절할 경우
401 | 클라이언트가 인증되지 않은 상태에서 보호된 리소스를 요청했을 때 사용하는 응답 코드
403 | 유저 인증상태와 관계없이 응답하고 싶지 않은 리소스를 클라이언트가 요청했을 때 사용하는 응답코드405 | 클라이언트가 요청한 리소스에서는 사용 불가능한 Method를 이용할 경우
301 | 클라이언트가 요청한 리소스에 대한 URI가 변경되었을 때 사용하는 응답 코드
500 | 서버에 문제가 있을 경우

