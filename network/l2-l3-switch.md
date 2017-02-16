L3 스위치가 IP Layer를 보고 라우터처럼 동작하는 것은 맞지만 이러면 L3 스위치나 라우터간 구별이 쉽지 않다.

원래 스위치는 Layer2에서 동작하는 장비인데 여기서 Layer2라고 하면 TCP/IP protocol stack에서 MAC layer를 의미한다. 그리고 라우터는 Layer3에서 동작한다. 당연히 Layer3 즉 IP Later에서 동작.
그런데 예전에 이 스위치와 라우터의 동작방식에 결정적이 차이가 하나 있었다. 스위치는 좀 단순하게 하드웨어적으로 MAC address를 보고 들어오는 데이터를 전달 (스위칭, switching) 하는 장비라면. 라우터는 좀더 똑똑하게 소프트웨어적으로 IP Layer를 보고 들어오는 데이타의 경로를 (경로, Path, Route) 결정하는 동작을 한다.
왜냐하면 IP Layer가 Mac보다 훨씬 복잡하기 때문에 하드웨어로 처리하는게 무척 어렵기 때문이다..

즉,
스위치 : L2, MAC address, Hardware동작
라우터 : L3, IP address, Software동작

그런데 시간이 지나면서 하드웨어도 상당히 발전을 많이 했다. ASIC도 발전하게 되어서 MAC address가 아닌 IP address를 보고 경로를 결정할 수 있게 되었다. 그것을 IP Switch 또는 Layer 3 Switch라고 부른다.

요즘에 나오는 L3 switch장비라고 하면 일단 IP address를 보고 switching을 할수 있는 장비를 말한다.
