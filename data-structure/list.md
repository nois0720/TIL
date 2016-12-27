# List (리스트)

List는 데이터의 목록을 다루는 비교적 단순한 자료구조이다. 리스트는 구조가 단순하면서도 가장 널리 쓰이며 리스트는 다른 자료구조를 이해하는데 기초를 제공한다. 리스트는 데이터를 순차적으로 저장하며, 이 때문에 선형(linear)한 구조를 띈다. 데이터가 순차적으로 저장되기 때문에, 마치 선과 같은 구조를 보여준다. 

linked list에는 singly linked list, doubly linked list, circular linked list의 세 가지가 있다.

## 1. singly linked list

singly linked list는 Node로 구성되어 있다. 이 노드는, 데이터와 포인터를 가지는데, 데이터는 말 그대로 데이터 필드를 말하고, 포인터는 다음 노드를 가리키는 포인터를 말한다.

```java
class Node {
	int value; // 데이터 필드
	Node next; // 다음 노드
}
```

## doubly linked list

singly linked list는 단순히 다음 노드에 대한 포인터만 가지기 때문에, head로부터 tail까지 단방향으로만 탐색할 수 있다. 하지만 doubly linked list는 다음 노드인 next 뿐만 아니라, 이전의 노드에 해당하는 prev노드 또한 가진다. 따라서 양방향 탐색이 가능하고 때문에 검색 속도를 향상시킬 수 있다.

```java
class Node {
	int value; // 데이터 필드
	Node prev; // 이전 노드 
	Node next; // 다음 노
}
```

## circular linked list

circular linked list는 tail의 next가 head가 되는. 즉, cycle을 형성하는 linked list를 말한다. circualr linked list도 역시 singly circular linked list와 doubly circular linked list의 두 가지가 있다.
