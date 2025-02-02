# Socket의 bind.

socket에서의 bind는 소켓 디스크립터를 포트넘버와 ip주소를 연관시키는 것을 말하는데, 여기서 bind는 NIC와 어떤 연관이 있을까?

---

bind는 Receive와 관련되어 Receive 할 때에만 해당 인터페이스를 이용한다. 따라서 Send와는 관련이 없다. 아래 그림을 보자.

!(exam)[bind-exam-1.png]

Appl.1, Appl.2는 왼쪽의 NIC와 bind되어있다. 또한 Appl.3은 오른쪽 NIC와 bind되어있다. 따라서 Appl.1, Appl.2에게 전송되는 데이터는 왼쪽의 NIC를 통하여 전송되고 Appl.3은 오른쪽 NIC를 통해 전달된다.

그런데, 특정 애플리케이션에서 패킷을 보낼 때에도 같은 NIC를 이용할까? 답은 '그때그때 다르다.' 이다. Send는 bind와 상관이 없고, 라우팅 테이블을 보고 상황에 따라 다르게 보내게 된다. 

여기서 라우팅 테이블을 사용한다는 것은 라우팅 알고리즘을 사용한다는 뜻은 아니다. 라우터의 경우 RIP/OSPF등의 라우팅 알고리즘을 사용하지만 내 노트북이 그런 알고리즘을 돌리지는 않는다. 커널에서는 라우팅 테이블에서 longest match를 통해 매칭되는 인터페이스를 사용하고, 해당 정보가 없다면 네트워크 카드의 default gateway를 이용한다. 물론 명령어를 통해 라우팅 테이블을 변경시킬 수도 있다.

## INADDR_ANY

그럼 만약 Network Interface가 여러 개 존재하는 소위 Multi-Homed 환경에서 여러 개의 NIC로 부터 패킷을 전달받아야 하는 상황이 있다면 어떨까.

위의 방법으로는 특정 NIC로 패킷이 전송되지 않는 이상 해당 애플리케이션으로 패킷을 전달받을 수 없다. 하지만, sockAddr struct의 sin_port를 다음과 같이 작성하는 경우,

```c
...
sockAddr.sin_port = INADDR_ANY;
```

어떤 NIC로부터 패킷이 도착하더라도 이를 받을 수 있다.
