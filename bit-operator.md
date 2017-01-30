# bit operator

비트 연산자에 대한 내용은 아주 오래전에 배웠지만 당시에는 비트 연산자가 어디에서 어떻게 활용되는지는 감을 잡기 힘들었는데, 실제 어떻게 활용되는지 궁금해서 찾아보게 되었다.

## 시프트 연산자 활용

```java
...
int color;
int r;
int g;
int b;

color = Math.random() * 0xFFFFFF; // 무작위 색
r = Math.random() * 0xFF;
g = Math.random() * 0xFF;
b = Math.random() * 0xFF;
color = r << 16 | g << 8 | b; // 8비트씩 R,G,B값 할당.
...
```

이렇게 rgb값을 각각 나누었으므로 red값만 바꾼다거나 하는 일이 쉬워진다. 따라서 이런 비트 연산자는 비트를 나누어야 하는 경우에 응용할 수 있다.
