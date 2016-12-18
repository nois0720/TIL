# Deadlock

Deadlock이란 프로세스가 하나의 자원을 점유하고 봉쇄하고(Blocking) 있을 때, 다른 프로세스가 이 자원을 획득하기 위해 요청 후 기다리는 상황을 뜻한다.

## Deadlock Characterization

데드락은 아래의 네 가지 상황이 동시에 모두 만족할 때 발생한다.

1. Mutual exclusion : 한 번에 하나의 프로세스만이 하나의 리소스를 사용한다.
2. Hold and wait : 최소한 하나의 리소스를 가진 프로세스가 다른 프로세스가 가진 리소스를 추가로 얻기 위해 기다린다.
3. No preemption : 리소스는 그 리소스를 가진 프로세스가 자신의 일이 끝난 후에 스스로 리소스를 내려놓아야만 Release가 가능하다.
4. Circular wait : 리소스를 기다리는 프로세스 집합 {P0, P1, P2, ... , Pn}에서, P0는 P1이 점유한 리소스를 기다리고, P1은 P2가 점유한 리소스를 기다리고, ... 와 같이 Cycle이 형성된다.

## Resource Allocation Graph

V(vertex)와 E(edge)의 집합으로 구성된 그래프.

* vertex에는 P(process)와 R(resource)이 있다.
* edge에는 P->R(P이 R의 리소스 인스턴스를 하나 요청) R->P(R의 하나의 인스턴스가 P에 할당)

Resource Allocation Graph에서 cycle이 없으면 Deadlock이 아니며 cycle이 있을 때에는 Cycle을 형성하는 Resource노드 중에서 인스턴스를 여러개 가지고 있는 노드가 있으면 100% Deadlock라고 할 수 없다. 즉 Deadlock의 가능성만 있으며, 모든 Resource 노드의 인스턴스가 1개이면 Deadlock이다.

## Deadlock handling

### 방법
1. 시스템이 절대 Deadlock에 빠지지 않게 한다.(Deadlock Prevention)
2. Deadlock을 허용하고 후에 Recover한다.
3. 데드락을 무시. 시스템에서 문제가 발생하지 않은것처럼 가장.

### Deadlock Prevention

Deadlock Prevention은 Deadlock 발생 조건 4 가지에 대해서 단 하나도 문제가 없도록 만드는 방법이다.
* Mutual Exclusion : 공유 가능한 자원에 대해서는 하지 않고, 공유 불가능한 자원에 대해서 반드시 적용시킨다.
* Hold and wait : 하나의 프로세스가 하나의 자원을 요청할 시에 다른 자원을 점유하지 않도록 보장한다.
	* 각 프로세스가 실행 전에 사용되는 자원을 모두 요청하고, 모두 할당받을것을 요구
	* Resource utilization이 매우 낮다.
	* Starvation 가능성이 있다.
* No preemption
	* 몇 개의 리소스를 가진 프로세스가 있고, 이 프로세스가 필요로 하는 리소스가 즉시 여기에 할당 가능한 리소스가 아니라면 현재 가진 모든 리소스를 내려놓는다. 
	* 내려놓은 리소스를 기다리는 프로세스들의 리소스 리스트에 추가한다.
	* 리소스를 preemption한 프로세스는 요청했던 리소스를 포함해서 이미 점유했었던 예전 리소스들까지 획득 가능할 때 재시작한다.
* Circular wait : 전체에 순서를 부여하여 각 프로세스가 이 순서대로 요청하도록 요구한다.

그래서 이러한 Deadlock Prevention 방법은 전체 utilization을 낮추고 시스템 처리율(throughput)을 감소시킨다.

### Deadlock Avoidance

데드락 발생조건 네 가지 중 적어도 하나를 해결하는 방법이다.

1. 각 프로세스가 필요로 하는 최댓값으로 요청 -> 단순하고 간단한 방법
2. Deadlock Avoidance Algorithm -> 동적으로 현재 자원 할당 상태를 검사한다.
	* 가용 자원 수
	* 할당된 자원 수
	* 프로세스들의 최대 요구 수.

Resource Allocation Graph 이용.
Banker's Algorithm
