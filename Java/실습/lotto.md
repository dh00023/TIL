
# Java GUI 실습 - 로또 게임

```
/src
ㄴ/controller
	ㄴMain.java
ㄴ/model
	ㄴLottoModel.java
ㄴ/view
	ㄴLottoView.java
```
## Model

```java
package model;

import java.io.InputStreamReader;
import java.net.URL;
import java.util.Arrays;

import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

public class LottoModel {
	private int count,bonusCount;
	private String winNum[] = new String[6];
	private String bonus;
	private String myNum[]  = new String[6];
	private String checkNum[]=new String[6];
	public LottoModel(String turn) {
		setLotto(turn);
		System.out.println(this.getBonus());
		System.out.println(this.getWinNum());
		setRandom();
		System.out.println(this.getMyNum());
		check();
	}
	public void setLotto(String turn) {
		URL result;
		String winNums[]=new String[6];
		try {
			result = new URL("http://www.nlotto.co.kr/common.do?method=getLottoNumber&drwNo="+turn);
			InputStreamReader isr = new InputStreamReader(result.openConnection().getInputStream(),"UTF-8");
			
			JSONObject obj = (JSONObject)JSONValue.parse(isr);
			System.out.println("읽어온 결과 : "+obj.toJSONString());
			
			if("success".equals(obj.get("returnValue"))) {
				System.out.print("로또 번호 : ");
				for(int i=1;i<=6;i++) {
					System.out.print(" "+obj.get("drwtNo"+i));
					
					winNums[i-1]=obj.get("drwtNo"+i).toString();
					this.setWinNum(winNums);
				}
				System.out.println("보너스 : "+obj.get("bnusNo"));
				this.setBonus(obj.get("bnusNo").toString());
			}else {
				System.out.println("로또 정보 읽기 실패");
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void setRandom() {
		String[] myNum=new String[6];
		int[] lotto = new int[6];
		for(int i=0;i<myNum.length;i++) {
			lotto[i] = (int)(Math.random()*45)+1;
			for(int j=i-1;j>=0;j--) {
				if(lotto[i]==lotto[j]) {
					i--;
					break;
				}
			}
			
		}
		Arrays.sort(lotto);
		for(int i=0;i<myNum.length;i++) {
			myNum[i]=String.valueOf(lotto[i]);
			System.out.println(myNum[i]);
		}
		this.setMyNum(myNum);
	}
	public void check() {
		this.count=0;
		this.bonusCount=0;
		
		for(String i : winNum) {
			if(Arrays.asList(myNum).contains(i)) {
				this.checkNum[count++]=i;
			}
		}
		for(int i=count;i<6;i++) {
			this.checkNum[i]=null;
		}
		if(Arrays.asList(this.myNum).contains(bonus)&&count==5) {
			this.checkNum[count]=bonus;
			bonusCount=1;
		}
		
	}
	public int result() {	
		switch (this.count) {
		case 6:
			return 1;
		case 5:
			if(this.bonusCount==1)return 2;
			else return 3;
		case 4:
			return 4;
		case 3:
			return 5;
		default:
			return 6;
		}
	}

	public String[] getWinNum() {
		return winNum;
	}
	public void setWinNum(String[] winNum) {
		this.winNum = winNum;
	}
	public String getBonus() {
		return bonus;
	}
	public void setBonus(String bonus) {
		this.bonus = bonus;
	}
	public String[] getMyNum() {
		return myNum;
	}
	public void setMyNum(String[] myNum) {
		this.myNum = myNum;
	}
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public int getBonusCount() {
		return bonusCount;
	}
	public void setBnousCount(int bnousCount) {
		this.bonusCount = bonusCount;
	}
	public String[] getCheckNum() {
		return checkNum;
	}
	public void setCheckNum(String[] checkNum) {
		this.checkNum = checkNum;
	}
	
}
```

## View

```java
package view;

import java.awt.Color;

import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Graphics;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.Border;

import model.LottoModel;

public class LottoView extends JFrame{
	private JPanel panel,win, my,result;
	
	Border blackline = BorderFactory.createLineBorder(Color.black);
	private JLabel lottoNum[]= new JLabel[6],myNum[] = new JLabel[6],resNum[] = new JLabel[6];
	private JLabel plus,res,turn_name,my_name,bonus;
	private String winNums[],myNums[];
	private String[] resNums;
	
//	public void paint(Graphics g) {
//		g.setColor(Color.white);
//		g.drawOval(480, 480, 200, 200);
//		g.setColor(Color.red);
//		g.fillOval(240,240,200,100);
//	}
	public LottoView(String turn) {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 450);
		getContentPane().setLayout(null);
		
		panel = new JPanel();
		panel.setBounds(6, 6, 438, 415);
		panel.setLayout(null);
		this.add(panel);
		
		win  = new JPanel();
		win.setBounds(6, 38, 426, 96);
		win.setLayout(new GridLayout(1,8));
		win.setBorder(blackline);
		panel.add(win);
		
		my = new JPanel();
		my.setBounds(6, 181, 426, 96);
		my.setLayout(new GridLayout(1,6));
		my.setBorder(blackline);
		panel.add(my);
		
		result = new JPanel();
		result.setBounds(6, 313, 426, 96);
		result.setLayout(new GridLayout(1,6));
		result.setBorder(blackline);
		panel.add(result);
		
		turn_name = new JLabel(turn+"회 로또번호");
		turn_name.setFont(new Font("Apple SD Gothic Neo", 1, 20));
		turn_name.setBounds(6, 6, 426, 30);
		panel.add(turn_name);
		
		my_name = new JLabel("나의 로또 번호");
		my_name.setFont(new Font("Apple SD Gothic Neo", 1, 20));
		my_name.setBounds(6, 147, 208, 30);
		panel.add(my_name);
		

		res = new JLabel("결과");
		res.setFont(new Font("Apple SD Gothic Neo", 1, 20));
		res.setBounds(6, 284, 426, 30);
		panel.add(res);
	}
	public LottoView(String turn, LottoModel model) {
		this(turn);
		winNums = model.getWinNum();
		int i=0;
		for(String winN : winNums) {
			System.out.println(winN);
			lottoNum[i] = new JLabel(winN, SwingConstants.CENTER);
			lottoNum[i].setOpaque(true);
			lottoNum[i].setFont(new Font("Apple SD Gothic Neo", 1, 20));
			win.add(lottoNum[i++]);
		}
		plus = new JLabel("+", SwingConstants.CENTER);
		plus.setOpaque(true);
		plus.setFont(new Font("Apple SD Gothic Neo", 1, 25));
		win.add(plus);
		bonus = new JLabel(model.getBonus(), SwingConstants.CENTER);
		bonus.setOpaque(true);
		bonus.setFont(new Font("Apple SD Gothic Neo", 1, 20));
		win.add(bonus);

		JButton button = new JButton("새로 뽑기");
		button.setBounds(315, 146, 117, 29);
		panel.add(button);
		
		myNums = model.getMyNum();
		i=0;
		for(String myN : myNums) {
			myNum[i] = new JLabel(myN, SwingConstants.CENTER);
			myNum[i].setOpaque(true);
			myNum[i].setFont(new Font("Apple SD Gothic Neo", 1, 20)); 
			my.add(myNum[i++]);
			System.out.println(myN+"view: "+i);
		}
		
		res.setText("결과 : "+model.result()+"등입니다.");
		resNums = model.getCheckNum();
		i=0;
		for(String resN : resNums) {
			resNum[i] = new JLabel(resN, SwingConstants.CENTER);
			resNum[i].setOpaque(true);
			resNum[i].setFont(new Font("Apple SD Gothic Neo", 1, 20));
			result.add(resNum[i++]);
		}
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				System.out.println("a클릭");
				model.setRandom();
				model.check();
				
				res.setText("결과 : "+model.result()+"등입니다.");
				int i=0;
				for(String myN : model.getMyNum()) {
					System.out.println(i+"view: "+myN);
					myNum[i++].setText(myN);
				}
				i=0;
				for(String myN : model.getCheckNum()) {
					System.out.println(i+"checkview: "+myN);
					if(myN==null) {
						System.out.println("null");
						resNum[i++].setText(" ");
					}else {
						resNum[i++].setText(myN);
					}
					
				}
			}
		});
	}

}
```

## Controller

```java
package controller;
//import java.util.Calendar;
//import java.util.TimeZone;

import model.LottoModel;
import view.LottoView;

public class Main {

	public static void main(String[] args) {
		String turn="807";
		LottoModel m = new LottoModel(turn);
		LottoView  v= new LottoView(turn,m);
		v.setVisible(true);				
	}

}
```