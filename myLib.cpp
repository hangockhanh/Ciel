#include "bigNum.h"
#include "cleanString.h"
#include <fstream>
using namespace std;

bool test(bigInt a, bigInt b)
{ // kiểm tra dữ liệu nhập vào có đúng không
	bool flag = 1;
	for (char x : a.getNum())
		if (!isdigit(x))
			flag = 0;
	for (char x : b.getNum())
		if (!isdigit(x))
			flag = 0;
	if (a.getSign() != '+' && a.getSign() != '-')
		flag = 0;
	if (b.getSign() != '+' && b.getSign() != '-')
		flag = 0;
	return flag;
}

int way2()
{ 
	while (1){
		cout << "Nhap bieu thuc: ";
		string e;
		fflush(stdin);
		getline(cin, e); 
		if (e == "") return 0;
		e = noSpace(e);
		string e1 = cleanString(e);
		if (e1 == "syntax"){
			cout << "[ERROR]: Syntax Error!!\n";
			return 1;
		};
		string convert = infixToPostfix(e1);
        if (convert == "syntax"){ 
            cout << "[ERROR]: Syntax Error!!\n";
            return 1;
        }
		bigInt ans = calcPostfix(convert);
		if (ans.getSign() == ' '){               
			cout << "[ERROR]: Cannot divide by 0\n";
			return 1;
		}
		string res;
		for (int i = 0; i < e.length(); i++)
		{
			res.push_back(e[i]);
		}
		ofstream fo;
		fo.open("output.txt", std::ofstream::app);
		fo << res << " = " << ans << endl;
		cout << res << " = " << ans << endl;
	}
}
int main()
{ // hàm main
	while (1){
		cout << "\n---------------------CHUONG TRINH TINH SO NGUYEN LON--------------------------------\n";
		cout << "|\tMENU:                                                                      |\n";
		cout << "|\t1: Nhap bieu thuc tu ban phim (Khi da chon thi nhan Enter de tro ve MENU)  |\n";
		cout << "|\t2: Nhap bieu thuc tu file                                                  |\n";
		cout << "|\t3: Tinh 1000 so fibonacci dau tien va luu vao file \"fibonacci.txt\"         |\n";
		cout << "|\t4: Thoat chuong trinh                                                      |\n";
		cout << "------------------------------------------------------------------------------------\n";
		cout << "Nhap lua chon:\n";
		string f; 
		cin >> f;
		while (f != "1" && f != "2" && f != "3" && f != "4"){
			cout << "Yeu cau nhap lai: ";
			cin >> f;
		}
		if (f == "1")
		{
			while (way2());
		}
		else if (f == "2")
		{ // kiểm tra dữ liệu nhập vào từ file
			ifstream fi("input.txt");
			ofstream fo;
			fo.open("output.txt", std::ofstream::app);

			// fi.ignore(); // tính biểu thức trung tố
			string e;
			while (getline(fi, e)){
				if (e == "") return 0;
                e = noSpace(e); 
                string e1 = cleanString(e); 
                if (e1 == "syntax"){
                    cout << "[ERROR]: Syntax Error!!\n";
                    continue;
                };

                string convert = infixToPostfix(e1);
				if (convert == "syntax"){ 
					cout << "[ERROR]: Syntax Error!!\n";
					continue;
        		}
                bigInt ans = calcPostfix(convert);
                if (ans.getSign() == ' '){         
                    cout << "[ERROR]: Cannot divide by 0\n";
                    continue;
                }
                string res;
                for (int i = 0; i < e.length(); i++)
                {
                    res.push_back(e[i]);
                }
                res.push_back(' ');
                ofstream fo;
                fo.open("output.txt", std::ofstream::app);
                fo << res << "= " << ans << endl;
                cout << res << "= " << ans << endl;
			}
			
		}
		else if (f == "3"){
			ofstream fo("fibonacci.txt");
			int i = 2, lim = 1000;
			fo << lim << " so Fibonacci dau tien la:\n"; // tính lim số fibonacci
			fo << 0 << "\n"
			<< 1 << endl;
			bigInt f1('+', "1"), f2('+', "2"), f;
			while (i <= lim)
			{
				fo << f1 << endl;
				f = f1 + f2;
				f1 = f2;
				f2 = f;
				i++;
			}
		}
		else exit(0);
	}
	return 0;
}