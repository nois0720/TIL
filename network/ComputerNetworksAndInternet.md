# Computer Networks & The Internet
## Architecture, Access Networks

### 네트워크란?
상호간에 연결된 어떠한 그룹 혹은 시스템

### 인터넷이란?
1. 서비스의 관점(Service View) - 인터넷을 통해 우리가 할 수 있는 것들.
	* Service View에서, 인터넷은 **Infrastructure**이다!
		* 애플리케이션에 서비스를 제공(web, VoIP, email, games, e-commerce, social nets)
		* 앱에 프로그래밍 인터페이스를 제공(Hooks, Service Options)

2. 구성요소의 관점("Nuts and Bolts" View) - 인터넷을 구성하는 컴포넌트들 (Switch, Links, Protocols)
	* 수백만개의 연결된 computing devices(Hosts = End System, Running Network Apps)
	* Communication Links(Fiber, Copper, Radio, Satelite)
	* Packet Switches(Routers And Switches, Forward Packets)
	* Network of networks(Interconnected ISPs)
	* Protocols => *Software Component* of Internet - Control sending & receiving of messages(TCP, IP, HTTP, Skype, 802.11)
	* Internet Standard => 철저하게 테스트된 Specification(반드시 따라야 함)
		* RFC : Request for comments, IETF : Internet Enginnering Task Force

### 프로토콜이란?
The set of *conventions*
* Conventions - For two communicating entities to successfully communicate.
	* What it is communicated
	* how it is communicated
	* when it is communicated
프로토콜은 포맷, 메시지 송수신 순서 등을 정의.

즉 반드시 상호간 받아들일 수 있는 프로토콜에 따라야 한다!

### 네트워크 구조
1. Network Edge
	* Hosts : Clients & Servers
	* Servers often in data centers
2. Access Network, Physical media
	* Wired or Wireless communication Links
3. Network core
	* InterConnected Routers
	* Network of networks(ISPs)
