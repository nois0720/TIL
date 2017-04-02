# Iterative Server vs Concurrent Server

## Iterative server 

`Iterative Server` 는 클라이언트의 서비스 요구를 순서대로 처리해주는 서버이다. Request 처리시간이 짧거나 문제가 되지 않을 경우에 사용한다. 이 서버는 프로그램 구현이 비교적 간단하다. 하지만 서비스를 순서대로 처리하기 때문에 Convoy Effect와 유사한 문제가 발생한다.

실제로 Iterative server에서 LimitQueue의 크기를 1~2정도의 작은 값으로 설정해두고 여러 클라이언트가 동시에 echo 서버에 짧은 간격으로 각각 요청하는 경우, wireshark에서 packet retransmission이 일어남을 확인할 수 있었다.

## Concurrent server

`Concurrent Server` 는 여러 요구를 동시에 서비스 할 수 있는 서버이다. 새로운 클라이언트가 접속할 때마다 서비스를 담당할 프로세스를 새로 할당하는 방법을 사용한다. 하지만 이런 경우 클라이언트가 많아질수록 부담이 커지므로 하나의 프로세스에서 멀티쓰레드 등을 사용하여 소켓을 여러개 생성하는 방법을 주로 사용한다.
