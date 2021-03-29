/*
 8진수가 주어졌을 때, 2진수로 변환하는 프로그램을 작성하시오.
 첫째 줄에 8진수가 주어진다. 주어지는 수의 길이는 333,334을 넘지 않는다.
 첫째 줄에 주어진 수를 2진수로 변환하여 출력한다. 수가 0인 경우를 제외하고는 반드시 1로 시작해야 한다.
*/

#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
string eight[8] = {"000","001","010","011","100","101","110","111"};
int main(){
	string s;
	cin >> s;
	bool st = false;
	if(s.length() == 1 && s[0]-'0' == 0)	cout << "0";
	for(int i = 0;i < s.length();i ++){
		int n = s[i]-'0';
		if(!st && n < 4){
			if(n == 0)	continue;
			else if(n == 1)	cout << "1";
			else if(n == 2)	cout << "10";
			else if(n == 3)	cout << "11";
			st = true;
		}
		else{
			cout << eight[n];
			st = true;
		}
	}
	return 0;
}