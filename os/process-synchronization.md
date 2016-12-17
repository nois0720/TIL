# Process Synchronization

## CPU Scheduler

Short-term 스케쥴러는 Ready-Queue에 있는 프로세스 사이에서 CPU를 할당할 프로세스를 선택한다.

CPU scheduling 결정은 아래의 네 가지 상황에서 발생한다.
1. running에서 waiting state로의 변경
2. running에서 ready state로의 변경
3. waiting에서 ready로의 변경
4. terminate

1, 4번은 non-preemptive이고 2, 3번은 preemptive이다. preemptive의 경우 shared data, kernel mode에서의 preemption, 중요한 운영 체제 활동 중에 발생하는 인터럽트 고려해야 한다.

## Dispatcher

Dispatcher 모듈은 Short-term에 의해 선택된 프로세스에 대해 CPU를 컨트롤한다. 이것은 context switching, user mode로의 변경, 해당 프로그램을 다시 시작하기 위해 사용자 프로그램의 적절한 위치로 이동 들을 포함한다.

#### Dispatch latency : dispatcher가 하나의 프로세스를 멈추고, 다른 프로세스를 시작하기 위해 걸리는 시간을 말한다.

## Scheduling Criteria(스케쥴링 성능 분석 요소들)

* CPU utilization : CPU가 최대한 바쁘게 유지되도록 해야한다.
* Throughput : 시간 단위 당 실행을 완료한 프로세스 수.
* Turnaround time : 특정 프로세스를 실행하는데 걸린 시간.
* Waiting time : 프로세스가 Ready queue내에서 기다린 시간의 양
* Response time : 요청이 전송된 후 첫 번째 응답이 생성될 때까지 걸리는 시간 (Time-sharing의 경우)

## Scheduling Algorithm 


