# Tortoise and Hare(토끼와 거북이 알고리즘)

이 알고리즘은 주어진 리스트에 사이클이 있는지 없는지를, 일반적으로는 주어진 함수에서 사이클이 있는지 없는지 알려주는 알고리즘이다. 이 알고리즘은 Floyd(플로이드)라는 사람이 만들었다. (All Shortest Path 알고리즘을 만든 Floyd 맞다.)

문제는 다음과 같다.

![image1](/image/tortoise-and-hare.png)

이러한 링크드 리스트에서 O(n)의 Time Complexity와 O(1)의 저장공간을 이용해서 사이클이 있는지 없는지를 알아내라.

시간과 저장공간에 제약이 없다면, 노드마다 방문되었음을 기억하는 변수를 두고 링크드 리스트를 돌면 된다. 하지만 O(1)의 공간을 이용해야하므로 추가적인 변수를 둘 수 없다.

정답은 토끼와 거북이를 사용하는 것이다.

1. 거북이는 리스트를 한 번에 한 노드씩 이동한다.
2. 토끼는 두 노드씩 이동한다.
3. 링크드리스트의 tail까지 이동하거나 둘이 만날때까지 반복한다.

![step1](/image/th-step1.png)  
![step2](/image/th-step2.png)  
![step3](/image/th-step3.png)  
![step4](/image/th-step4.png)  
