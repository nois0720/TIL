# webpack & HTTP/2

전에 HTTP2가 무조건 좋다는 식으로 말했었는데 아닌듯. 나중에 이거 찾아봐야겠다.

HTTP/2에서는 멀티플렉싱을 제공하므로 여러 요청을 하나의 커넥션에서 처리해 줄 수 있어서 웹팩 등으로 파일을 하나로 합치지 않아도 될 것 같지만 실제로 현실에서는 좋은 성능을 얻기가 어렵다. 이글에서는 AggressiveSplittingPlugin으로 정적파일로 가장 성능 좋은 청크로 나누어서 번들링하는 방법에 관해서 설명하고 있다. AggressiveSplittingPlugin은 아직 실험 상태이다.(영어)
