# Socket

소켓은 Application간 통신을 위한 End System으로 네트워크 통신을 위해 유저는 직접 TCP/IP 레벨에 접근하지 않고 소켓을 통해 해당 기능을 사용할 수 있게 한다.

소켓은 1982년 BSD(Berkeley Software Distribution) Unix 4.1에서 처음 소개되었다. 현재 널리 사용되는 소켓은 1986년 BSD Unix 4.3에서 개정된 버젼이다.

소켓은 네트워크 프로그래밍을 위한 인터페이스를 제공하며, 이는 커널의 애플리케이션 레이어와 프로토콜 레이어 사이에 존재하게 된다.

## 소켓 생성

소켓의 생성은 sock()함수를 통해 생성할 수 있다.

```c
int sock(int domain, int type, int protocol);
```

위와 같은 형태로 소켓을 생성할 수 있으며 각각의 attribute들은 다음과 같다.

* domain
	- PF_INET (IPv4)
	- PF_INET6 (IPv6)
	- PF_UNIX (UNIX)
	- etc

* type
	- SOCK_STREAM (stream-oriented. e.g. TCP)
	- SOCK_DGRAM (datagram-based. e.g. UDP)
	_ SOCK_RAW (raw-mode. e.g. ICMP)

* protocol :
	- 0 (by default)

* return
	- file descriptor on success
	- -1 or error (with error number)

소켓을 생성하면, 해당 소켓의 파일 디스크립터 값을 리턴한다. 이를 통해 해당 소켓에 옵션을 주거나 close 등을 할 수 있게 된다.

## sk_buff

소켓을 생성하면 내부적으로는 sk_buff라는 구조체를 생성한다.

![sk_buff](/image/sk-buff.png)

그림을 보면, sk_buff에는 Application의 data, transport layer header, network layer header, link layer header의 정보를 저장하기 위한 포인터가 있다. 원래 OSI 7 Layer 구조에서는 이러한 정보를 encapsulation 할 때마다 메모리 카피가 발생하게 되는데, 소켓을 생성하여 sk_buff구조체를 활용하면 처음부터 모든 공간을 만들어두고 해당 포인터 값만 잘 주면 되므로 각 레이어에서 메모리 카피가 발생하지 않는다는 이점도 있다.
