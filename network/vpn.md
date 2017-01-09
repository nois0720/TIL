# VPN (Virtual Private Network)

## 목차
* [개요](https://github.com/nois0720/TIL/blob/master/network/vpn.md)
* [등장배경](https://github.com/nois0720/TIL/blob/master/network/vpn.md#등장배경)
* [VPN이란](https://github.com/nois0720/TIL/blob/master/network/vpn.md#VPN이란)
* [종류](https://github.com/nois0720/TIL/blob/master/network/vpn.md#종류)

## 개요
우리는 내부자료유출 사건에서 용의자가**VPN**업체를 통해 정보를 빼낸것으로 추정된다는 말을 기사로 접하기도 하고, 예전 농협 전산망 사건 때 **VPN**을 거쳐 농협 전산망에 접속한 흔적을 발견했다는 기사를 접하기도 한다. 여기에서 해킹을 위한 수단으로 VPN이라는 수단이 사용되었다는 것을 알 수 있다. 게다가 VPN앱에서도 대부분 차단된 사이트를 우회하여 접속하거나 자신의 IP를 감추는데 사용할 수 있다고 되어있다.

마치 ``VPN``은 보안을 뚫기 위한 도구로 오해할 수 있다. 하지만 ``VPN``은 안전하게 네트워크 접속을 하기 위한 도구로 개발되었으며 실제로 보안 강화에 큰 역할을 할 수 있다.

## 등장배경

### 사설망과 공중망(Private Network and Public Network)
먼저 VPN을 이해하기에 앞서 ``사설망``과 ``공중망``에 대해서 알아보자. 

``사설망``은 특정한 회사 혹은 조직이 소유하고, 독점적으로 사용하는 네트워크를 의미한다. '위키피디아에서는 사설 IP 주소공간을 이용하는 네트워크로 RFC 1918과 RFC 4193 표준을 준수한다. 이러한 주소는 가정, 사무실, 기업의 랜에 쓰인다'라고 설명한다. 가장 많이 사용하는 사설망 중 하나는 우리가 집에서 많이 사용하는 공유기 내부에서 사설 IP로 사용하는 네트워크이다.

대표적인 사설망은 회사 내부 네트워크. 행정전산망이나 금융기관에서 사용하는 금융망 등이 있는데, 사설망은 보안과 일정한 통신 품질을 제공한다는 면에서 장점이 있다.

반면 ``공중망``은 불특정 다수의 사용자에게 제공하는 통신망이며, 우리가 흔히 사용하는 인터넷은 대표적인 공중망이다.

대표적인 사설망에서 금융망이 있다고 했었다. 그런데 만약에 은행에서 본점과 지점을 사설망으로 연결하고자 하는 경우 어떻게 연결해야할까? 가장 먼저 떠오르는 방법은 그냥 본점과 지점을 회선으로 연결하여 이를 사설망으로 구축하는 것이다. 이 방법은 간단하고 전송속도도 비교적 안정적이고 보안도 뛰어나겠지만 네트워크 장비를 설치하는데 엄청난 금전적인 비용이 든다.

때문에 고가의 전용망을 사용하지 않고 공중망을 이용하여 사설망처럼 안전한 전용 네트워크를 구성하고자 하는 요구가 생기게 되었고, 때문에 VPN(Virtual Private Network, 가상 사설망)이 탄생하게 되었다.

## VPN이란?

등장배경에서 설명한대로 VPN은 인터넷을 이용해 고비용의 사설망을 대체하는 효과를 얻기위한 기술로 인터넷망과 같은 공중망을 사용하여 둘 이상의 네트워크를 안전하게 연결하기 위해 가상의 터널을 만들어 암호화된 데이터를 전송할 수 있도록 구성된 네트워크라고 정의할 수 있다.

VPN 클라이언트는 VPN서버의 가상 포트로 가상의 콜을 만들기위해 일명 터널링 프로토콜이라 불리는 TCP/IP-based 프로토콜을 사용한다. 일반적인 VPN Deployment 시나리오는 다음과 같다. 먼저 클라이언트가 Remote access server로의 가상의 point-to-point connection을 시작한다. Remote access server가 콜을 받으면, caller에 대한 authentication 절차를 밟고 나면 VPN클라이언트와 organization의 사설망 사이에서 데이터를 주고받게된다.

point-to-point link를 애뮬레이트하기 위해서 데이터는 캡술화되거나 헤더와 함께 감싸진다. 헤더는 데이터가 공유 혹은 공공 네트워크를 통과하여 end-point에 도달할 수 있도록 라우팅 정보를 제공한다. private link를 애뮬레이트하기 위해 데이터는 보안을 위해 암호화된다. 공유 혹은 공공 네트워크에서 인터셉트된 패킷은 암호 키값 없이는 해석할 수 없다. private 데이터가 캡슐화되고 암호화되는 링크를 VPN connection이라고 한다. 

공유 또는 공용 네트워크에서 가로채는 패킷은 암호화 키가 없으면 해독 할 수 없습니다. 개인 데이터가 캡슐화되고 암호화되는 링크를 VPN 연결이라고합니다.

![vpn](/image/vpn.png)

그림과 같이 본점과 지점간 전용망을 연결하는 방법. 그리고 공중망(인터넷)상에서 VPN터널을 구성하고 VPN을 연결하는 것은 논리적으로 동일하며 VPN은 인터넷을 통해 전용망과 같은 사설 네트워크를 구성할 수 있도록 해주는 기술이라고 할 수 있겠다.

## 종류
VPN은 두 가지 타입이 있는데 하나는 Remote Access VPN이고, 다른 하나는 Site-to-site VPN이다. 

* Remote access VPN

Remote access VPN을 사용하면 가정이나 이동중인 사용자가 인터넷과 같은 공용 네트워크에서 제공하는 인프라를 사용하여 개인 네트워크의 서버에 액세스 할 수 있다. 사용자 관점에서, VPN은 VPN client와 기관의 서버 사이의 point-to-point connection이다. 공유 혹은 공공 네트워크의 인프라는 데이터가 private 링크를 통해 전송되는 것처럼 logical하게 나타나므로 관련이 없다.

* Site-to-site VPN

Site-to-site VPN connections(혹은 router-to-router VPN connections라고도 불림)을 사용하면 기관들은 공공네트워크를 통해 분리된 사무실이나 다른 기관과의 연결을 라우팅하는 동시에 커뮤니케이션 시 보안을 유지할 수 있다. 인터넷을 통해 라우팅 된 VPN connection은 logical하게 WAN(wide area network) Link로 작동한다. 아래 그림과 같이 네트워크들이 인터넷으로 연결될 때, 라우터는 VPN connection을 통해서 패킷을 다른 라우터로 포워딩한다. 라우터들에게 VPN connection은 data-link layer 링크처럼 작동한다. 

site-to-site VPN connection은 private network의 두 부분을 연결한다. VPN서버는 VPN서버가 연결된 네트워크에게 라우팅 된 connection을 제공한다. calling route(VPN client)는 answering router에 대해 스스로를 인증하고, 상호간의 인증을 위해서 answering router가 calling router에게 자신을 인증한다. site-to-site VPN connection에서 VPN커넥션을 통해 두 라우터에서 전송한 패킷은 일반적으로 라우터에서 발생하지 않는다.

내일은 VPN 터널링 프로토콜에 대해서 다루도록 하자
