# Socket의 listen()

서버가 listen함수를 호출함으로서 클라이언트가 connect요청을 할 수 있다. 즉, 클라이언트의 connect보다 listen함수가 먼저 호출되어야한다.

```c
#include <sys/socket.h>

int listen(int sock, int backlog);
```

listen함수는 성공 시 0, 실패 시 -1을 반환한다.

* sock : connect request 대기상태에 두고자 하는 소켓의 file descriptor. 이 함수의 argument로 전달된 디스크립터의 소켓이 서버 소켓(listening socket)이 된다.

* backlog : connect request wait queue의 사이즈. 예를 들어 5가 전달되면 큐의 크기가 5가 되어 클라이언트의 connect request를 5개까지 대기시킬 수 있다.

실제로 backlog의 값이 충분히 크지 않으면서 여러 클라이언트가 동시에 connect를 서버에 요청한다면 wireshark에서 retransmission이 일어남을 확인할 수 있다. 이는 queue가 가득 차있어 loss가 발생하고, TCP의 특성상 retransmission이 일어나는 것이다.


