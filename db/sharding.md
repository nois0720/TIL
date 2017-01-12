# DB Sharding

## 의미
`Shard`의 사전적 의미는 'a small part of a whole', 우리말로 '전체의 작은 한 부분. 즉 조각'이라는 뜻이다. Sharding은 많은 양의 데이터를 처리하기 위해서 하나의 데이터베이스가 아니라 여러 개의 데이터베이스에 데이터를 분할하는 기술이다. 분할된 각각의 데이터베이스는 `샤드(Shard)` 혹은 `데이터베이스 샤드(Database shard)`라고 부르며, 부하의 분산을 위해서 서로 다른 db서버에 저장된다. (즉, 데이터베이스 자체를 분할한다.)

## 파티셔닝과 샤딩
`파티셔닝(Partitioning)`은 성능과 utilization, 그리고 용이한 관리를 위해 데이터를 서로 다른 테이블 혹은 DB로 분산하는 것을 말한다. 파티셔닝에는 `Vertical Partitioning`과 `Horizontal Partitioning`이 있다.

!(partitioning)[/image/db-partitioning.png]

`Vertical Partitioning`은 하나의 데이터를 스키마 단위로 나누어 여러 테이블 혹은 데이터베이스에 저장하는 방식이다. 예를 들면, id, name, address로 구성된 고객 정보를 id를 참조하도록 하여 name과 address 테이블로 나누어 저장할 수 있다.

`Horizontal Partitioning`은 스키마가 같은 데이터를 여러 테이블에 나누어 저장하는 방식이다. 예를 들면, 고객 정보를 id에 따라 0 ~ 10000번 고객까지는 테이블 A에, 10001 ~ 20000번까지는 테이블 B에 저장하는 방법이 있다. 보통 `Horizontal Partitioning`을 한다고 하면 하나의 데이터베이스 안에서 이루어지는 경우를 말한다. 반면, `Sharding`은 다른 데이터베이스에 데이터를 `Horizontal Partitioning`하는 방법을 사용한다.

## Sharding 종류
`Sharding`을 위해서, 데이터를 분산하기 위한 `Shard key`를 정해야하고, 이러한 `Shard key`에 따라 데이터가 어떻게 분산될 지 결정된다. 같은 `Shard key`를 가지는 데이터는 같은 `노드`에 저장된다.

### 1. Algorithmic Sharding
Key(Hash) based partitioning이라고도 한다. 이 방식은 데이터의 특정 속성을 함수에 넣어 나오는 값을 이용하여 데이터가 저장될 서버를 선택한다. 이러한 hash-function으로 Shard key를 만들고 이 키값에 따라 데이터를 저장하므로 hash-function을 잘 정의해야 데이터를 균등하게 나눌 수 있다는 단점이 있다. 또한 서버의 갯수를 늘릴 때 데이터를 재분배하는 과정에서 오버헤드가 크다는 단점이 있다.

### 2. Dynamic Sharding
Range based partitioning이라고도 한다. 이 방식은 데이터의 특정 속성 범위에 따라 저장될 서버를 정한다. 예를 들면 유저 정보를 저장할 때, 가입년도 혹은 id의 범위에 따라 다른 데이터베이스에 저장하는 방법이 있다. 

두 방법은 모두 데이터베이스에서 데이터에 접근할 때 shard key가 있으면 해당 데이터베이스만 찾아가면 되지만 shard key가 없으면 모든 데이터베이스를 탐색해야만 한다.
