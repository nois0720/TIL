# DNS (Domain Name System)

우리는 휴대전화를 사용하면서 친한 친구나 가족의 전화번호를 다 외워서 전화를 걸지 않는다. 보통 전화번호와 함께 이름 혹은 별명등을 대응시켜 전화번호를 외우지 않고도 원하는 사람에게 해당 이름만 검색해서 전화를 건다. 우리는 이런 비슷한 기능을 인터넷에서도 사용하고 있다. 우리는 인터넷을 사용하면서 네이버에 접속하고 싶을 때 브라우저의 주소창에 naver.com를 입력하여 네이버에 접속한다. 사실 naver.com이라고 입력하여 엔터를 치는 순간, DNS라는 녀석이 이를 IP주소로 변환하는 작업을 해준다. 따라서 우리는 실제 naver의 IP주소를 외우지 않고도 쉽게 네이버 페이지에 접속할 수 있다.

nslookup을 통해 naver.com등의 IP주소를 알아낸 후, 브라우저에 해당 주소를 입력하면 네이버 메인페이지가 정상적으로 나옴을 확인할 수도 있다.

**DNS**는 `.com` 또는 `.net` 최상위 도메인(Top-level domain, TLD)의 모든 도메인 네임과 해당 도메인 네임과 대응하는 IP주소를 저장하는 일종의 분산 데이터베이스 시스템이다.

## Domain Name Structure

DNS가 어떻게 동작하는 지 알기 전에, Domain name 구조를 먼저 알아보자.

![domain-name-structure](domain-name-structure.png)

그림을 보면, 도메인 네임 구조는 Hierarchical하다는 것을 확인할 수 있다.

org, edu, com, net, kr... 등은 top level으로 흔히 TLD(Top Level Domain)이라고 하며 각각을 책임지는 기관이 다 다르고 기관마다 정책도 다 다르다.

그 아래에 조금 더 친숙한 debian, google, facebook 등은 second level으로 SLD(Second Level Domain)라고도 부른다. 따라서 google이나 facebook의 IP주소는 com DNS server에서 알고있다. 

도메인 네임에는 www.amazon.com, nois0720@github.com 과 같은 3rd level Domain과 www.edison.k12.js.us와 같은 4th level domain이 있다.

## 동작

그럼 DNS는 어떤 식으로 동작하는가 궁금해진다. 위에서 분산 데이터베이스 시스템이라는 말을 썼는데, 사실 DNS를 구성하는 서버는 `분산`이라는 말에서 알 수 있듯이 하나가 아니다.

![iterated-dns](image/iterated-dns.png)

위의 그림은 DNS의 동작 방식 중 하나인 `Iterated Query`방식이다. 설명을 돕기 위해, 내 컴퓨터에서 gaia.cs.umass.edu이라고 주소창에 입력하는 시나리오를 예로 들어보겠다.

나는 브라우저 주소창에 gaia.cs.umass.edu라고 입력한 후 엔터를 누르겠지만, 브라우저는 사실 gaia.cs.umass.edu에 대한 ip주소를 알아야 해당 주소에 html, css, js등을 요청할 수 있다.

따라서 requesting host는 먼저 Local DNS server에 gaia.cs.umass.edu에 대응하는 ip주소를 알고있는지 물어보기 위해 DNS query를 생성하여 보낸다. 만약 여기서 local DNS Server가 이를 알고있다면, 바로 돌려주게 된다.

* local DNS server가 존재하는 이유가 바로 여기에 있다. 자주 요청하는 주소를 비교적 빠르게 요청/응답이 가능한 local DNS Server에 저장하여 속도를 높힌다.

하지만 local DNS server에 해당 도메인 네임에 해당하는 IP주소가 없다면, 모든 도메인 네임 정보를 가지고 있는 root DNS server에 물어볼 수 밖에 없다. 따라서 local DNS server는 해당 도메인 네임에 대한 정보를 root DNS server에 물어본 후, Iterative하게 Sub Domain Name에 대한 정보를 가진 서버들에게 물어본 후 마지막으로 최종 IP주소를 얻게된다.

