# Java GUI 실습 - 버튼을 클릭해서 위치 변경 + 배경색 랜덤

```java
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
```
```java
class Quiz extends JFrame implements MouseListener{
	private JButton btn;
	private JPanel panel;
	private Color[] cs = {Color.blue,Color.red,Color.yellow, Color.cyan};
	
	public Quiz(String name) {
		this.setSize(300,300);
		panel = new JPanel();
		panel.setSize(200,300);
		panel.setBackground(Color.gray);
		
		btn = new JButton(name);
		btn.setOpaque(true);
		btn.setBounds(10, 10, 200, 20);
		panel.add(btn);
		this.add(panel);
		
		btn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e){
				System.out.println((int)(Math.random()*10%4));
				btn.setBackground(cs[(int)(Math.random()*10%3)]);
			}
		});
		
		
		panel.addMouseListener(this);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}
	public void mouseClicked(MouseEvent e) {
		System.out.println(e.getX());
		System.out.println(e.getY());
		btn.setLocation(e.getX(), e.getY());
	}
	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}
```
```java
public class QuizTest {
	public static void main(String[] args) {
		Quiz q = new Quiz("버튼이다다");
	}
}
```