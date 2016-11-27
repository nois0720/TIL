git의 태그
깃의 태그는 보통 릴리즈(버전)를 위해 사용한다.



깃의 태그는 LightWeight, annotated 두 가지 태그가 있음. 

Lightweight태그는 특정 커밋에 대한 포인터로 브랜치와 비슷하지만 브랜치처럼 가리키는 지점을 최신 커밋으로 이동시키지는 않는다.

Annotated 태그는 Git 데이터베이스에 태그를 만든 사람의 이름, 이메일과 태그를 만든 날짜, 그리고 태그 메시지도 저장한다. 또 GPG(GNU Privacy Guard)로 서명할 수도 있다.

위에서 서술한 모든 정보를 저장해둬야 할 때에만 Annotated 태그를 추천한다. 그냥 다른 정보를 저장하지 않는 단순한 태그가 필요하다면 Lightweight 태그를 사용하는 것이 좋다.


Annotated 태그
Annotated 태그를 만드는 방법 :  tag 명령을 실행할 때 -a 옵션을 추가한다.
$ git tag -a v1.4 -m 'my version 1.4'
-m 옵션으로 태그를 저장할 때 메시지를 함께 저장할 수 있다. 명령을 실행할 때 메시지를 입력하지 않으면 Git은 편집기를 실행시킨다.

GPG 개인키가 있으면 태그에 서명할 수 있다. 이때에는 -a옵션 대신 -s를 사용한다.

$ git tag -s v1.5 -m 'my signed 1.5 tag'

git show 명령으로 태그 정보와 커밋 정보, GPG서명 등을 모두 확인할 수 있다.



Lightweight 태그
Lightweight 태그는 기본적으로 파일에 커밋 체크섬을 저장하고 다른 정보는 저장하지 않는다. Lightweight 태그를 만들 때에는 -a, -s, -m 옵션을 사용하지 않는다

이 태그에 git show를 실행하면 별도의 태그 정보를 확인할 수 없다. 이 명령은 단순히 커밋 정보만을 보여준다:



물론 예전 커밋에 대해서도 태그할 수 있다. 

$ git log --pretty=oneline
15027957951b64cf874c3557a0f3547bd83b3ff6 Merge branch 'experiment'
a6b4c97498bd301d84096da251c98a07c7723e65 beginning write support
0d52aaab4479697da7686c15f77a3d64d9165190 one more thing
6d52a271eda8725415634dd79daabbc4d9b6008e Merge branch 'experiment'
0b7434d86859cc7b8c3d5e1dddfed66ff742fcbc added a commit function
4682c3261057305bdd616e23b64b0857d832627b added a todo file
166ae0c4d3f420721acbb115cc33848dfcc2121a started write support
9fceb02d0ae598e95dc970b74767f19372d61af8 updated rakefile
964f16d36dfccde844893cac5b347e7b3d44abbc commit the todo
8a5cbc430f1a9c3d00faaeffd07798508422908a updated readme

"updated rakefile" 커밋을 v1.2로 태그하지 못했다고 해도 차후에 태그를 붙일 수 있다. 특정 커밋에 태그하기 위해서 명령의 끝에 커밋 체크섬을 명시한다(긴 체크섬을 전부 사용할 필요는 없다)

$ git tag -a v1.2 -m 'version 1.2' 9fceb02

git tag 명령으로 생성한 태그 리스트를 볼 수 있음.
