# DASH(Dynamic Adaptive Streaming over HTTP)

## 소개

`DASH`는 ISO 표준(ISO/IEC 23009-1)으로 개발된 HTTP Adaptive Streaming의 한 종류이다. Adaptive Streaming은 'Adaptive'라는 말에서 알 수 있듯이 클라이언트는 자신의 단말기 네트워크 상황에 맞추어 적절한 비디오 화질을 선택하여 서비스를 받을 수 있는 기술이다.

2008년부터 HTTP 기반의 Adaptive Streaming에 대한 이슈가 `MPEG(Moving Picture Expert Group)`에서 핫하게 떠오르기 시작했다. `MPEG`는 향후에 이 기술이 기존의 Streaming 서비스 환경에 크게 영향을 줄 것으로 예상했고, `MPEG`에서는 `DASH(Dynamic Adaptive Streaming over HTTP)`라는 그룹을 만들어 관련된 Streaming Package 포맷에 대한 표준화를 시작했다. 

기존에는 회사마다 이와 유사한 기술을 사용하고 있었다.

* Adobe의 HTTP Dynamic Streaming
* Apple의 HTTP Live Streaming (HLS)
* Microsoft 의 Smooth Streaming

이러한 기술들은 거의 유사한 기술이었지만 호환이 되지 않고 있었다. 그래서 표준화를 진행한 것도 하나의 이유이다. 현재 `YouTube`가 1080p 이상 화질의 동영상을 `MPEG-DASH` 형태로, 비디오와 오디오 스트림을 따로 제공하고 있다.

## 동작

**DASH Server**에서는 비디오 컨텐츠를 먼저 각각 다른 bit rate를 갖는 여러 버전으로 인코딩 한다. 이후 인코딩된 비디오 데이터를 작은 세그먼트(또는 chunck)단위로 분할한다. **DASH Client**에서는 자신의 상황에 따라서 비트 rate 적용 알고리즘을 수행하여 네트워크의 가용 대역폭을 계산하고 계산한 값을 토대로 다음으로 전송받을 비디오 세그먼트의 비트 rate를 결정한다. 즉, DASH 클라이언트의 비디오 플레이어가 현재 단말 네트워크의 상태 및 *QoE*를 고려하여, 적절한 비디오의 화질을 선택하여 서비스한다.

* QoE(Quality of Experience) : 제공할 수 있는 품질. 서비스를 받는 개개인의 서비스 만족도와는 직접적인 관계에 있지는 않다. 따라서 **사용자가 요금을 지불한 서비스에 대하여 기대하는 값을 근거로 규정하는 품질 척도**를 말한다. 예를 들면 품질은 낮아도 요금이 싼 서비스가 비싸고 최고 품질의 서비스보다 QoE가 높을 수 있다. 

## 요소

* MP (Media Presentation)
	* 오디오/비디오는 하나의 파일로 묶을 수 있다 (예를 들면, HTTP Live Streaming)
	* 각각의 파일로 분리될 수 있다. (예를 들면, Smooth Streaming)
	
**각각 예시들이 뭔지는 나중에 찾아볼것**

* MPD(Media Presentation Description)
	* 스트림의 정보를 나타내는 XML.

## 특징

* DASH는 MP4 포맷, MPEG-2 Tranport Stream을 지원한다.
* (DRM을 명시하지는 않았지만) ISO/IEC 23001-7: Common Encryption 표준에 명시된 모든 DRM 기술을 지원한다.
* 재생 이동, 빨리 재생, 되감기 등의 trick 모드를 지원한다.
* 광고 삽입을 지원한다.

* DRM : `Digital rights management`은 출판자 또는 저작권자가 그들이 배포한 디지털 자료나 하드웨어의 사용을 제어하고 이를 의도한 용도로만 사용하도록 제한하는 데 사용되는 모든 기술들을 지칭하는 용어다. 이는 종종 복사 방지, 기술 보호 장치와 혼동하기도 한다. 앞의 두 용어는 DRM의 일부로, 이런 기술이 설치된 전자장치 상의 디지털 콘텐츠에 대해 사용을 제어하는 데 사용되는 기술을 지칭한다.

## 문제점

* Adobe와 Apple의 지원이 부족하다.
* 로열티 무료가 불확실하여 Mozilla와 같은 단체의 지원을 받지 못함. 이 부분은 Google이 지원의사를 밝혔기 때문에 다소 해결될 전망이라고 함.
