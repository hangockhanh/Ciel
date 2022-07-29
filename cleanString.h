#include <string>
#include <iostream>

using namespace std;

bool lowSign(char c){
	if (c == '+' || c == '-') return true;
	return false;
}

bool highSign(char c){
	if (c == '*' || c == '/' || c == '%') return true;
	return false;
};

string cleanString(string s){
	int len = s.length();
	int i;
	int count;
	for (i = 0; i < len; i++){
		if (lowSign(s[i])){
			if (i == 0){
				s = '0' + s;
				len++;
				i++;
			}
			int j = i;
			count = 0;
			while (lowSign(s[i])){     	      //j..i tinh so dau -
				if ( highSign(s[i+1])){ 
					return "syntax";
				}
				if (s[i] == '-') count++;
				i++;
			}
			if ( (count%2) == 0){
				s = s.substr(0,j) + '+' + s.substr(i, len-i);
			} 
			else{
				s = s.substr(0,j) + '-' + s.substr(i, len-i);
			} 
			len -= (i-j-1);
			i = j + 1;
		}
		if (highSign(s[i])){
			if (i == 0){
				return "syntax"; 
			}
			if (lowSign(s[i+1])){
				int j = i + 1, k = i;
				int count = 0;
				k++;
				while (lowSign(s[k])){
					k++;
					count++;
				}   
				if (!isdigit(s[k])) return "syntax";
				while (isdigit(s[k])) {
					k++;
					count++;
				}
				s = s.substr(0,j) + "(0" + s.substr(j, count) + ")" + s.substr(k, len - k); 
				len+=3;
			}			
		}
		else if (isdigit(s[i])) continue;
		else if (s[i] == '('){
			if (highSign(s[i+1])) return "syntax";
			else if (lowSign(s[i+1])){
				s = s.substr(0, i+1) + "0" + s.substr(i+1, len-i+1);
				len++;
			}
		}
		else if (s[i] == ')') continue;
		else{ 
			cout << s << endl;
			return "syntax";
		} 
	}
	return s;
}


