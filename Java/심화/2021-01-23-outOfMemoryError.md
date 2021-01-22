# OutOfMemeryError 메모리 누수

`OutOfMemoryError`는 메모리 누수 상황이 발생했을 떄 일어난다. 자바는 객체를 힙공간에 생성하고, 이 생성위치에 대한 주소를 가지고 객체 참조를 한다. 이 오류는 힙 공간에 객체를 할당하기 위한 공간이 부족한 경우 발생하는데 `OutOfMemoryError`의 종류 및 원인에 대해서 살펴볼 것이다.


## java.lang.OutOfMemoryError: Java heap space

### 원인

**자바 힘 공간에 새로운 객체를 생성할 수 없는 경우 발생**한다. 이 오류가 반드시 메모리 누수를 의미하는 것은 아니다. 지정한 힙 크기가 애플리케이션에 충분하지 않은 경우에도 발생한다.
혹은 `finalize`를 과도하게 사용하는 애플리케이션에서 발생하기도 한다. 클래스에 `finalize` 메서드가 있는 경우 해당 객체에 대한 GC 공간을 확보하지 못한다. `finalizer` 큐를 처리하는 속도보다 빠른 속도로 쌓이면서 힘 공간이 가득차 발생할 수 있다.

### 해결

`finalization` 보류 상태의 객체를 모니터링하는 방법을 고려해야한다.


## java.lang.OutOfMemoryError: GC Overhead limit exceeded

### 원인

이 예외는 일반적으로 데이터를 할당하는데 필요한 공간이 힙에 없는 경우 발생한다.

### 해결

- 힙 공간을 늘린다.
- `-XX:-UseGCOverheadLimit` 선택사항을 추가하여 `java.lang.OutOfMemoryError` 가 발생하는 초과 오버헤드 GC 제한 명령을 해제할 수 있다.

## java.lang.OutOfMemoryError: Requested array size exceeds VM limit

### 원인

애플리케이션이 힙 공간보다 큰 배열을 할당 시도하는 경우 발생한다. 예를들어 512MB크기의 배열을 할당하려하지만, 힙의 최대크기가 256MB인 경우 요청 배열크기가 VM제한을 초과하면서 해당 오류를 발생시킨다.

- 힙 사이즈가 너무 작은 경우
- 배열의 크기가 커지는 경우

## java.lang.OutOfMemoryError: Metaspace

### 원인

자바 클래스 메타데이터는 원시 메모리에 할당된다. 클래스 메타데이터가 할당될 메타공간이 모두 소멸되면 해당 오류가 발생한다.

### 해결

`MaxMetaSpaceSize` 값을 늘려 해결할 수 있다. `MaxMetaSpaceSize`는 자바 힙과 동일한 주소 공간에 할당되며, 자바 힙의 크기를 줄이면 더 많은 공간을 확보할 수 있다. 즉, 자바 힙 공간에 여유가 있는 경우에 고려해볼 수 있다.

1. 하나의 프로세스 당 사용가능 메모리는 4G
2. 이 최대 메모리 안에서 heap영역, perm영역, native heap영역, stack영역을 설정
3. user가 설정할 수 있는 옵션은 heap영역과 perm영역
4. 그 이외 영역은 3번에서 설정한 크기를 제외한 공간에 적절하게 설정된

즉, heap영역과 perm영역을 과하게 설정하면, native영역과 stack영역이 적은 공간으로 설정되어 이 두 영역의 공간부족에러가 발생 할 수도 있다.


## java.lang.OutOfMemoryError: request size bytes for reason. Out of swap space?

### 원인

자바 HotSpot VM 코드가 Native Heap이 고갈되에 할당할 수 없는 경우에 발생한다. 이 오류의 경우 실패한 요청의 크기(byte)와 메모리 요청의 이유를 나타내며, 주로 소스 모듈의 이름을 출력한다.


### 해결

Native Heap 고갈의 경우는 힙 메모리 로그 및 메모리 맵 정보를 분석하는 것이 유용하며, 운영체제의 문제 해결 유틸리티를 사용해 문제를 진단할 수 있다.

- [Fetal Error Log](https://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/felog.html#fatal_error_log_vm)
- [운영체제 분석 도구](https://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/tooldescr020.html#BABBHHIE)

## java.lang.OutOfMemoryError: Compressed class space

### 원인

64bit 플랫폼에서 클래스 메타데이터 포인터는 32bit 오프셋으로 표현되는데, 이 방식은 `UseCompressedClassPointers`로 제어할 수 있다. `UseCompressedClassPointers`가 활성화되면 클래스 메타데이터가 사용할 수 있는 공간의 크기가 고정되고, `CompressedClassSpaceSize` 공간을 초과하면 오류가 발생한다.

### 해결

`CompressedClassSpaceSize`의 크기를 늘리거나 `UseCompressedClassPointers`를 비활성화 시켜 해결할 수 있다.

### 오류 발생시켜보기

`-XX:CompressedClassSpaceSize=4g` 설정한 후 실행하면 다음과 같은 메세지를 볼 수 있다.

```
CompressedClassSpaceSize of 4294967296 is invalid; must be between 1048576 and 3221225472.
```

## java.lang.OutOfMemoryError: reason stack_trace_with_native_method

### 원인

네이티브 메서드에 할당 오류가 발생한 경우이다. 이 오류 메세지는 JVM코드가 아닌 JNI(Java Native Interface) 또는 원시메서드에서 할당 실패가 감지된 것이다.

### 해결

- [운영체제 분석 도구](https://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/tooldescr020.html#BABBHHIE)를 이용해 문제점을 진단하고 파악해야한다.

## 참고

- [https://m.blog.naver.com/PostView.nhn?blogId=selenitte&logNo=220481440393&proxyReferer=https:%2F%2Fwww.google.com%2F](https://m.blog.naver.com/PostView.nhn?blogId=selenitte&logNo=220481440393&proxyReferer=https:%2F%2Fwww.google.com%2F)
- [http://honeymon.io/tech/2019/05/30/java-memory-leak-analysis.html](http://honeymon.io/tech/2019/05/30/java-memory-leak-analysis.html)