# nano

Debian 계열에서는 nano를 이용하여 텍스트 파일이나 프로그램 파일을 작성하고 편집하는 경우가 많은데, 처음에 nano를 사용할 때에는 vi(vim)인줄 알았다가 vi의 기능을 사용할 수 없어 당황한 기억이 있다. nano의 경우 이번에 라즈베리파이를 만지면서 다시 사용하게 되어 정리해보게 되었다.

## 사용법

편집 모드에서는 기본적으로 상하좌우 방향키로 caret을 이동시킬 수 있고, delete, backspace, enter키를 사용할 수 있고, ctrl+g의 조합키를 사용하여 도움말을 볼 수도 있다.

#### 기본 명령어

명령어 | 행동
ctrl + g (F1) | Help
ctrl + x (F2) | nano 종료. 혹은 현재의 file buffer를 닫음.
ctrl + o (F3) | 현재 파일 저장
ctrl + j (F4) | 문단의 행 끝을 나란하게 한다.
ctrl + r (F5) | 현재 파일에 다른 파일 내용 추가
ctrl + w (F6) | search
ctrl + c (F11) | 현재 커서위치 표시
ctrl + t (F12) | spell check
ctrl + \  | search and replace

#### 편집 명령어

명령어 | 행동
ctrl + k (F9) | 현재 line 혹은 선택된 text 삭제. (vi와 마찬가지로 copy가 동시에 일어난다.)
ctrl + u (F10) | 붙여넣기
ctrl + 6 | 현재 cursor위치로부터 text 선택 시작. (vim의 visual모드와 비슷.) 이후 `alt + 6` 을 통해 복사하고 선택 종료. 혹은 다시 `ctrl + 6` 을 입력하여 행동 취소.
alt + 6 | 선택 구간 복사. 선택된 구간이 없으면 현재 caret이 있는 한 줄 복사. 이후 `ctrl + u` 를 통해 붙여넣기.

#### 화면 이동 명령어

명령어 | 행동
PageUp or ctrl + y (F7) | page up
PageDown or ctrl + v (F8) | page down 
alt + ( | 현재 문단의 시작점으로 이동.
alt + ) | 현재 문단의 끝으로 이동.
alt + = | 한 줄 밑으로 이동.
alt + - | 한 줄 위로 이동.
ctrl + space | 한 단어 앞으로 이동
alt + space | 한 단어 뒤로 이동
alt + \ | file의 첫 line으로 이동
alt + / | file의 마지막 line으로 이동
alt + ] | 현재 괄호에 매치되는 괄호 검색
ctrl + - | 행과 열을 입력. 해당 위치로 이동
