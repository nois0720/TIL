# ARP란?

* IP 주소에 대응되는 이더넷카드의 하드웨어 주소(MAC주소)를 알아내는 프로토콜
* 논리적 주소를 물리적 주소로 변환
* 주소변환방법
- Static Mapping : 관리자수동설정
- Dynamic Mapping : ARP,RARP
 
## ARP Packet 구조

1. Hardware Type
- 16bit로 ARP가 수행되고 있는 네트워크 유형을 정의
- 이더넷인 경우 값은 1로 설정됨
2. Protocol Type
- 16bit로 상위 프로토콜을 정의
- 상위 프로토콜이 IP일경우 0x0800으로 설정됨
3. Hardware Length
- 8bit로 물리주소의 길이를 바이트 단위로 정의
- 이더넷인 경우 6으로 설정
4. Protocol Length
- 8bit로 논리주소의 길이를 바이트단위로 정의
- 이더넷인 경우 4로 설정
5. Operation
- 16bit로 패킷의 유형을 정의
- ARP Request : 1, ARP Reply : 2
6. Sender Hardware Address
- 송신자의 물리주소를 나타내는 필드
- 이더넷의 경우 이필드는 6byte값
7. Sender IP Address
- 송신자의 논리주소를 나타내는 필드
- IP프로토콜인 경우 4byte값
8. Target Hardware Address
- 목적지 시스템의 물리주소를 정의
- 이더넷의 경우 6byte값
- ARP Request인경우 송신자는 목적지 시스템의 물리주소를 몰라 모두 0으로 설정
9. Target IP Address
- 목적지 시스템의 논리주소를 정의
- IP 프로토콜의 경우 4byte값
 
## ARP 작동과정
1. 송신자는 목적지 IP Address를 지정해 패킷송신
2. IP프로토콜이 ARP프로토콜에게 ARP Request 메시지를 생성하도록 요청
3. 메시지는 2계층으로 전달되고 이더넷  프레임으로 Encapsulation
4. 모든 호스트와 라우터는 프레임을 수신 수 자신의 ARP프로토콜에게 전달
5. 목적지 IP Address가 일치하는 시스템은 자신의 물리주소를 포함하고 있는 ARP Reply메시지를 보냄
6. 최초 송신측은 지정한 IP Address에 대응하는 물리주소를 획득

**ARP요정은 브로드캐스트, ARP응답은 유니캐스트**
 
## ARP Cache
1. 송신 시스템이 수신시스템에게 데이터를 보내기 전에 먼저 cache내용을 참조하게함으로써 효율적인 통신을 위해 사용
2. ARP Cache내 저장된 정보는 일정 시간이 지날때까지 사용되지 않으면 지워짐
3. ARP Cache 정보 저장 시간은 일반적으로 2분 동안 저장
4. 2분 이내 다시 통신이 일어나면 10분으로 Cache 저장 시간을 늘림
