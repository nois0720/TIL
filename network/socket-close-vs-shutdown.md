# close()와 shutdown()

소켓의 연결을 종료시키는 방법에는 close와 shutdown함수를 사용하는 방법이 있다. close의 경우, 모든 스트림을 닫아 데이터를 보낼 수도 받을 수도 없게 되고, shutdown은 option을 설정하여 half close를 하거나 모두 close하여 close()와 같은 효과를 낼 수도 있다.

기본적으로, 소켓을 생성하면 동시에 메모리가 할당된다. shutdown의 경우, 초창기 컴퓨팅 환경에서 메모리 관리가 크리티컬하게 작용했고, 이 때문에 데이터를 보내기만 할 때 혹은 받기만 할 때 조금이라도 메모리를 절약하는 방법으로서 사용되었다고 한다. 또한 보낼 데이터는 모두 보냈지만 이후 받을 데이터가 있고 이 데이터가 언제 도착할 지 모르는 경우에 shutdown을 사용한다고 한다.

int shutdown(int sockfd, int howto);

위의 howto argument에 아래와 같은 값들을 입력할 수 있다.

* SHUT_RD : Half close. read. 이 소켓으로는 데이터를 받을 수 없다.
* SHUT_WR : Half close. write부분. 즉 send부분만 닫는다. 따라서 어떤 데이터도 보낼 수 없다.
* SHUT_RDWR : close()와 동일하다.
