# PXE (Preboot Execution Environment)

회사에 첫 출근을 했던 날이었다. 첫날이라서 회사에서 준 컴퓨터의 작업환경을 셋팅하는 일이 필요했다. 그런데, 따로 USB등을 이용한 부팅디스크를 이용하여 OS를 설치하지 않고 PXE라는 환경을 사용하여 따로 운영체제가 설치되어 있지 않은 컴퓨터를 단지 네트워크에 참가시키는 것만으로 부팅을 시킬 수 있었다. 이쪽 업계에서 나만 몰랐던 기술일 수도 있겠지만 여태까지 부팅디스크 = USB로 생각하며 삶을 살아온 나에게는 너무너무 신기했고 그래서 좀 더 찾아보게 되었다. 

PXE는 메인보드에서 지원하는 기능이며, 요즘 출시되는 메인보드들은 대부분 PXE를 지원한다고 한다. 실제로 내 데스크탑에 들어간 Asrock B150M PRO4 제품 역시 PXE기능을 지원함을 asrock 홈페이지의 제품 specification을 확인하여 알 수 있었다. 이 기능을 활성화한 후 부트 오더 가장 첫번째에 LAN을 두면 활성화시킬 수 있다. 보드마다 설정하는 방법은 조금씩 다를 수 있다고 하니 특정 메인보드에 대한 구체적인 내용은 메뉴얼을 참고하면 될 것 같다.

## 동작

PXE의 동작은 DHCP, TFTP에 초점을 둘 수 있다. 처음에 PXE에서 가장 먼저 실행되는 것은 DHCP클라이언트이다. 일반적으로 DHCP(Dynamic Host Configuration Protocol)는 IP주소가 없는 클라이언트가 IP주소를 서버로부터 할당받아서 사용하는 방법이다. 하지만 PXE의 경우 IP주소만 할당하는 일반적인 DHCP응답 메시지가 아니라 PXE를 위해 부가적으로 커널 이미지를 받아올 수 있는 부트 서버의 목록을 함께 보낸다. 이렇게 DHCP 서버로부터 IP주소를 할당받은 후에, 클라이언트는 필요한 부트 서버를 찾고 다운로드할 파일을 정할 수 있다. 그 다음에 tftp프로토콜을 이용하여 원하는 커널이미지를 서버로부터 다운로드 받을 수 있게 된다.

tftp는 ftp와 비슷하지만 전혀 다른 프로토콜이다. tftp는 udp를 이용하는 파일 전송 프로토콜이므로 reliable하게 데이터 전송을 하지 못한다. 하지만 단순하고 가볍기 때문에 커널이미지의 전송에 사용하기에는 큰 문제가 없다. 이를 통해 다운로드 받은 커널이미지를 통해 클라이언트는 부팅을 할 수 있다.

## 장점

PXE를 사용하여 얻을 수 있는 이점은 크게 세 가지이다.
* 클라이언트 PC에 OS, 심지어 하드디스크조차 반드시 있을 필요가 없다.
* 클라이언트 PC는 하드웨어나 소프트웨어의 고장시 재부팅 될 수 있다. 이를 통해 관리자가 문제를 파악하고 해결할 수 있게 한다.
* PXE는 서버와 독립적이기 때문에, 새로운 형태의 컴퓨터도 쉽게 네트워크에 추가할 수 있다.
