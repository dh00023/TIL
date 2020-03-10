# 12. 멀티 스레드

## 개념

### 프로세스와 스레드

- **프로세스** : 운영체제에서 실행 중인 하나의 애플리케이션

사용자가 애플리케이션을 실행하면 운영체제로부터 실행에 필요한 메모리를 할당받아 애플리케이션 코드를 실행하는데 이것을 프로세스라한다. 하나의 애필리케이션은 다중 프로세스를 만들기도 한다.

예를들어 Chrome 브라우저를 두개 실행하면 두 개의 Chrome 프로세스가 생성된 것이다.

- 멀티 태스킹(multi tasking) : 두 가지 이상의 작업을 동시에 처리하는 것

운영체제는 멀티 태스킹을 할 수 있도록 CPU 및 메모리 자원을 프로세스마다 적절하게 할당해주고, 병렬로 실행시킨다. 멀티 태스킹은 꼭 멀티 프로세스를 의미하지는 않는다. 한 프로세스 내에서도 멀티 태스킹을 할 수 있다. 예) 메신저 - 파일전송, 채팅 기능 동시 수행

- **멀티 스레드**(multi thread) : 하나의 프로세스 내에서의 멀티 태스킹

![](http://www.cs.fsu.edu/~baker/opsys/notes/graphics/F4-1.jpg)

**멀티 프로세스**는 운영체제에서 할당받은 자신의 메모리를 가지고 실행하기 때문에 **서로 독립적**이다. 따라서 하나의 프로세스에서 오류가 발생해도 다른 프로세스에 영향을 미치지 않는다.

**멀티 스레드는 하나의 프로세스 내부에 생성**되기 때문에 하나의 스레드가 예외를 발생시키면 프로세스가 종료될 수 있어 **다른 스레드에 영향**을 미친다. 그렇기 때문에 멀티 스레드에서는 예외처리를 신경써야한다.

## 메인 스레드

모든 자바 애플리케이션은 메인 스레드(main thread)가 `main()` 메소드를 실행하면서 시작된다. 메인 스레드는 main() 메소드의 첫 코드부터 아래로 순차적으로 실행하고,main()의 마지막 코드를 실행하거나 return 문을 만나면 종료된다.

![](http://cfile24.uf.tistory.com/image/276DB934566B8EEE0310E7)

**메인 스레드는 필요에 따라 작업 스레드를 생성해 병렬로 코드를 실행할 수 있다.** 즉, 멀티 스레드를 생성해 멀티 태스킹을 수행한다. 싱글 스레드 어플리케이션에서는 메인 스레드가 종료되면 프로세스도 종료된다. 하지만 멀티 스레드 애플리케이션에서는 실행 중인 스레드가 하나라도 있다면, 프로세스는 종료되지 않는다.

## 작업 스레드 생성과 실행

멀티 스레드로 실행하는 애플리케이션을 개발하려면 먼저 몇 개의 작업을 병렬로 실행할지 결정하고, 각 작업별로 스레드를 생성해야한다. 자바에서는 **작업 스레드로 객체로 생성**되기 때문에 클래스가 필요하다.

- java.lang.Thread 클래스를 직접 객체화해서 생성
- Thread를 상속해 하위 클래스로 생성

### Thread 클래스로부터 직접 생성

java.lang.Thread 클래스를 직접 객체화해서 생성하려면 **Runnable** 을 매개값으로 갖는 생성자를 호출해야한다.

```java
Thread thread = new Thread(Runnable target);
```

Runnable은 작업 스레드가 실행할 수 있는 코드를 가지고 있는 객체라고 해서 붙여진 이름이다. Runnable은 인터페이스 타입이기 때문에 구현 객체를 만들어서 대입해야한다. **Runnable은 인터페이스 타입**이므로 구현 객체를 만들어야한다. Runnable 에는 run() 메소드가 정의되어있다.

```java
class Task implements Runnable{
	@Override
    public void run(){
        // 스레드가 실행할 코드;
    }
}
```

```java
Runnable task = new Task();
Thread thread = new Thread(task);
```

Runnable은 작업 내용을 가지고 있는 객체이지 실제 스레드는 아니다. 그러므로 Runnable 구현 객체를 생성한 후에 이것을 매개값으로 해서 Thread 생성자를 호출하면 작업 스레드가 생성된다.

```java
Thread thread = new Thread(new Runnable(){
    public void run(){
        //스레드가 실행할 코드;
    }
});
```

오히려 이 방법이 더 많이 사용된다.

```java
Thread thread = new Thread(()->{
        //스레드가 실행할 코드;
});
```

 Runnable 인터페이스는  run()메소드 하나만 정의 되어있기 때문에 함수적 인터페이스이다. 따라서 다음과 같이 람다식을 매개값으로 사용할 수 있다.(자바 8부터 지원)



작업 스레드는 생성되는 즉시 실행되지 않는다. **start()** 메소드를 호출해야만 실행된다.

```java
thread.start();
```



#### 예제

0.5 초 주기로 beep음을 발생시키면서 동시에 프린팅하는 작업

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Toolkit tk = Toolkit.getDefaultToolkit();
		for(int i=0;i<5;i++) {
			tk.beep();
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
		}
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				// 0.5초마다 비프음 발생
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
		}
	}
}
```

이렇게 하는 경우 Beep음이 발생한 후 "띵"이라는 글자가 print 된다. 동시에 작업을 하려면 두 작업중 한개를 메인 스레드가 아닌 다른 스레드에서 실행시켜줘야한다.

- 방법1

```java
package chap12;

import java.awt.Toolkit;

public class BeepTask implements Runnable {

	@Override
	public void run() {
		// TODO Auto-generated method stub
		Toolkit tk = Toolkit.getDefaultToolkit();
		for(int i=0;i<5;i++) {
			tk.beep();
			try {
				// 0.5초마다 비프음 발생
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
		}
	}

}
```

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Runnable beepTask = new BeepTask();
		Thread thread = new Thread(beepTask);
		thread.start();
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
		}
	}

}
```

- 방법2

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {
		Thread thread = new Thread(new Runnable() {
			@Override
			public void run() {
				Toolkit tk = Toolkit.getDefaultToolkit();
				for(int i=0;i<5;i++) {
					tk.beep();
					try {
						Thread.sleep(500);
					} catch (Exception e) {
					}
				}
			}
		});
		thread.start();
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				Thread.sleep(500);
			} catch (Exception e) {
			}
			
		}
	}

}
```

- 방법3

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {

		Thread thread = new Thread(()-> {
			Toolkit tk = Toolkit.getDefaultToolkit();
			for(int i=0;i<5;i++) {
				tk.beep();
				try {
					Thread.sleep(500);
				} catch (Exception e) {
				}
			}
		});

		thread.start();
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
		}
	}

}

```

### Thread 하위 클래스로부터 생성

작업 스레드가 실행할 작업을 Runnable로 만들지 않고, Thread 하위 클래스로 작업 스레드를 정의하면서 작업 내용을 포함할 수 있다.

```java
public class TaskThread extends Thread{
    @Override
    public void run(){
        // 스레드가 실행할 코드
    }
}
Thread thread = new TaskThread();
```

코드를 절약하기 위해서 익명객체로 작업 스레드 객체를 생성할 수 있다.

```java
Thread thread = new Thread(){
    public void run(){
        //스레드가 실행할 코드
    }
}
```

이렇게 생성한 스레드에 `.start()` 를 해주면 작업 스레드는 자신의 run() 메소드를 실행한다.

#### 예제

```java
package chap12;

import java.awt.Toolkit;

public class BeepThread extends Thread{
	@Override
	public void run() {
		// TODO Auto-generated method stub
		Toolkit tk = Toolkit.getDefaultToolkit();
		for(int i=0;i<5;i++) {
			tk.beep();
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
		}
	}
}

```

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {

		Thread thread = new BeepThread();
		thread.start();
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
		}
	}

}

```

- 방법2

```java
package chap12;

import java.awt.Toolkit;

public class BeepPrintEx {

	public static void main(String[] args) {
		Thread thread = new Thread(){
            	public void run() {
                    // TODO Auto-generated method stub
                    Toolkit tk = Toolkit.getDefaultToolkit();
                    for(int i=0;i<5;i++) {
                        tk.beep();
                        try {
                            // 0.5초마다 비프음 발
                            Thread.sleep(500);
                        } catch (Exception e) {
                            // TODO: handle exception
                        }
                    }
                }            
        }
		thread.start();
		for(int i=0;i<5;i++) {
			System.out.println("띵");
			try {
				// 0.5초마다 비프음 발
				Thread.sleep(500);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
		}
	}
}
```

### 스레드 이름

스레드는 자신의 이름을 가지고 있다. 큰 역할을 하는 것은 아니지만, 디버깅할 때 어떤 스레드가 어떤 작업을 하는지 확인할 때 사용된다. 메인 스레드는 "main"이라는 이름을 가지고 있고, 우리가 직접 생성한 스레드는 자동적으로 "Thread-n" 로 이름이 설정된다. 만약 다른 이름으로 설정하고 싶다면 `setName()` 메소드로 변경할 수 있다.

```java
thread.setName("스레드 이름");
```

반대로 스레드 이름을 알고 싶다면 `getName()` 으로 받아올 수 있다.

```java
thread.getName();
```

setName()과 getName()은 Thread 인스턴스 메소드여서 스래드 객체의 참조가 필요하다. 스레드 객체를 참조하고 있지 않다면 currentThread() 정적메소드로 참조를 얻을 수 있다.

```java
Thread thread = Thread.currentThread();
```



## 스레드 우선순위

![](https://images.techhive.com/images/idge/imported/article/jvw/1998/09/concurrency-100158287-orig.gif)

스레드는 동시성(concurrency) 또는 병렬성(parallelism)으로 실행된다.

- 동시성 : 멀티 작업을 위해 하나의 코어에서 멀티 스레드가 번갈아가며 실행되는 성질
- 병렬성 : 멀티 작업을 위해 멀티 코어에서 개별 스레드를 동시에 실행하는 성질

스레드 수가 코어의 수보다 많을 경우에 스레드를 어떤 순서에 의해 동시성으로 실행할 것인지 결정해야한다. 이것을 **스레드 스케쥴링**이라 한다. 스레드 스케줄링에 의해 스레드들은 아주 짧은 시간에 번갈아가면서 run() 메소드를 조금씩 수행한다.

자바에서 스레드 스케줄링은 **우선순위(Priority)** 방식과 **순환 할당(Round-Robin)** 방식을 사용한다.

- 우선순위 : 우선순위가 높은 스레드가 실행 상태를 더 많이 가지도록 스케줄링 한것
- 순환 할당 : 시간 할당량(Time Slice)을 정해서 하나의 스레드를 정해진 시간만큼 실행하고 다시 다른 스레드를 실행하는 방식

우선 순위 방식은 스래드 객체에 우선순위 번호를 부여할 수 있기때문에 개발자가 코드로 제어할 수 있으나, 순환 할당 방식은 자바 가상 기계에 의해서 정해지기 때문에 코드로 제어할 수 없다.

우선순위 방식에서 우선순위는 1(가장 낮은 우선순위)~10(가장 높은 우선순위)까지 부여된다. 우선순위를 부여하지 않으면 모든 스레드들은 기본적으로 5의 우선순위를 할당받는다.

```java
thread.setPriority(우선순위);
```

`setPriority()` 메소드를 이용해서 우선순위를 줄 수 있다. 1~10의 값을 직접 주어도 되지만, 코드의 가독성을 높이기 위해 클래스 상수를 사용할 수도 있다.

```java
thread.setPriority(Thread.MAX_PRIORITY);	// 10
thread.setPriority(Thread.NORM_PRIORITY);	// 5
thread.setPriority(Thread.MIN_PRIORITY);	// 1
```

#### 예제

```java
package chap12;

public class PriorityEx {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for(int i=1;i<=10;i++) {
			Thread thread = new CalcThread("thread"+i);
			if(i==10) {
				thread.setPriority(Thread.MAX_PRIORITY);
			}else {
				thread.setPriority(Thread.MIN_PRIORITY);
			}
			thread.start();
		}
	}

}
```

```java
package chap12;

public class CalcThread extends Thread{
	public CalcThread(String name) {
		// 스레드 이름 설정 
		setName(name);
	}
	
	@Override
	public void run() {
		for(int i=0;i<2000000000;i++) {
			
		}
		System.out.println(getName());
		
	}
}
```



## 동기화 메소드와 동기화 블록

### 공유 객체를 사용할 때 주의할 점

싱글 스레드 프로그램에서는 한 개의 스레드가 객체를 독차지해서 사용하면 되지만, 멀티 스레드 프로그램에서는 스레드들이 객체를 공유해서 작업해야하는 경우가 있다. 이러한 경우에 스레드 A를 사용하던 객체가 스레드 B에 의해서 상태가 변경될 수 있기 때문에 스레드 A가 의도했던 것과 다른 결과를 산출할 수 있다.

```java
package chap12;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Calculator calculator = new Calculator();
		
		User1 user1 = new User1();
		user1.setCalculator(calculator);
		user1.start();
		User2 user2 = new User2();
		user2.setCalculator(calculator);
		user2.start();
	}
}
```

```java
package chap12;

public class Calculator {
	private int memory;

	public int getMemory() {
		return memory;
	}

	public void setMemory(int memory) {
		this.memory = memory;
		try {
			Thread.sleep(2000);
		} catch (Exception e) {
			// TODO: handle exception
		}
		System.out.println(Thread.currentThread().getName() + ": "+this.memory);
	}
	
}
```

```java
package chap12;

public class User1 extends Thread{
	private Calculator calculator;

	public void setCalculator(Calculator calculator) {
		this.setName("USER1");
		this.calculator = calculator;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		calculator.setMemory(100);
	}
	
}
```

```java
package chap12;

public class User2 extends Thread{
	private Calculator calculator;

	public void setCalculator(Calculator calculator) {
		this.setName("USER2");
		this.calculator = calculator;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		calculator.setMemory(50);
	}
	
}
```

```
USER1: 50
USER2: 50
```

User1 스레드가 Calculator 객체의 memory 필드에 100을 저장하고 2초간 멈춘 상태가된다. 그동안에 User2가 memory값을 50으로 변경한다. User1이 2초가 지나고 memory 필드의 값을 출력하면 50이 나오는 것을 볼 수 있다.

### 동기화 메소드 및 동기화 블록

스레드가 사용 중인 객체를 다른 스레드가 변경할 수 없도록 하려면 스레드 작업이 끝날 때까지 객체에 다른 스레드가 접근할 수 없도록 해야한다. 멀티 스레드 프로그램에서 **단 하나의 스레드만 실행할 수 있는 코드 영역을 임계 영역(critical section)**이라고 한다. 자바에서 임계 영역을 지정하기 위해서 **동기화(synchronized)** 메소드와 동기화 블록을 제공한다. 스레드가 객체 내부의 동기화 메소드 혹인 블록에 들어가면 즉시 객체에 잠금을 걸어서 다른 스레드가 임계영역코드를 실행하지 못하도록 한다.

```java
public synchronized void method(){
    //임계영역, 단 하나의 스레드만 실행
}
```

동기화 메소드는 메소드 전체 내용이 임계영역이므로 스레드가 동기화 메소드를 실행하는 즉시 객체에는 잠금이 일어나고, 스레드가 동기화 메소드를 종료하면 잠금이 풀린다.

메소드 전체가 아니라 일부만 임계영역으로 만들 수도 있다.

```java
public void method(){
    //여러스레드가능
    synchronized(공유객체){
        //임계영역
    }
    // 여러 스레드 실행 가능
}
```

#### 예제

```java
package chap12;

public class Calculator {
	private int memory;

	public int getMemory() {
		return memory;
	}

	public synchronized void setMemory(int memory) {
		this.memory = memory;
		try {
			Thread.sleep(2000);
		} catch (Exception e) {
			// TODO: handle exception
		}
		System.out.println(Thread.currentThread().getName() + ": "+this.memory);
	}
	
}
```

```
USER1: 100
USER2: 50
```

동기화메소드로 바꾼 결과 user1은 100, user2는 50이 나오는 것을 볼 수 있다.

```java
package chap12;

public class Calculator {
	private int memory;

	public int getMemory() {
		return memory;
	}

	public void setMemory(int memory) {
		synchronized (this) {
			this.memory = memory;
			try {
				Thread.sleep(2000);
			} catch (Exception e) {
				// TODO: handle exception
			}
			System.out.println(Thread.currentThread().getName() + ": "+this.memory);
		}	
	}	
}
```

다음과 같이 동기화 블록으로도 만들 수 있다.



## 스레드 상태

![](https://www.careerride.com/Images/states.PNG)

스레드 객체를 생성(New)하고, start() 메소드를 호출하면 곧바로 스레드가 실행되는 것처럼 보이지만 사실은 **실행 대기 상태(Runnable)**가된다. 

- 실행대기상태 : 아직 스케줄링이 되지 않아서 실행을 기다리고 있는 상태

실행 대기 상태에 있는 스레드 중에서 스레드 스케줄링으로 선택된 스레드가 비로서 CPU를 점유하고 run()메소드를 실행한다. 이때를 **실행상태(Running)** 라고한다.

실행 상태의 스레드는 run() 메소드를 모두 실행하기 전에 스레드 스케줄링에 의해서 다시 대기 상태로 돌아갈 수 있다. 그리고 실행 대기 상태에 있는 다른 스레드가 선택되어 실행 상태가된다. 이렇게 **스레드는 실행 대기 상태와 실행 상태를 번갈아가면서 자신의 run() 메소드를 조금씩 수행한다.**

더 이상 실행할 코드가 없으면 스레드의 실행은 멈추게되고 이 상태를 **종료상태**(Dead, Termianted) 라고한다.

경우에 따라서 스레드는 실행 상태에서 **일시 정지 상태**로 가기도한다.

- 일시정지상태 : 스레드가 실행할 수 없는 상태
  - WAITING
  - TIMED_WAITING
  - BLOCKED

스레드가 일시정지상태에서 다시 실행상태로 가기 위해서는 실행대기상태로 가야한다.

### getState()

스레드의 상태를 코드에서 확인할 수 있는 메소드이다.

| 상태      | 열거상수      | 설명                                                  |
| --------- | ------------- | ----------------------------------------------------- |
| 객체 생성 | NEW           | 스레드 객체가 생성, 아직 start() 메소드 호출전 상태   |
| 실행 대기 | RUNNABLE      | 실행 상태로 언제든지 갈 수 있는 상태                  |
| 일시정지  | WAITING       | 다른 스레드가 통지할 때까지 기다리는 상태             |
|           | TIMED_WAITING | 주어진 시간동안 기다리는 상태                         |
|           | BLOCKED       | 사용하고자 하는 객체의 락이 풀릴 때까지 기다리는 상태 |
| 종료      | TERMINATED    | 실행을 마친 상태                                      |



## 스레드 상태 제어

실행중인 스레드의 상태를 변경하는 것을 스레드 상태 제어라한다.

### 상태 제어 메소드

| 메소드                                                      | 설명                                                         |
| ----------------------------------------------------------- | ------------------------------------------------------------ |
| interrupt()                                                 | 일시 정지 상태의 스레드에서 InterruptedException 예외를 발생시켜서 예외 처리 코드(catch)에서 실행 대기 상태 혹은 종료 상태로 갈 수 있도록한다. |
| notify()<br>notifyAll()                                     | 동기화 블록 내에서 wait() 메소드에 의해 일시 정지 상태에 있는 스레드를 실행 대기 상태로 만든다. |
| sleep(long millis)<br>sleep(long millis, int nanos)         | 주어진 시간동안 메소드에 의해 일시 정지 상태에 있는 스레드를 실행 대기 상태로 만든다. |
| join()<br>join(long millis)<br>join(long millis, int nanos) | join() 메소드를 호출한 스레드는 일시 정지 상태가 된다. 다시 대기 상태로 가려면, join()메소드를 멤버로 가지는 스레드가 종료되거나, 매개값으로 주어진 시간이 지나야한다. |
| wait()<br>wait(long millis)<br>wait(long millis, int nanos) | 동기화(synchronized) 블록 내에서 스레드를 일시 정지 상태로 만든다. 매개값으로 주어진 시간이 지나면 자동적으로 실행 대기 상태가 된다. 시간이 주어지지 않으면 notify(), notifyAll() 메소드에 의해서 실행 대기 상태로 갈 수 있다. |
| yield()                                                     | 실행 중에 우선순위가 동일한 다른 스레드에게 실행을 양보하고 실행 대기 상태가 된다. |

#### sleep() : 주어진 시간동안 일시 정지

실행 중인 스레드를 일정시간 멈추게 할때 사용하는 Thread 정적 메소드이다.

```java
try{
    Thread.sleep(1000);
}catch(InterruptedException e){
    // interrupt() 메소드가 호출되면 실행
}
```

매개값에는 얼마 동안 일시 정지 상태로 있을 것인지, 밀리세컨드(1/1000) 단위로 시간을 주면 된다. 

일시 정지 상태에서 주어진 시간이 끝나기 전에 interrupt() 메소드가 호출되면 InterruptedException이 발생하기 때문에 예외 처리가 필요하다.

####  yield() : 다른 스레드에게 실행 양보

스레드가 처리하는 작업은 반복적인 실행을 위해서 for문이나 while 문을 포함하는 경우가 많다.

```java
public void run(){
    while(true){
        if(work){
            System.out.println("Thread1 작업내용");
        }
    }
}
```

이 코드에서 스레드가 시작되어 run() 메소드를 실행하면 while문은 무한 반복 실행하게 된다. 이것보다는 다른 스레드에게 실행을 양보하는 것이 전체 프로그램 성능이 도움이 된다.

```java
public void run(){
    while(true){
        if(work){
            System.out.println("Thread1 작업내용");
        }else{
            Thread.yield();
        }
    }
}
```

yield() 메소드를 호출한 스레드는 실행 대기 상태로 돌아가고 동일한 우선순위 또는 높은 우선순위를 갖는 다른 스레드가 실행 기회를 가질 수 있도록해준다.

#### join() : 다른 스레드의 종료를 기다림

스레드는 다른 스레드와 독립적으로 실행하는 것이 기본이지만 다른 스레드가 종료될 때까지 기다렸다가 실행해야하는 경우가 발생할 수도 있다. 예를 들어서 계산 작업을 하는 스레드가 모든 계산 작업을 마쳤을 때, 계산 결과값을 받아 이용하는 경우이다.

join() 메소드를 호출하면 다른 스레드가 종료될때까지 일시 정지 상태가 되고 종료되면 join()이 풀려서 다음 코드를 수행하게 된다.

```java
package chap12;

public class SumThread extends Thread{
	private long sum;

	public long getSum() {
		return sum;
	}

	public void setSum(long sum) {
		this.sum = sum;
	}
	
	@Override
	public void run() {
		for(int i=1;i<=100;i++)
			sum+=i;
	
	}
}
```

```java
package chap12;

public class Main {

	public static void main(String[] args) {

		SumThread sumThread = new SumThread();
		sumThread.start();
		
		try {
            // sumThread가 종료될때까지 main thread를 일시 정지 시킨다.
			sumThread.join();
		} catch (Exception e) {
			// TODO: handle exception
		}
		
		System.out.println("합 : "+sumThread.getSum());
	}

}
```



#### wait(), notify(), notifyAll() : 스레드 간 협업

경우에 따라서 두 개의 스레드를 교대로 번갈아가며 실행해야 할 경우가 있다. 정확한 교대 작업이 필요한 경우에 자신이 작업이 끝나면 상대방 스레드를 일시 정지 상태에서 풀어주고, 자신은 일시정지 상태로 만드는 것이다.

**공유 객체** 가 핵심이다. 공유 객체는 두 스레드가 작업할 내용을 각각 동기화 메소드로 구분해 놓고, 한 스레드가 작업을 완료하면 **notify() 메소드를 호출해 일시 정지 상태에 있는 다른 스레드를 실행 대기 상태**로 만들고, 자신은 두 번 작업하지 않도록 **wait()  메소드를 호출해 일시정지 상태**로 만든다.

`wait(long timeout)`이나 `wait(long timeout, int nanos)` 를 사용하면 notify()를 호출하지 않아도 지정된 시간이 지나면 스레드가 자동적으로 실행 대기 상태가 된다.

notifyAll()  메소드는 wait() 에 의해 일시 정지된 모든 스레드를 실행 대기 상태로 만든다. 

주의 할점은 이 메소드들은 **동기화 메소드 또는 동기화 블록** 내에서만 사용할 수 있다.

```java
package chap12;

public class WorkObj {
	public synchronized void methodA() {
		System.out.println("ThreadA의 methodA 실행 ");
		// 일시정지->실행대기!
		notify();
		
		try {
			//일시정지상태로 만듦!
			wait();
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
	public synchronized void methodB() {
		System.out.println("ThreadB의 methodB 실행 ");
		// 일시정지->실행대기!
		notify();
		
		try {
			//일시정지상태로 만듦!
			wait();
		} catch (Exception e) {
			// TODO: handle exception
		}
	}

}
```

```java
package chap12;

public class ThreadA extends Thread{
	private WorkObj workObj;
	
	public ThreadA(WorkObj workObj) {
		this.workObj = workObj;
	}
	
	@Override
	public void run() {
		for(int i=0;i<10;i++)
			workObj.methodA();
	}
}

```

```java
package chap12;

public class ThreadB extends Thread{
	private WorkObj workObj;
	
	public ThreadB(WorkObj workObj) {
		this.workObj = workObj;
	}
	
	@Override
	public void run() {
		for(int i=0;i<10;i++)
			workObj.methodB();
	}
}

```

```java
package chap12;

public class Main {

	public static void main(String[] args) {
		// 공유객체생성 
		WorkObj sharedObj = new WorkObj();
		
		ThreadA threadA = new ThreadA(sharedObj);
		ThreadB threadB = new ThreadB(sharedObj);
		
		threadA.start();
		threadB.start();
	}

}

```

```
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
ThreadA의 methodA 실행 
ThreadB의 methodB 실행 
```

