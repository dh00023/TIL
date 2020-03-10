# Thread 실습

## extends && synchronized

```java
package system;

public class BookingThread extends Thread{
	private TicketCounter tc;
	private String name;
	private int num;
	
	public BookingThread(TicketCounter tc, String name, int num) {
		this.tc= tc;
		this.name = name;
		this.num = num;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		tc.booking(name, num);
	}
}
```

```java
package system;

public class TicketCounter {
	private int availableSeats = 3;
	
	public synchronized void booking(String name, int num) {
		if(availableSeats>=num && num>0) {
			System.out.println(name+"님 안녕하세요.");
			System.out.println(num+"개의 좌석 예약이 완료되었습니다^-^");
			availableSeats-=num;
		}else {
			System.out.println(name+"님 안녕하세요.");
			System.out.println("예약가능한 좌석은 "+availableSeats+"개 입니다.");
			System.out.println(num+"개의 좌석 예약이 불가능합니다.");
		}
	}
}
```

```java
package client;


import system.BookingRunnable;
import system.BookingThread;
import system.TicketCounter;

public class Test {
	public static void main(String[] args) {
		// extends
		TicketCounter tc = new TicketCounter();
		
		BookingThread t1 = new BookingThread(tc,"dahye",2);
		BookingThread t2 = new BookingThread(tc,"mirea",2);
		
		t1.start();
		t2.start();
		
	}
}
```

## implements

```java
package system;

public class BookingRunnable implements Runnable {

	private TicketCounter tc;
	private String name;
	private int num;
	
	public BookingRunnable(TicketCounter tc, String name, int num) {
		this.tc= tc;
		this.name = name;
		this.num = num;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		tc.booking(name, num);
	}
}
```

```java
package client;


import system.BookingRunnable;
import system.BookingThread;
import system.TicketCounter;

public class Test {
	public static void main(String[] args) {
		//implements
		Runnable r1 = new BookingRunnable(tc, "dahye", 2);
		Runnable r2 = new BookingRunnable(tc, "mirea", 2);
		Thread t1 = new Thread(r1);
		Thread t2 = new Thread(r2);
		t1.start();
		t2.start();
	}
}
```

## wait(), notify()

```java
package message;

public class Message {
    private String msg;
    
    public synchronized String getMsg() {
        if(this.msg == null) {
        		// 메세지 필드가 null 이면 받는사람의 스레드를 일시정지상태로 만들어준다!
        		try {
        			wait();
        		}catch(InterruptedException e) {}
        }
        
        String returnMsg = msg;
        System.out.print("메세지가 도착했습니다. => ");
        System.out.println(returnMsg);
        
        // 메세지 필드를 null로 만들고 메세지를 보내는 사람의 스레드를 실행대기상태로 만든다.
        msg = null;
        notify();
        
    		return returnMsg;
    }

    public synchronized void setMsg(String str) {
	    	if(this.msg != null) {
	    		// msg 필드가 null 이 아니면 보내는 사람의 스레드를 일시정지상태로만든다.
	    		try {
	    			wait();
	    		}catch(InterruptedException e) {}
	    }
    		this.msg=str;
    		System.out.print("메세지를 보냅니다. => ");
    		System.out.println(msg);
    		// 메세지를 msg 필드에 저장하고, 받는 사람의 스레드를 실행대기 상태로 만든다.
    		notify();
    }

}
```

```java
package message;

public class Sender extends Thread{
	private Message msg;
	
	public Sender(Message msg) {
		this.msg = msg;
	}
	
	@Override
	public void run() {
		for(int i=1;i<=3;i++) {
			String str = "오늘은 6월 "+i+"일이야!";
			msg.setMsg(str);
		}
	}

}
```

```java
package message;

public class Recipient extends Thread {
	private Message msg;
	
	public Recipient(Message msg) {
		this.msg = msg;
	}
	
	@Override
	public void run() {
		for(int i=1;i<=3;i++) {
			String str = msg.getMsg();
		}
	}
	
}
```

```java
package message;

public class Main {
	public static void main(String[] args) {
		Message msg = new Message();
		
		Sender sender = new Sender(msg);
		Recipient recipient = new Recipient(msg);
		
		sender.start();
		recipient.start();
	}
}
```