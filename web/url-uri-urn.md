# URI과 URL 그리고 URN

URI와 URL, URN은 종종 마주하는 용어이지만 이 세 용어가 어떻게 다른 지 설명하라고 하면 막상 쉽지 않다. 

## URL

URL은 Uniform Resource Locator의 약자로 **프로토콜**, **도메인 네임**, **하위 경로**로 구성되는 **자원에 대한 주소 혹은 위치**라고 볼 수 있다.

URL에는 https://www.google.co.kr과 같은 웹사이트 주소도 포함되지만, 메일 주소나 FTP주소 등도 여기에 포함된다.

## URN

URL의 경우, 주소를 기반으로 하기 때문에 해당 위치에 있는 자원이 없어지는 경우 기능을 상실한다. URN은 이를 보완하기 위해 만들어졌다고 한다. URN은 Uniform Resource Name의 약자로 특정 리소스에 대한 *unique*한 이름이다. 즉, 해당 리소스가 존재하는 한 영구적이고 바뀌지 않는 값이다. 사람으로 치면 주민등록번호같은 것이라고 할 수 있겠다.

## URI

URI는 Universal Resource Identifier의 약자로 단어에서도 알 수 있듯이 Identifier. 즉 리소스를 식별할 수 있는 식별자이다. URL과 URN도 리소스를 가리키는 용어이지만, URI는 더 넓은 의미이다.

간단히 말하자면, URL과 URN은 URI의 부분집합이라고 할 수 있다. 구별하기 위해 URL(주소) 혹은 이름(URN)이 필요한데, 이 것들을 포괄하는 개념이라고 할 수 있겠다.
