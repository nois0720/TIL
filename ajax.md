# Ajax (Asynchronous Javascript and XML)

* 전체 웹페이지를 업데이트 하지 않고 웹 브라우저와 웹 서버가 내부적으로 데이터 통신을 통해서 업데이트된 정보를 웹페이지에 프로그래밍적으로 반영한다. 그래서 로딩 없이 서비스 사용이 가능하다.

Tranditional App의 경우, Infrequent Large Update인 반면 Ajax는 Frequent Small Update이다. 즉, Ajax는 전체 페이지 업데이트 하지 않고 비동기적으로 점차 업데이트

## JQuery - 가장 이름있는 1000 만의 웹사이트 중 약 65 %가 jQuery를 갖추고 있다.

JQuery 특징.
1. DOM 조작 가능(navigate a document, DOM 엘리먼트 선택)
2. 애니메이션 생성 기능.
3. 이벤트 핸들링 가능
4. Ajax 애플리케이션 개발 가능.

## jQuery vs Angular
	jQuery는 라이브러리라면 Angular는 프레임워크이다.


## AngularJS : 프론트 앤드 자바스크립트 프레임워크로 주로 구글에 의해 관리되는 프론트앤드 웹 애플리케이션 프레임워크 오픈소스이다.

* multi page를 로딩하지 않고 Single Page App이용.
* Cross-platform, MVC에 기반한 MVVM(model-view-viewmodel)패턴
* 목표 : 웹 애플리케이션의 단순한 개발, 테스팅.

### AngularJS를 사용하는 이점

* 직관적인 프레임워크로 코드 작성이 쉽다.
* 테스트 가능한 코드는 개발자를 밤에 잘 수 있게 만든다.
* 2-way data binding이 코드 라인을 save한다.
	템플릿은 HTML으로 작성하고, 이미 대부분이 어떻게 HTML을 작성하는 지 알고 있다.


###	Angular 2.0

* Angular 1.3과 2.x버전은 거의 다른 프레임워크라고 볼 수도 있다.
* version 업그레이드가 아니라, 완전히 새로 작성되었다.
* Angular 1.3의 컨트롤러와 뷰 대신 component를 사용한다.
	-  $Scope, angular.module을 사용하지 않는다.
* JavaScript의 Superset인 MS TypeScript 사용. Angular2를 사용하기 위해 다음 스텝 사용 
	* package.json을 수정해서 Angular 2.0, TypeScript(ts)관련 module을 설치.
	* tsconfig.json파일 생성, TypeScript compile정보를 설정한다.
*Directive와 Dependency Injection을 사용한다.


## Ajax Motivation

왜 Ajax를 사용하는가?
	
웹앱의 3가지 key problem을 해결하기 위함.
1. Coarse-grained updates : 즉 하나의 요청으로 전체를 업데이트 하는 것을 말함.
2. Synchronous : 결과를 기다리면서 유저는 아무것도 할 수 없다.
3. Extremely limited Option for widgets(GUI elements) - 위젯에 대한 극도로 제한된 옵션

Ajax는 여전히 브라우저 베이스.
Ajax는 "모든 사람이 이미 가지고있는 브라우저로 할 수있는 최선은 무엇인가?”에 대한 답이다.
