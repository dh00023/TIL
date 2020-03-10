# GUI (Graphical User Interface)


 GUI 응용 프로그램은 키보드뿐 아니라 마우스 사용 지원, 화려하고 다양한 화면과 더불어 사용자가 자유롭게 화면 작동 가능하다.

## Java GUI 종류

![](https://www.javatpoint.com/images/awthierarchy.jpg)

- AWT(Abstract Windows Toolkit) : 운영체제가 제공하는 자원을 이용하여 컴포넌트 생성한다. 따라서 운영체제 별로 느낌이 다르다.
  - `java.awt.*`
  - Button, Frame, TextField

![](https://cdn.guru99.com/images/uploads/2012/06/java-swing-class-hierarchy.jpg)

- Swing : 컴포넌트가 자바로 작성되어 있기 때문에 어떤 플랫폼에서도 일관된 화면을 보여줄 수 있다.

  - `javax.swing.*`
  - 형식화된 텍스트 입력이나 패스워드 필드 동작과 같은 복잡한 기능이 제공된다.
- Java 2D API : 그림, 이미지, 애니메이션 기능을 제공
- 데이터 전송 : 자르기, 복사, 붙이기 , Drag and Drop 등 데이터 전송 기능 제공 + undo, redo


## Container

자바에서 Container는 창의 역할을 한다.

- 한 개 이상의 Container 위에 **Component들이 올려질 영역**
- Container는 실제로는 Component보다 작은 개념
- (예) Frame, Window, Panel, Dialog, Applet
- (예) JFrame, JDialog, JApplet, JPanel, JScrollPane

### Frame 생성 하기

#### 방법1 : JFrame 객체 생성

```java
import javax.swing.*;

public class FrameTest1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame f = new JFrame("Frame Test");
		f.setSize(300,200); //크기 지정
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //swing에만 존재한다. x버튼 클릭시 종료
		f.setVisible(true); // Container보이기
	}
}
```

#### 방법2 : JFrame 상속

```java
import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
		setSize(300,200);
        //swing에만 존재한다. x버튼 클릭시 종료
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
		setVisible(true);
	}
	
}

public class FrameTest1{
	public static void main(String[] args) {
		FrameTest f = new FrameTest();
	}
}
```

### 메소드 or 생성자

| 생성자 또는 메소드                   | 설명                                                         |
| ------------------------------------ | ------------------------------------------------------------ |
| void add(Component c)                | 지정된 컴포넌트를 프레임에 추가                              |
| JMenuBar getJMenuBar()               | 이 프레임에 대한 메뉴를 얻는다.                              |
| void pack()                          | 프레임의 크기를 추가된 컴포넌트들의 크기에 맞도록 조절한다.  |
| void remove(Component c)             | 지정된 컴포넌트를 프레임에서 제거                            |
| void setDefaultCloseOperation()      | 사용자가 프레임을 닫을 때 수행된는 동작을 설정한다.<br>일반적으로 `JFrame.EXIT_ON_CLOSE` 로 지정 |
| void setIconImage(Icon Image)        | 프레임이 최소화되었을 때의 아이콘 지정                       |
| void setLayout(LayoutManager layout) | 프레임에 놓이는 컴포넌트들을 배치하는 배치 관리자 지정, 디폴트는 BorderLayout이다. |
| void setLocation(int x, int y)       | 프레임의 (x,y)좌표 지정                                      |
| void setResizeable(boolean value)    | 프레임의 크기 변경 허용 여부                                 |
| void setSize(int width, int height)  | 프레임의 크기 설정                                           |
| void setMenuBar(JMenuBar menu)       | 현재 프레임에 메뉴바를 붙인다.                               |



### Panel

Component들이 가질 수 있는 컨테이너이다.(컴포넌트들을 붙일 수 있는 판)

![](https://www.ntu.edu.sg/home/ehchua/programming/java/images/AWT_ContainerComponent.png)



#### 메소드 & 생성자

| 생성자 or 메소드                      | 설명                                                  |
| ------------------------------------- | ----------------------------------------------------- |
| JPanel()                              | 새로운 Panel 생성                                     |
| JPanel(boolean isDoubleBuffered)      | 만약 매개변수가 참이면 더블 버퍼링 사용               |
| JPanel(LayoutManager layout)          | 지정된 배치 관리자를 사용하는 Panel 생성              |
| void add(Component c)                 | 지정된 컴포넌트 Panel에 추가                          |
| void remove(Component c)              | 지정된 컴포넌트 Panel에 제거                          |
| void setLaytout(LayoutManager layout) | 배치 관리자를 지정한다. 디폴트는 FlowLayout이다.      |
| void setSize(int width, int height)   | Panel의 크기 지정                                     |
| void setLocation(int x, int y)        | Panel의 위치 지정                                     |
| void setToolTipText(String text)      | 사용자가 마우스를 Panel의 빈곳에 올려놓으면 팁을 표시 |



## Component

실제로 Container 위에 올려져서 화면 구성을 담당하는 요소들이다.

- (예) Button, TextField, TextArea, List
- (예) JButton,  JTextField, JChoice, JList, JMenu, JCheckbox, JScrollBar,JTextArea, JCanvas

### Component 생성하기

```java
import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
        //버튼 생성, 추가
		JButton button  = new JButton("버튼");
		// Container위에 Component추가
        this.add(button);
        //
		setSize(300,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
		setVisible(true);
	}
	
}
```

### 모양을 설정하는 메소드

| 메소드                                             | 설명                                                         |
| -------------------------------------------------- | ------------------------------------------------------------ |
| void setBorder(Border)<br>Border getBorder()       | 컴포넌트의 테두리를 설정하거나 가져온다.                     |
| void setBackground(Color)<br>Color getBackground() | 컴포넌트의 배경색를 설정하거나 가져온다.                     |
| void setForeground(Color)<br>Color getForeground() | 컴포넌트의 전경색를 설정하거나 가져온다.                     |
| void setOpaque(boolean)<br>Boolean IsOpaque()      | 컴포넌트의 불투명을 설정하거나 불투명상태를 확인한다.        |
| void setFont(Font)<br>Font getFont()               | 컴포넌트의 글꼴을 설정하거나 가져온다.                       |
| void setCursor(Cursor)<br>Cursor getCursor()       | 컴포넌트에 마우스 커서를 가져갔을 때 보이는 커서 모양을 설정하거나 가져온다. |

### Label

편집이 불가능한 텍스트를 표시한다.

| 메소드                      | 설명                                                  |
| ------------------------------------- | ----------------------------------------------------- |
| String getText() | Label의 텍스트 반환 |
| void setText() | Label의 텍스트 설정 |
| void setToolTipText(String text)      | 사용자가 마우스를 Label의 위에 올려놓으면 팁을 표시 |
| void setVisible(boolean value) | Label을 보이게 하거나 감춘다. |

### Button

사용자가 클릭했을 경우, 이벤트를 발생하여 원하는 동작을 하게 하는데 이용된다.

| 메소드                                   | 설명                                                         |
| ---------------------------------------- | ------------------------------------------------------------ |
| String getText()                         | 버튼의 현재 텍스트 반환                                      |
| void setText(String text)                | 버튼의 텍스트 설정                                           |
| void doClick()                           | 사용자가 버튼을 누른 것 처럼 이벤트 발생                     |
| void setBorderPanited(boolean value)     | 버튼의 경계를 나타내거나 감춘다.                             |
| void setContentAreaFilled(boolean value) | 버튼의 배경을 채울 것인지 지정                               |
| void setEnable(boolean value)            | 버튼을 활성화 하거나 비활성화                                |
| void setRolloverEnabled(boolean value)   | 마우스가 버튼 위에 있으면 경계를 진하게 하는 rollover 효과 설정 |
| void setToolTipText(String text)         | 사용자가 마우스를 버튼위에 올려놓으면 팁을 표시              |
| void setVisible(boolean value)           | 버튼을 보이게 하거나 감춘다.                                 |

### Text Field

입력이 가능한 한줄의 텍스트 필드를 만드는데 사용한다.

| 생성자 or 메소드                      | 설명                                                  |
| ------------------------------------- | ----------------------------------------------------- |
| JTextField()                          | TextField 생성                                        |
| JTextField(int columns)               | 지정된 칸수를 가지고 있는 TextField 생성              |
| JTextField(String text)               | 지정된 문자열로 초기화된 TextField 생성               |
| String getText() | TextField에 입력된 문자열 반환 |
| void setText(String text) | TextField에 텍스트 쓰기 |
| void setEditable(boolean)<br>boolean isEditable() | 사용자가 텍스트를 입력할 수 있는지 없는지 설정하고 반환 |

### 여러가지 Component 생성하기

```java
class FrameTest extends JFrame{

	public FrameTest() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Component");
		this.setLayout(new FlowLayout());
		
		//한줄을 입력하기위한 텍스트 필드 + 10은 초기열 크
		JTextField txt1 = new JTextField(10);
		this.add(txt1);
		
		// 여러줄 입력하기 위한 텍스트 영역(행, 열)
		JTextArea txt2 = new JTextArea(5,10);
		this.add(txt2);
		//textarea 영역에 스크롤바 추가 
		this.add(new JScrollPane(txt2));
		
		//비밀번호 필드 
		JPasswordField txt3 = new JPasswordField(10);
		this.add(txt3);
		
		setSize(200,200);
		setVisible(true);
	}
	
}
```

```java
class FrameTest extends JFrame{

	public FrameTest() {
		ImageIcon img1 = new ImageIcon("~/Downloads/aa.jpg");
		ImageIcon img2 = new ImageIcon("~/Downloads/aa.jpg");
		
		//버튼에 이미지와 문자가 모두 나타나도록 설정 
		JButton btn1 = new JButton("버튼1",img1);
		
		//Label을 이미지 또는 문자로 생성 
		JLabel lbl1 = new JLabel("Label 입니다.");
		JLabel lbl2 = new JLabel(img2);
		
		//체크박스 3개 생성 + true가 된곳은 체크가 되도록 설정 
		JCheckBox chk1 = new JCheckBox("C++");
		JCheckBox chk2 = new JCheckBox("Ruby");
		JCheckBox chk3 = new JCheckBox("Java",true);
        
        //단일선택 체크박스
        JCheckboxGroup group = new JCheckboxGroup();
		JCheckbox man = new JCheckbox("남자" , true, group);
		JCheckbox woman = new JCheckbox("여자" , false, group);
		
		JRadioButton rdo1 = new JRadioButton("고래 ");
		JRadioButton rdo2 = new JRadioButton("상어  ");
		JRadioButton rdo3 = new JRadioButton("새우  ");

	}
	
}
```



## LayoutManager

 Container 위에 Component들을 올릴 때 자리 배치 방법

- (예) FlowLayout, BorderLayout , GridLayout , CardLayout , GridBackLayout ...

### Layout 설정 형식

```java
Container.setLayout(new 레이아웃종류());
```

### Flow Laytout

![](http://www.zentut.com/wp-content/uploads/2012/10/flowlayout.gif)

기본적으로 component들이 왼쪽에서 오른쪽으로 추가되는 형태이다.

Container의 크기가 변하면 component의 크기는 그대로 이며, 위치가 변경된다. 가운데 정렬이 기본이다.

- Panel, Applet

```java
import java.awt.FlowLayout;

import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
		JButton button  = new JButton("버튼");
		this.add(button);
		setSize(300,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
        // FlowLayout설정
		setLayout(new FlowLayout());
		setVisible(true);
	}
	
}
```



### Border Laytout

![border Layoutì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](https://chortle.ccsu.edu/java5/Notes/chap63/borderPicture.gif)

기본적으로 컴포넌트들이 틀 형태로 존재한다.

Border Layout에 component를 추가할 때는 `this.add(컴포넌트, 위치);` 를 지정해줘야한다. 위치를 지정해주지 않으면 Default값은 Center이다.

```java
import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
		
		JButton button  = new JButton("버튼");
		this.add(button,BorderLayout.NORTH);
		setSize(300,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
		setVisible(true);
	}
	
}
```



### Grid Layout

![](http://profspevack.com/gdprinciples1/wp-content/uploads/2009/09/grids.png)

테이블 형태의 레이아웃이다. 인수를 주지 않으면 행은 1행으로 고정되고 열이 계속해서 추가된다.

행/열 인수에 0이 들어갈 수 있다.

- ex) (2,0)이면 행은 2행으로 고정, 열은 무한대

```java
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;

import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
		
		JButton[] b  = new JButton[6];
		setLayout(new GridLayout(3,2));
		for(int i=0;i<b.length;i++) {
			b[i] = new JButton("button"+i);
			this.add(b[i]);
		}
		
		setSize(300,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
		setVisible(true);
	}
	
}
```



### Card Layout

![card Layoutì ëí ì´ë¯¸ì§ ê²ìê²°ê³¼](http://resource.thaicreate.com/upload/tutorial/java-gui-layout-cardlayout-01.jpg?v=1001)



#### 

### 구체적인 위치 정하기

setLayout에는 null로 지정한 후 setBounds로 직접적인 좌표값을 지정할 수 있다.
```java
setLayout(null);
setBounds(0,0,0,0);
```



### 복합적인 레이아웃 설정하기

```java
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.LayoutManager;

import javax.swing.*;

class FrameTest extends JFrame{

	public FrameTest() {
		
		JPanel pane = new JPanel();
		JButton[] b  = new JButton[4];
		for(int i=0;i<b.length;i++) {
			b[i] = new JButton("button"+i);
		}
		pane.add(b[0]);
		pane.add(b[1]);
		this.add(pane,"North");
		this.add(b[2],"West");
		this.add(b[3],"Center");
		
		setSize(300,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Practice Frame");
		setVisible(true);
	}
	
}

public class FrameTest1{
	public static void main(String[] args) {
		FrameTest f = new FrameTest();
	}
}
```




## 이벤트 처리

- 이벤트(event) : 마우스로 클릭하거나 키보드로 누르는 일련의 모든 작동
- 리스너(Listener) : 사용자가 마우스를 클릭하거나 키보드를 누를 때까지 기다리는 것

![](http://chortle.ccsu.edu/java5/notes/chap57/buttonClick.gif)

```
버튼을 누른다 -> 이벤트 객체가 발생 -> 이벤트 처리(이벤트 리스너 객체)
```

즉, 버튼에 반응하려면 이벤트 처리를 해야한다.

### 액션 이벤트 actionPerformed() 

- **이벤트를 발생시키는 Component(버튼)가 있어야한다.**

- 이벤트 발생 감지 방법 : **Listener 인터페이스**를 달아준다.

  - 클래스에서 implements 시켜 method를 구현 방법

  ```java
  MyClass implements ActionListener{
      public void actionPerformed(ActionEvent e){
          //꼭 구현해야하는 메소드
          //Action 이벤트를 처리하는 코드가 여기에 들어간다.
      }
  }
  ```

  - new로 생성하여 Component마다 리스너를 붙이는 방법

  ```java
  button1.addActionListener(new ActionListener(){메소드 구현..});
  ```



#### Event Listener 위치

- 별도의 클래스로 Event Listener를 작성
  - 별도의 클래스를 두어 이벤트 동작만을 위한 처리를 작성하게 할 수 있다. 
  - 별도의 클래스이기때문에 클래스간 변수를 사용하도록 처리해주어야한다.

```java
MyClass implements ActionListener{
    public void actionPerformed(ActionEvent e){
        //꼭 구현해야하는 메소드
        //Action 이벤트를 처리하는 코드가 여기에 들어간다.
    }
}
```

```java
public class MyFrame extends JFrame{
    ...
    public MyFrame(){
        JPanel panel = new JPanel();
		btn= new JButton("버튼");
		btn.addActionListener(new MyListener());
		panel.add(btn);
		this.add(panel);
		this.setVisible(true);
    }
}
```



- 내부 클래스로 Event Listener를 작성
  - 위와 같이 별도로 클래스를 만들면 MyFrame안의 멤버 변수를 쉽게 사용할 수 없으므로 내부 클래스를 만들어줄 수 있다.

```java
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

class MyFrame extends JFrame{
	private JButton btn;

	public MyFrame() {
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setTitle("내부 클래스 이용하기");
		
		JPanel panel = new JPanel();
		btn= new JButton("버튼");
		btn.addActionListener(new MyListener());
		panel.add(btn);
		this.add(panel);
		this.setVisible(true);
	}
	private class MyListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(e.getSource()==btn) {
				btn.setText("클릭됨");
			}
		}
	}
	
}

public class TestCS {
	public static void main(String[] args) {
		MyFrame f = new MyFrame();
		
	}
}
```
- 프레임 클래스가 Event Listener를 구현하도록 작성
  - `public class Simple extends JFrame implements ActionListener{…}` 의 형태로 actionPerformed를 구현할 수 있다.
  - 각 컴포넌트들이 공통된 동작을 하는 것이 아니라 다양한 동작을 할대는, 각 컴포넌트에서 Event Listener룰 구현하도록한다.

```java
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

class MyFrame extends JFrame implements ActionListener{
	private JButton btn;

	public MyFrame() {
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		btn= new JButton("버튼");
		btn.addActionListener(this);
		panel.add(btn);
		this.add(panel);
		this.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if(e.getSource()==btn) {
			btn.setText("클릭됨");
		}
        //버튼이 여러개라면 if then else가 길어지는 형태이다.
	}
}

public class TestCS {
	public static void main(String[] args) {
		MyFrame f = new MyFrame();
		
	}
}
```

- 각 컴포넌트들이 Event Listener를 구현하도록 작성

```java
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

class MyFrame extends JFrame implements ActionListener{
	private JButton btn;

	public MyFrame() {
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		btn= new JButton("버튼");
		btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(e.getSource()==btn) {
					btn.setText("클릭됨");
				}
			}
		});
		panel.add(btn);
		this.add(panel);
		this.setVisible(true);
    }
}

public class TestCS {
	public static void main(String[] args) {
		MyFrame f = new MyFrame();
		
	}
}
```



### 이벤트의 분류

#### 모든 Component가 지원하는 이벤트

| 이벤트 종류 | 설명                                                         |
| ----------- | ------------------------------------------------------------ |
| Component   | 컴포넌트의 크기나 위치가 변경되었을 경우 발생                |
| Focus       | 키보드 입력을 받을 수 있는 상태 또는 그 반대의 경우 발생     |
| Container   | 컴포넌트가 컨테이너에 추가되거나 삭제될 때 발생              |
| Key         | 사용자가 키를 눌렀을 때 키보드 Focus를 가지고 있는 객체에서 발생 |
| Mouse       | 마우스 버튼이 클릭되거나 마우스가 객체의 영역으로 들어오가나 나올때 발생 |
| MouseMotion | 마우스가 움직였을 때 발생                                    |
| MouseWheel  | 컴포넌트 위에서 마우스 휠을 움직이는 경우 발생               |
| Window      | 윈도우에 어떤 변화(열림, 닫힘, 아이콘화 등)가 있을 때 발생   |

#### 일부 Component가 지원하는 이벤트

| 이벤트 종류   | 설명                                                         |
| ------------- | ------------------------------------------------------------ |
| Action        | 사용자가 어떤 동작을 하는 경우 발생                          |
| Caret         | 텍스트 삽입점이 이동하거나 텍스트 선택이 변경되었을 경우 발생 |
| Change        | 일반적으로 객체의 상태가 변경되었을 경우 발생                |
| Document      | 문서의 상태가 변경되는 경우 발생                             |
| Item          | 선택 가능한 컴포넌트에서 사용자가 선택한 경우 발생           |
| ListSelection | 리스트나 테이블에서 선택 부분이 변경된 경우 발생             |

![](http://cfs13.tistory.com/image/35/tistory/2008/12/15/09/16/4945a1cdb2838)

#### Action Event

- 사용자가 버튼 클릭하는 경우
- 사용자가 메뉴 항목을 선택하는 경우
- 사용자가 텍스트 필드에서 엔터키를 누르는 경우

```java
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

class MyFrame extends JFrame{
	private JButton btnYellow,btnPink;
	private JPanel panel;

	public MyFrame() {
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		panel = new JPanel();
		btnYellow= new JButton("Yellow");
		btnYellow.addActionListener(new MyListener());
		panel.add(btnYellow);
		btnPink= new JButton("Pink");
		btnPink.addActionListener(new MyListener());
		panel.add(btnPink);
		
		
		this.add(panel);
		this.setVisible(true);
		
	}
	private class MyListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(e.getSource()==btnYellow) {
				panel.setBackground(Color.YELLOW);;
			}else if(e.getSource()==btnPink) {
				panel.setBackground(Color.PINK);;
			}
		}
	}
}

public class TestCS {
	public static void main(String[] args) {
		MyFrame f = new MyFrame();
		
	}
}
```

- `getSource()` 메소드를 이용해 이벤트를 발생시킨 객체를 식별한다.
- `getId()` 메소드를 이용해 이벤트의 타입을 식별한다.
- `getActionCommand()` 메소드를 이용해 이벤트를 발생시킨 컴포넌트의 이름을 식별한다.

### Key Event

`keyListener` 인터페이스를 구현한다.

| 메소드                  | 설 명                                   |
| ----------------------- | --------------------------------------- |
| keyTyped(KeyEvent e)    | 사용자가 글자를 입력했을 경우에 호출    |
| keyPressed(KeyEvent e)  | 사용자가 키를 눌렀을 경우에 호출        |
| keyReleased(KeyEvent e) | 사용자가 키에서 손을 떼었을 경우에 호출 |

```java
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class KeyEventPractice extends JFrame implements KeyListener{
	
	public KeyEventPractice() {
		
		this.setSize(300,300);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JTextField tf = new JTextField(20);
		tf.addKeyListener(this);
		this.add(tf);
		this.setVisible(true);
		
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		display(e, "key typed");
	}

	
	@Override
	public void keyPressed(KeyEvent e) {
		display(e, "key pressed");
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		display(e, "key Released");
	}
	private void display(KeyEvent e, String string) {
		// TODO Auto-generated method stub
		 char c = e.getKeyChar();
         int keyCode = e.getKeyCode();
         String modifiers = e.isAltDown() + " " + e.isControlDown() + " " +e.isShiftDown();
         System.out.println(string + " " + c + " " + keyCode + " " + modifiers);

	}	
}
```

### Mouse 이벤트

| 메소드                      | 설 명                                                        |
| --------------------------- | ------------------------------------------------------------ |
| mouseClicked(MouseEvent e)  | 사용자가 컴포넌트를 마우스로 클릭한 경우에 호출된다.         |
| mouseEntered(MouseEvent e)  | 마우스 커서가 컴포넌트의 경계안으로 커서가 들어가면 호출된다. |
| mouseExited(MouseEvent e)   | 마우스 커서가 컴포넌트의 경계밖으로 커서가 나가면 호출된다.  |
| mousePressed(MouseEvent e)  | 마우스가 컴포넌트위에서 눌려지면 호출된다.                   |
| mouseReleased(MouseEvent e) | 마우스가 컴포넌트위에서 떼어지면 호출된다.                   |

```java
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class MouseEventPractice extends JFrame implements MouseListener{
	MouseEventPractice(){
		this.setSize(300,300);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
        JPanel panel = new JPanel();
        panel.addMouseListener(this);  
        add(panel);
        setVisible(true);

	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		display("Mouse clicked (# of clicks: " + e.getClickCount() + ")", e);
	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		display("Mouse pressed (# of clicks: " + e.getClickCount() + ")", e);
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		display("Mouse released (# of clicks: " + e.getClickCount() + ")", e);
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
        display("Mouse entered", e);
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
        display("Mouse exited", e);
	}
	
    protected void display(String s, MouseEvent e) {
        System.out.println(s + " X=" + e.getX() + " Y=" + e.getY());
  }
}
```

#### Mouse의 좌표 얻기

| 메소드                                                       | 설명                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| int getClickCount()                                          | 빠른 연속적인 클릭의 횟수를 반환한다. 예를 들어 2이면 더블 클릭을 의미한다. |
| int getX()<br>int getY() <br>Point getPoint()                | 이벤트가 발생했을 당시의 (x,y) 위치를 반환한다. 위치는 컴포넌트에 상대적이다. |
| int getXOnScreen() <br>int getYOnScreen() <br>int getLocationOnScreen() | 절대 좌표 값 (x,y)을 반환한다. 이들 좌표값은 가상 화면에 상대적이다. |
| int getButton()                                              | 어떤 마우스 버튼의 상태가 변경되었는지를 반환한다. NOBUTTON, BUTTON1, BUTTON2, BUTTON3 중의 하나이다. |
| boolean isPopupTrigger()                                     | 마우스 이벤트가 팝업 메뉴를 나타나게 하면 true를 반환한다.   |
| String getMouseModifiersText(int)                            | 이벤트 도중의 수식키와 마우스 버튼을 기술하는 설명문을 반환한다. |

## 참조 페이지

- [http://programmingsummaries.tistory.com/61](http://programmingsummaries.tistory.com/61)