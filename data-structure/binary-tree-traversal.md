# Binary Tree Traversal

Binary Tree을 Traversal(순회)하는 몇 가지 방법이 있다. 

![tree](/image/tree.png)

이러한 트리가 있다고 하자. 여기서 왼쪽 자식 노드를 L, 현재 노드를 N, 오른쪽 자식 노드를 R이라고 하면 총 3! = 6. 즉 여섯가지의 방문 순서가 생긴다. LNR, LRN, ...

여기서 사용하는 방법은 3가지 정도로 LNR(inorder), NLR(preorder), postorder(LRN)이다.

## preorder traversal(전위 순회)

![preorder](/image/preorder-traversal.png)

그림과 같이, preorder traversal은 루트 노드로부터 다음과 같은 방법을 반복하여 노드들을 방문한다. 

1. 노드를 방문한다.
2. 현재 노드에서 왼쪽 서브트리를 preorder traversal한다.
3. 현재 노드에서 오른쪽 서브트리를 preorder traversal한다.

따라서 방문 순서는 F-B-A-D-C-E-G-I-H이다. 이는 루트의 왼쪽에서 트리 전체를 따라 쭉 한바퀴 돈다고 생각했을 때, 노드의 왼쪽에 닿았을 때의 방문 순서와 일치한다.

## inorder traversal(중위 순회)

![inorder](/image/inorder-traversal.png)

inorder traversal은 루트 노드로부터 다음과 같은 방법을 반복하여 노드들을 방문한다. 

1. 현재 노드에서 왼쪽 서브트리를 inorder traversal한다. 
2. 노드를 방문한다..
3. 현재 노드에서 오른쪽 서브트리를 inorder traversal한다.

따라서 방문 순서는 A-B-C-D-E-F-G-H-I이다. 이는 루트의 왼쪽에서 트리 전체를 따라 쭉 한바퀴 돈다고 생각했을 때, 노드의 아래에 닿았을 때의 방문 순서와 일치한다.

## postorder traversal(postorder traversal)

![postorder](/image/postorder-traversal.png)

postorder traversal은 루트 노드로부터 다음과 같은 방법을 반복하여 노드들을 방문한다. 

1. 현재 노드에서 왼쪽 서브트리를 preorder traversal한다.
2. 현재 노드에서 오른쪽 서브트리를 preorder traversal한다.
3. 노드를 방문한다.

따라서 방문 순서는 A-C-E-D-B-H-I-G-F이다. 이는 루트의 왼쪽에서 트리 전체를 따라 쭉 한바퀴 돈다고 생각했을 때, 노드의 오른쪽에 닿았을 때의 방문 순서와 일치한다.

그래서 각각의 traversal을 코드로 나타내면 다음과 같다.

```java
void traversal(node) {
	if(node) {
		//visit(node); preorder
		traversal(node.left);
		//visit(node); inorder
		traversal(node.right);
		//visit(node); postorder
	}
}
```

이러한 코드로 기억해 두면 의미상으로 이해하기도 쉽다.
