# Raw Socket

일반적으로 애플리케이션 레벨에서 데이터를 보내면 커널에서 이에 대한 프로토콜 헤더를 덧붙여 전송한다. 그러나 새로운 프로토콜을 설계하여 그에 대한 구현이 필요하거나 패킷을 세밀하게 조작할 필요가 있다. 이때 Raw 소켓을 사용하면 커널 수준에서 다룰 수 있는 패킷의 헤더 등을 직접 구현하거나 조작할 수 있다.

Raw 소켓을 생성하거나 수정할 수 있는 권한, 생성할 수 있는 Raw 소켓의 종류는 운영체제마다 다르며 root권한을 가지고 있어야 Raw소켓을 생성할 수 있다.

## 생성 방법

socket 함수의 두 번째 argument로 SOCK_RAW, 세 번째 argument에는 원하는 프로토콜을 주어 생성한다.

## 사용 이유

앞에서 패킷을 세밀하게 조작하거나 새로운 프로토콜 사용 등의 이유도 있으나 Ip 데이터그램이나 ICMP, IGMP을 읽고 쓰는것이 가능하다.
