# CDN (Content delivery network 또는 Content distribution network)

CDN은 음원, 영상 등의 대용량 파일을 안정적으로 제공하기 위해 구상되었는데, 이 과정에서 CDN을 이용하면 자주 사용되는 파일의 병목현상을 해결할 수 있음이 확인된 전송 기술이다. CDN은 초기에 미국에서 집중적으로 개발되었는데, 땅이 넓어 네트워크의 중간에서 서버에 문제가 발생하거나 전송망에 이상이 생기면 전송 속도가 매우 낮아지는 상황이 많았기 때문이다. 특히 동부와 서부를 연결하는 중부지방에 전송망이 집중되어 형성되는 미들마일 구간에서의 전송에러와 중간 손실문제를 해결할 필요성 때문에 개발되었다.

## 원리

ISP네트워크 말단에 캐시 서버를 여러대 설치한다. 이후 요청에 대해 가장 가까운 여러 캐시서버들에서 데이터를 전송한다. 캐시 서버가 설치된 지역 혹은 국가의 것을 우선적으로 전송한다는 점에서 P2P와는 차이가 있다. 

## 장점

CDN을 설치하면 병목현상이 만드는 전송속도 저하를 막고, 타사의 ISP를 거치며 발생하는 데이터 손실을 방지할 수 있다. 또한 ISP에 문제가 생겨도 다른 ISP에 설치된 캐시서버에서 전송하므로 연결이 끊기지 않는다.

## 서비스

실제 서비스로는 가장 많이 볼 수 있는 Cloudflare가 있으며, 나무위키도 해당 서비스를 사용하고 있다. 그래서 나무위키의 경우 우리나라에서는 서울에 있는 IDC((Internet Data Center)에서 나무위키의 내용을 캐싱하였다가 보여준다.
