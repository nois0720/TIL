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

# Binary tree

![binary-tree](/image/binarytree.png)

부모 노드 밑에 자식 노드가 최대 2개밖에 오지 않는 가장 간단한 형태의 트리이다. 두 자식 노드를 보통 왼쪽과 오른쪽 자식으로 구분지으며, 하나의 값과 왼쪽, 오른쪽 자식 노드를 가리킬 두 개의 포인터를 가진 구조로 구현할 수 있다.

Binary tree에는 다음과 같은 종류가 있다.
* Full binary tree : 모든 트리의 자식은 0개 혹은 2개이다.
* perfect binary tree : 모든 리프 노드의 높이가 같다.
* complete binary tree : 모든 리프노드의 높이가 최대 1차이가 나고, 모든 노드의 오른쪽 자식이 있으면 왼쪽 자식이 있는 binary tree이다. 다시 말해서 트리의 원소를 왼쪽에서 오른쪽으로 하나씩 빠짐없이 채워나간 형태이다.

일반적으로 비 선형 구조인 binary tree는 각각의 노드가 자식들의 포인터를 갖도록 구현되지만, complete binary tree의 경우 왼쪽부터 빠짐없이 채워져있다는 성질을 이용해 배열을 사용하여 구현하기도 한다. 1번부터 시작하는 배열을 생각하면 n번째 원소의 왼쪽 자식은 2n, 오른쪽 자식은 2n+1번째 원소로 구성하면 된다. 또 n번째 원소의 부모 노드는 n/2번쨰 원소가 된다.


