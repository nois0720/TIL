# Connectionless transport : UDP

## UDP(User Datagram Protocol [RFC 768])
UDP는 1980년 '데이빗 리드'가 설계하였고, 현재 IETF의 RFC768의 표준으로 정의되어 있다. TCP와 함께 데이터그램으로 알려진 단문의 메시지를 교환하기 위해 사용된다. 

## 특징

UDP의 전송방식은 너무 단순해서 'No frills' 혹은 'Bare bone' internet transport protocol이라고 부르기도 한다. 이러한 단순한 전송방식 때문에 중간에 데이터가 손실되기도 하며 데이터그램의 도착 순서가 바뀌거나, 중복되기도 하고 심지어 통보 없이 누락되기도 한다. UDP의 경우 일반적으로 오류 검사 혹은 수정이 필요하지 않은 애플리케이션에서 수행하는 것을 가정으로 한다.

UDP는 loss tolerant. rate sensitive한 성격을 가지는 Streaming multimedia app에서 주로 사용되며, DNS. SNMP의 경우에도 사용된다. DNS의 경우 주고받을 패킷의 양이 거의 없으므로 TCP처럼 굳이 handshake하는 것이 더 오버헤드가 크기 때문에 UDP를 사용하며, SNMP도 비슷한 맥락에서 UDP를 사용한다.

UDP를 사용해서 Reliable하게 데이터를 전송하고 싶다면, application layer에 reliability를 추가하여야 한다.

## Segment Header

UDP segment header의 구조는 아래 그림과 같다.

![segment-header-udp](https://upload.wikimedia.org/wikibooks/en/d/d9/Header_of_UDP.jpg)
