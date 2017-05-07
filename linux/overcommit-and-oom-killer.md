# Overcommit

linux에서는 **overcommit** 이라는 메모리 관리 메커니즘이 존재한다. overcommmit을 사용하면 실제 메모리 공간 이상의 공간을 확보하는 것

# OOM(Out of memory) Killer

사실 이 친구의 존재는 올해 초 한 회사에서 인턴을 할 때 처음 알게 되었다. 당시에는 직접적인 영향을 받은 것은 아니라서 그냥 넘어갔었는데, 이번에 ELK Stack을 활용한 간단한 프로젝트를 하면서 OOM Killer가 servier process를 죽이는 문제가 발생했고, 이를 해결하면서 더 알아보게 되었다.

먼저 OOM Killer란 메모리가 부족할 때 vimtim을 설정하는 알고리즘을 선택하여 해당 프로세스를 kill하여 메모리를 확보하는 것을 말한다. [여기](http://www.win.tue.nl/~aeb/linux/lk/lk-9.html#ss9.6)에는 linux의 [Overcommit](http://)과 OOM killer에 대한 이야기를 서술하고 있다.
