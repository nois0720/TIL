# Connection-Oriented

네트워크를 공부하다보면 `Connection-Oriented` 라는 용어와 종종 마주친다. 대체 Connection-Oriented가 뭘까.

처음부터 결론내리기보다는 주로 어떤 친구들이 `Connection-Oriented` 한 성격을 가지는지 알아봤다. 

1. TCP
2. 전화

사실 처음에 TCP의 예만 들었을때는 `ACK` 가 떠올랐다. Connection-Oriented. 내 요청 혹은 메시지에 대해서 잘 전달받았다는 말을 해주면 Connection-Oriented 한 게 아닐까?

그런데 2번째 예를 보고나면 조금 말이 달라진다. 내가 친구와 통화를 하면서 내 이야기만 하고 대답을 듣지 않아도 Connection-Oriented 하다는 말도 되는 것이다. 그럼 다시 돌아와서 Connection-Oriented 하다는게 도대체 어떤거지? 하는 생각이 들게 된다.

---담

`Connection-Oriented`를 굳이 한마디로 말하자면 Sender가 보낸 정보에 대해서 Receiver가 그 정보를 받음을 확신할 수 있는 것을 말한다. (사실 그래서 ACK을 떠올린건 아주 잘못된건 아니였다.)
	
하지만 두 예제간에는 사소하지만 큰 차이가 있다.

1. 먼저 전화의 경우를 생각해보자. 전화는 circuit switching방식을 사용하여 *Physically*하게 회선이 확보가 된다. 따라서 Connection-Oriented라는 성질을 만족시키며, 내가 한 말을 상대방이 무조건 들을 수 있음을 확신하고 보낸다.

2. 반면 TCP의 경우, Datagram방식을 사용한다. 즉, 물리적으로 내 정보가 상대방에게 100% 온전히 전달될 것이라고 확신할 수 없다. 때문에, 두 호스트간에는 내가 어떤 데이터를 전달받으면 ACK을 한다는 *Logically*한 약속을 맺어 Connection-Oriented라는 성질을 만족시키게 되는 것이다.

이 글은 수업에서 다룬 내용을 정리한 것이라 다소 올바르지 않은 내용이 담겨있을 수도 있다. 나중에 좀 더 정리가 된다면 글을 수정할 예정이다.
