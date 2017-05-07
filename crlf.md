# CR(Carraiage Return)과 LF(Line Feed)

깃을 통해 협업을 하다보면 다음과 같은 메시지를 마주칠 때가 있다. 사실 이러한 워닝 메시지는 진짜 많이 보았는데, 이제야 찾아보게 되었다.

``` bash
$ git add -A
warning:LF will be replaced by CRLF in 'file-name'
The file will have its original line endings in your working directory
```

CL과 LF는 줄바꿈을 의미하는 컨트롤 캐릭터로, 각각 다른 아스키 코드값을 가진다.

* Line Feed (LF) : 아스키코드는 `0x0A`. 커서를 현재 행의 다음 행으로, 즉 아래로 내리기.
* Carrage Return (CR) : 아스키코드는 `0x0D`. 커서를 현재 행의 맨 좌측으로 옮기기.

그런데, 윈도우는 CRLF를, 유닉스는 LF을 사용한다고 한다. 그래서 협업 시 동료간 작업 플랫폼이 다를 때에는 이러한 줄바꿈 문자가 달라질 수 있고, 만약 해당 프로젝트가 크로스 플랫폼을 서비스한다면 꽤 문제가 될 수 있다.

따라서 깃에서는 (윈도우 기준) 커밋할 때 CRLF를 자동으로 LF로 변환해주고, 반대로 Checkout할 때 LF를 CRLF로 변환해주는 옵션을 core.autocrlf를 true로 설정하여 사용할 수 있다.

```bash
$ git config --global core.autocrlf true
```

줄 바꿈 문자로 LF를 사용하는 Linux와 Mac에서는 Checkout할 때 Git이 LF를 CRLF로 변환할 필요가 없다. 게다가 우연히 CRLF가 들어간 파일이 저장소에 들어 있어도 Git이 알아서 고쳐주면 좋을 것이다. core.autocrlf 값을 input으로 설정하면 커밋할 때만 CRLF를 LF로 변환한다:

```bash
$ git config --global core.autocrlf input
```
이 설정을 이용하면 윈도에서는 CRLF를 사용하고 Mac, Linux, 저장소에서는 LF를 사용할 수 있다.

윈도 플랫폼에서만 개발하면 이 기능이 필요 없다. 이 옵션을 false라고 설정하면 이 기능이 꺼지고 CR 문자도 저장소에도 저장된다:

```bash
$ git config --global core.autocrlf false
core.whitespace
```
Git에는 공백 문자를 다루는 방법으로 네 가지가 미리 정의돼 있다. 두 가지는 기본적으로 켜져 있지만 끌 수 있고 나머지 두 가지는 꺼져 있지만 켤 수 있다.

먼저 기본적으로 켜져 있는 것을 살펴보자. trailing-space는 각 줄 끝에 공백이 있는지 찾고 space-before-tab은 모든 줄 처음에 tab보다 공백이 먼저 나오는지 찾는다.

기본적으로 꺼져 있는 나머지 두 개는 indent-with-non-tab과 cr-at-eol이다. intent-with-non-tab은 tab이 아니라 공백 8자 이상으로 시작하는 줄이 있는지 찾고 cr-at-eol은 줄 끝에 CR 문자가 있어도 괜찮다고 Git에 알리는 것이다.

core.whitespace 옵션으로 이 네 가지 방법을 켜고 끌 수 있다. 설정에서 해당 옵션을 빼버리거나 이름이 -로 시작하면 기능이 꺼진다. 예를 들어
, 다른 건 다 켜고 cr-at-eol 옵션만 끄려면 아래와 같이 설정한다:

```
$ git config --global core.whitespace \
		trailing-space,space-before-tab,indent-with-non-tab
```

git diff 명령을 실행하면 Git은 이 설정에 따라 검사해서 컬러로 표시해준다. 그래서 좀 더 쉽게 검토해서 커밋할 수 있다. git apply 명령으로 Patch를 적용할 때도 이 설정을 이용할 수 있다. 아래처럼 명령어를 실행하면 해당 Patch가 공백문자 정책에 들어맞는지 확인할 수 있다:

```bash
$ git apply --whitespace=warn <patch>
```

아니면 Git이 자동으로 고치도록 할 수 있다:

```bash
$ git apply --whitespace=fix <patch>
```

이 옵션은 git rebase 명령에서도 사용할 수 있다. 공백 문제가 있는 커밋을 서버로 Push하기 전에 --whitespace=fix 옵션을 주고 Rebase하면 Git은 다시 Patch를 적용하면서 공백을 설정한 대로 고친다.
