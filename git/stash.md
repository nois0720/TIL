# git stash 기능

깃을 사용하다보면 커밋 후에 다른 작업을 수행하는중 코드리뷰가 완료되어 내가 하던 작업을 잠깐 멈추어두고, 마지막 커밋으로 돌아가야하는 경우가 있다. 이러한 경우 유용하게 사용되는 기능이 바로 stash 인데, 오늘은 stash 기능에 대하여 작성해보려고 한다.

`git stash` 명령어를 입력하면 워킹 디렉토리에서 수정한 파일만 따로 저장한다. stash는 Modified이면서 Tracked 상태인 파일과, Staging Area 에 있는 파일들을 보관하는 장소이다. 다시 말해 아직 끝나지 않은 수정사항을 잠시 스택에 저장해두었다가 나중에 다시 불러와 적용시킬 수 있다.

## Stash 사용해보기

git pro의 예제를 보자. 파일을 두 개 수정하였다. 그 중 하나는 Staging area 에 추가한다. 그리고 git status 명령어를 사용하면 아래와 같은 결과를 볼 수 있다.

```bash
$ git status
# On branch master
# Changes to be committed:
#   (use "git reset HEAD <file>..." to unstage)
#
#      modified:   index.html
#
# Changes not staged for commit:
#   (use "git add <file>..." to update what will be committed)
#
#      modified:   lib/simplegit.rb
#
```

이제 브랜치를 변경할 것인데, 아직 작업중인 파일은 커밋하지 않고 *Stash*한다. git stash를 실행하면 스택에 새로운 stash가 만들어진다.

```bash
$ git stash
Saved working directory and index state \
 "WIP on master: 049d078 added the index file"
HEAD is now at 049d078 added the index file
(To restore them type "git stash apply")
```

대신 워킹 디렉토리는 깨끗해졌다..!!

```
git status
# On branch master
nothing to commit, working directory clean
```

stash가 완료된 후에는, 아무 브랜치로 옮겨도 문제가 없다. 수정한 내용은 스택에 저장하였기 때문이다.  
아래와 같이 git stash list를 사용하여 저장한 Stash를 확인할 수 있다.

```bash
$ git stash list
stash@{0}: WIP on master: ******* added the index file
...
```

자 이제 다시 원래 내가 하고있던 작업의 상태로 돌아가보자. git stash apply를 사용하여 stash를 적용할 수 있다. git stash 명령어를 실행하면 이 명령에 대한 도움말을 보여준다.  
다른 stash를 고르고 싶다면 stash 이름을 입력하면 된다. (이름을 입력하지 않은 경우 가장 최근의 stash를 적용시킨다)  

```bash
$ git stash apply
# On branch master
# Changes not staged for commit:
#   (use "git add <file>..." to update what will be committed)
#
#      modified:   index.html
#      modified:   lib/simplegit.rb
#
```

