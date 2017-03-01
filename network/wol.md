#WOL(wake on lan)

웨이크 온 랜(Wake-on-LAN, WOL)은 네트워크 메시지를 보냄으로써 컴퓨터의 전원을 켜거나 절전 모드에서 깨어나게 하는 *이더넷 컴퓨터 네트워킹 표준*이다.

이 메시지는 일반적으로 동일 근거리 통신망(LAN)의 다른 컴퓨터에서 실행되는 프로그램이 송신한다. 서브넷 다이렉트 브로드캐스트(subnet directed broadcasts)나 WOL 게이트웨이 서비스를 이용하여 다른 네트워크로부터 메시지를 초기화하는 것도 가능하다. 이 용어는 영어 낱말로서 wake on WAN, remote wake-up, power on by LAN, power up by LAN, resume by LAN, resume on LAN, wake up on LAN으로도 부른다. 와이파이를 통해 통신하여 컴퓨터를 깨우려면 WoWLAN(Wake on Wireless LAN)이라는 부가 표준을 이용하여야 한다.

WOL, WoWLAN 표준은 프로토콜 투명 주문형 서비스(protocol-transparent on-demand services)를 제공하는 업체들이 이따금 추가 제공하는데, 이를테면 애플 봉주르의 웨이크 온 디맨드(wake-on-demand, 슬립 프록시/Sleep Proxy) 기능을 들 수 있다.

## 적용

windows의 기능을 이용하여 실제 내 데스크탑에도 적용시켰다. 방법은 다음과 같다.

1. BIOS의 wol 옵션 enable로 변경 -> 이 부분에서 옵션 이름 등은 장치마다 조금씩 다를 수 있으니 메인보드 메뉴얼이나 설명 보고 하면 됨.
2. windows 장치 관리자에서 네트워크 어댑터 설정 -> 아래 옵션 on으로 변경.
	* wake on magic packet
	* wake on pattern match
3. 맥에서 wakeonlan 설치
4. 터미널에서 로컬의 경우 wakeonlan **mac address**, 외부 네트워크에서는 wakeonlan -i **ip address** **mac address** 명령어로 원격 부팅

이렇게 실행된 컴퓨터는 remote access가능하다. 즉 집밖에서도 집컴퓨터를 쓸 수 있다!!

## 추가내용

wol을 위해 remote desktop의 ip address를 알아야 하는데, 이 때 유동 ip때문에 생기는 문제는 ddns를 통해 해결할 수 있다. (nslookup을 이용해 ip주소를 알아낼 수 있음)
