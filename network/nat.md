# NAT (network address transmission)

NAT란 network address transmission의 약자로 하나의 호스트에 IP주소를 할당하는 일반적인 방식과 달리, 여러 호스트와 translator간 로컬 네트워크를 형성하고, 외부에서는 translator에게 IP주소를 할당하고 translator가 로컬 네트워크의 각 host들에게 별도의 IP주소를 할당하여 datagram을 주고받도록 하는 기술이다. 이 translator가 IP 패킷의 TCP/UDP 포트넘버와 source, destination의 ip주소를 변경하여 network traffic을 주고받도록 해준다. 따라서 패킷 정보에 변화가 생기게 되며 이에 따라 checksum도 다시 계산하고 기록해야 한다. NAT는 여러 호스트가 하나의 공인 IP주소를 사용하여 인터넷에 접속할 수 있게 한다. 하지만 그만큼 네트워크 성능 저하를 가져오기도 한다.

!(nat)[image/nat.png]

## 요약

* IP주소 하나에 여러 호스트가 사용가능하도록 하여 비용절감의 효과를 가진다.
* 외부에서는 내부 네트워크를 파악할 수 없다. 
* 패킷을 변경하는데 오버헤드가 발생하고 때문에 성능 저하를 유발한다.

* NAT이 IPv4 -> IPv6로 넘어가지 않도록 하는데 큰 기여를 하고 있다고도 한다.
