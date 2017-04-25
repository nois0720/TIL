# chmod

유닉스에서는 모든 것을 파일으로 관리한다. 따라서, 파일에 대한 권한을 다루는 일은 굉장히 중요하다고 할 수 있다. chmod는 change mode의 축약어로 유닉스와 유닉스 계통의 환경 안에서 쓰이는 셸 명령어이다. 이 명령어는 파일 혹은 디렉터리의 파일 시스템 모드를 변경한다.

chmod 명령어는 다음과 같이 사용한다.

```bash
$ chmod [options] mode[,mode] file1 [file2 ...]
```

구체적인 사용법을 알아보기에 앞서, 먼저 mode가 무엇인지 알아보도록 하자. 여기서 mode는 파일에 부여하려는 권한 값을 의미한다.

사실 우리가 쓰고있는 모든 파일에 이러한 권한값이 부여되어 있다. 필자는 /HOME/User 디렉터리에서 다음 명령어를 통해 파일 모드 조회를 해보았다.

```bash
$ ls -l
```

![file-mode-list](/image/file-mode-list.png)
맥북의 /HOME/User/ 디렉터리에서 `ls -l` 명령어를 실행시킨 모습이다. 가장 좌측에 `drwx------` , `drwx------@`, `drwx------+`, `-rw-r--r--`, `-rwxr--r--` 등을 확인할 수 있는데 이는 각 파일에 해당하는 파일 모드이다. 이제 이것들이 각각 무엇을 의미하는지 알아보도록 하자.

## mode

사실 `ls -l` 명령어를 통해 확인한 알 수 없는 10자리의 값은 파일에 대한 권한을 나타낸다. 이 권한 값은 총 10자리로, 이를 네 부분으로 나누어 해석해야 한다. 파일 타입을 나타내는 1자리(file type), 소유자 권한 3자리(user), 그룹 권한 3자리(group), 전체 권한 3자리이다.(other)

## file type

파일 타입에는 다음과 같은 종류가 있다.
* - : plain file (일반 파일을 말한다. 실행 파일도 포함한다.)
* d : directory
* l : link (다른 파일을 링크하는 링크 파일)
* p : pipe (두 개의 프로세스를 연결하는 pipe 파일)
* b : block device (block 단위로 하드웨어와 반응하는 파일)
* c : character device (stream 단위로 하드웨어와 반응하는 파일)

## file permission

앞에서도 살펴봤듯이 파일에는 유저, 그룹, 모든 사용자의 권한을 각각 부여한다. 이 세 권한 그룹을 user, group, other의 첫 문자를 따서 UGO라고 표현하기도 한다.

r, w, x 문자열은 각각 읽기(read), 쓰기(Write), 실행(Execute)를 의미한다. 해당 권한이 있을 경우, 각각을 r, w, x로 표시하며 권한이 없을 경우엔 -로 표시한다.

즉, `ls -l` 명령어를 통해 확인한 `drwx------` file mode를 해석해보자면 이 파일은 d라는 파일 타입이고, 소유자는 파일에 대한 rwx권한을 가지며, group과 other는 ---로 권한이 없다는 것을 알 수 있다.

## 사용 예제

```bash
$ chmod g+x test
$ chmod o-w test
```

첫 번째 명령어는 test 파일에 그룹(g) 실행(x)권한을 추가(+)한다는 명령어이다.  
그리고 두 번째 명령어는 test 파일에 나머지 사용자(o)의 쓰기(w) 권한을 제거(-)한다는 명령어가 된다. 또한 여러 심볼을 묶어서 다음과 같이 권한을 부여할 수도 있다.

```bash
$ chmod u+rwx test				# user에게 rwx 권한 부여
$ chmod ugo+rx test				# user, group, other에 rx 권한 부여
$ chmod u+x, g+rw, o-r test		# user에게 x권한 부여, group에 rw권한 부여, other에 read 권한 제거
```

이러한 synbol을 사용하기 불편하다면, 숫자를 통해 설정할 수도 있다. (`r은 읽기권한(4)`, `w는 쓰기권한(2)`, `x는 실행권한(1)`, `-는 권한 없음(0)`을 나타낸다.) 예를 들면, -rw-rw-r-rr는 664로 읽을 수 있다.

숫자를 이용한 명령어들은 다음과 같다.

```bash
$ chmod 755 test		# test 파일 권한을 rwxr-xr-x로 변경
$ chmod 654 test		# test 파일 권한을 rw-r-xr--로 변경
$ chmod 4 test		# test 파일 권한을 ------r--로 변경 
```

마지막 명령어는 `chmod 004 test` 와 같다.

## option

chmod 명령어는 행동에 영향을 미치는 수많은 명령어 옵션들을 가진다.

* -R : recursive하게 파일들과 디렉터리들의 모드를 변경한다.
