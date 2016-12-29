# Tree (트리)

## 정의

Tree는 1개 이상의 노드를 가지는 집합으로, 각각의 노드들은 다음의 조건을 만족한다.

1. Tree에는 루트(root)라는 특별한 노드가 있다.
2. 루트를 제외한 다른 노드들은 원소가 중복되지 않는 n개의 subtree T1, T2, ..., Tn으로 나누어지며 Ti 각각은 루트의 subtree라고 부른다

## 용어

* degree : 노드의 subtree 개수.
* degree of tree : 트리의 최대 degree
* leaf : degree가 0인 노드. 즉 맨 아리애 달린 노드들.
* internal node : 차수가 1이상인 노드
* parent : subtree를 가지는 노드
* child : 부모에 속하는 부속노드
* sibling : 부모가 같은 자식 노드들
* ancestor : 노드들의 부모 노드들의 집합.
* descentant : 노드들의 부속 트리에 있는 모든 노드들
* level : 루트 노드로부터의 깊이 (루트 노드의 레벨은 1이다.)
* depth of tree : 트리에 속한 노드의 최대 레벨
