# nn
Neural Network





## 개발 이슈

### MNIST 파일

- 파일형식 참고사이트 [여기](<http://daddynkidsmakers.blogspot.com/2017/06/hello-world-mnist.html>)
- MNIST 파일의 sizeOfImage/label 부분이 MST형식으로 저장되어 있기 때문에 읽어올 때 형식에 맞게 읽어와야함 : 플랫폼마다 파일 읽어오는 방식이 다르진 않을거 같은데 잘 모르겠다.
- 파일 읽는 부분에서 한번 읽을때마다 콜백 함수 호출하는 식으로 구현해서 파일 내용을 메모리에 올리지 않으려고 하는데 괜찮은지 확신이 들진 않는다.
- unsigned byte나 32bit integer를 플랫폼 종속적이지 않게 하는 자료형이 무엇일까?