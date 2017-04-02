# Marshalling (마샬링)

오늘 회사에서 마샬링이란 단어를 들었는데, 다소 생소한 용어라 정리하게 되었다.

`Marshalling`이라는 단어의 사전적 의미는 선박에서 양하된 컨테이너를 부두 밖으로 수송하기 위해서 혹은 컨테이너를 선박에 싣기 위해 부두 내에서 이동, 정렬하거나 잠시 대기시키는 것을 말한다고 한다. 즉, 컨테이너들을 다른 장소로 보내기 위해서 순서를 잘 정리한다는 뜻이다. 

그래서 컴퓨터 사이언스에서 마샬링은 메모리에 있는 어떠한 객체의 메모리 구조를 저장하거나 전송하기 위해 적당한 자료형으로 변형하는것을 의미한다고 한다. 그래서 보통 다른 환경의 컴퓨터나 다른 프로그램간에 데이터의 이동이 필요할 경우 사용된다고 한다. 예를 들면 컴퓨터 A에서는 Little Endian으로 데이터를 정렬하고, 컴퓨터 B에서는 Big Endian으로 데이터를 정렬한다고 하자. A에서 B로의 데이터 전송 시 B가 정확히 이해할 수 있게 Big Endian으로 데이터를 변형해 주어야 한다. 마샬링을 수행함으로써 복잡한 통신, 사용자 정의/복잡한 구조의 객체들을 사용하는 대신에 단순한 primitive타입 등을 사용할 수 있다. Marshalling의 반댓말은 Unmarshalling이다.

## Serialization

반면 `Serialization`은 객체의 상태를 저장하기 위해 객체를 byte stream으로 변환하는 것을 의미한다. 반대는 `Deserialization`이다.

## Marshalling vs Serialization

Serialization과 Marshalling은 그럼 어떻게 다를까? 다시 정리하면, Serialization은 자료구조 혹은 객체의 상태를 저장(File, Memory Buffer, Network 등에 사용)할 수 있는 포맷으로 변환하는 것을 말한다. 그리고 이는 다른 컴퓨터 환경에서도 Deserialization을 통해 같은 것으로 재조립이 가능하다.  
객체지향에서 객체의 Serialization은 객체와 관련된 메소드를 포함하지 않는데, 이를 마샬링이라고 부르기도 한다. 마샬링은 객체의 메모리 표현을 저장공간이나 전송에 적합한 데이터 포맷으로 변환하는 과정이다. 이는 데이터가 프로그램에서 다른 프로그램으로 이동할 때 많이 사용된다.

Marshalling은 여기저기서 파라미터를 얻는 반면 Serialization은 바이트 스트림과 같은 primitive한 type으로부터 구조화된 데이터를 복사해 오는 것과 관련이 있다. 이런 의미에서 Serialization은 Marshalling을 수행하기 위한 한 가지의 수단으로 볼 수도 있으며, 이런 상황에서는 Pass-by-value로 수행된다.

Serialization은 오브젝트의 멤버변수만 바이트스트림으로 변환한다. 즉, 코드(베이스)를 포함하지 않는다.

Marshalling은 오브젝트를 remote object로 전달할 때 쓰이는 용어다. (RMI. Remote Method Invocation) Marshalling은 오브젝트의 멤버와 코드베이스를 함께 포함한다.  
즉, Serialization은 Marshalling의 일부라고 할 수 있다.

코드베이스는 오브젝트 코드의 위치를 포함한다. 따라서 코드가 로컬에 없어 수행할 수 없어도 코드베이스를 찾아 코드를 수행할 수 있다. (코드베이스 의미가 정확히 어떤건지 알아봐야지)
