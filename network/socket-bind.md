# Socket의 bind.

socket에서의 bind는 소켓 디스크립터를 포트넘버와 ip주소를 연관시키는 것을 말하는데, 여기서 bind는 NIC와 어떤 연관이 있을까?

------

bind는 Receive와 관련되어 Receive 할 때에만 해당 인터페이스를 이용한다. 따라서 Send와는 관련이 없다. 아래 그림을 보자.

!(exam)[bind-exam-1.png]

Appl.1, Appl.2는 왼쪽의 NIC와 bind되어있다. 또한 Appl.3은 오른쪽 NIC와 bind되어있다. 따라서 Appl.1, Appl.2에게 전송되는 데이터는 왼쪽의 NIC를 통하여 전송되고 Appl.3은 오른쪽 NIC를 통해 전달된다.

그런데, 특정 애플리케이션에서 데이터를 보낼 때에도 같은 NIC를 이용할까? Send는 bind와 상관이 없고, 라우팅 테이블을 보고 상황에 따라 다르게 보내게 된다. 
