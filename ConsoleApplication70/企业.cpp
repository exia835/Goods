#include<iostream>
#include<string>
#include <conio.h>
#include<istream>
#include<fstream>  
using namespace std;
//******************货物相关****************
class GoodsKinds
{
public:
	char GoodsName[20];//商品名称
	int GoodsPrice;//商品单价
	int GoodsNum;//商品数量
	int PriceOfAllGoods=GoodsNum*GoodsPrice;//商品总价
	int Money;//公司自有资金
	GoodsKinds* next;
	void InPut();//输入信息
	void MoneyCount();
	void Show();
	void ShowGoods()
	{
		cout << "\t\t请输入商品名称：";  cin >> GoodsName;
		cout << "\t\t请输入商品的价格：";  cin >> GoodsPrice;
		cout << "\t\t请输入商品的数量：";  cin >> GoodsNum;
		cout << "\t\t请输入公司自有资金：";  cin >> Money;
	}
	void ReadFile(istream & in)
	{
		in >> GoodsName >> GoodsPrice >> GoodsNum >> PriceOfAllGoods>> Money;
	}
};
//*****************货物操作相关*************************
class Goods
{
public:
	Goods();
	~Goods();
	void ShowMenu();//输出菜单
	void Find();
	void Save();//保存
	void ModifyItem();//修改函数
	void Sort();
	void Swap(GoodsKinds*,GoodsKinds*);
	int ListCount();

	void DisPlay()//显示公司产品的
	{
		for (GoodsKinds* p = head->next;p!=End; p = p->next)
			p->Show();
		cout << "请继续输入。。。";
		getch();
	}
	void AddItem()
	{
		End->InPut();
		End->next = new GoodsKinds;
		End = End->next;
		cout << "添加成功!" << endl;
		cout << "输入任意字符！继续……";
		getch();
	}
	private:
		GoodsKinds *head, *End;
		ifstream in;
		ofstream out;
		GoodsKinds*FindGoods(char* GoodsName)
		{
			for (GoodsKinds*p = head->next; p->next!= End; p = p->next)
				if (!strcmp(p->GoodsName, GoodsName))
					return p;
		}
};
Goods::Goods()
{
	head = new GoodsKinds;
	head->next = new GoodsKinds;
	End = head->next;
	in.open("sort.txt");
	if (!in)
	{
		cout << "这是一个全新的系统。请输入" << endl;
	}
	else
	{
		while (in.eof())
		{
			End->ReadFile(in);
			if (End->GoodsName[0] == '\0')break;
			End->next = new GoodsKinds;
			End = End->next;
		}
		in.close();
		cout << "\t\t读取企业货物信息成成功！" << endl;
	}
}
//*********************析构函数*********************
Goods::~Goods()
{
	Save();
	for (GoodsKinds*temp; head->next != End;)
	{
		temp = head->next;
		head->next = head->next->next;
		delete temp;
	}
	delete head, End;
}
void GoodsKinds::MoneyCount()
{
	PriceOfAllGoods = GoodsNum*GoodsPrice;
	int All = PriceOfAllGoods + Money;
	cout << "公司总共有" << All << "元资金";
}
void Goods::Swap(GoodsKinds*p1,GoodsKinds*p2)
{
	GoodsKinds* temp = new GoodsKinds;
	strcpy(temp->GoodsName, p1->GoodsName);//名字
	strcpy(p1->GoodsName, p2->GoodsName);
	strcpy(p2->GoodsName, temp->GoodsName);

	temp->GoodsPrice = p1->GoodsPrice;//价格
	p1->GoodsPrice = p2->GoodsPrice;
	p2->GoodsPrice = temp->GoodsPrice;

	temp->GoodsNum = p1->GoodsNum;//数量
	p1->GoodsNum = p2->GoodsNum;
	p2->GoodsNum = temp->GoodsNum;

	temp->PriceOfAllGoods = p1->PriceOfAllGoods;
	p1->PriceOfAllGoods = p2->PriceOfAllGoods;
	p2->PriceOfAllGoods = temp->PriceOfAllGoods;

}
void Goods::Save()
{
	out.open("sort.txt");
	for (GoodsKinds*p = head->next; head->next != NULL; p = p->next)
	{
		out<<p-> GoodsName <<"\t"<<p->GoodsPrice << "\t" << p->GoodsNum 
			<< "\t" << p-> PriceOfAllGoods << "\t" << p-> Money;
	}
	out.close();
}
void Goods::ModifyItem()
{
	char name[20];
	GoodsKinds*p = NULL;
	cout << "请输入查找的货物：";
	cin >> name;
	for(p=head->next;head->next!=NULL;p=p->next)
		if (p = FindGoods(name))
		{
			cout << "请输入修改的。。。" << endl;
			p->next->InPut();
			cout << "修改成功！" << endl;
			cout << "输入任意字符！继续……";
			break;
			getch();
		}
		else
		{
			cout << "\t\t没有找到!" << endl;
			cout << "输入任意字符！继续……";
			break;
			getch();
		}
}
void GoodsKinds::Show()
{
	cout << "货物名称: " << GoodsName << endl;
	cout << "货物单价: " << GoodsNum << endl;
	cout << "货物数量: " << GoodsPrice << endl;
	cout << "这些货物的价值: " << GoodsNum*GoodsPrice << endl;
}
//*********************菜单************************
void Goods::ShowMenu()
{
	
		cout << "**************************************************************************" << endl;
		cout << "〓〓〓〓〓〓〓〓〓〓  ☆  货  物 管 理 系  统     ☆  〓〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓★★★★★       ★★★★★★★      ★★★★★〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       1.增减货物/数量     ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       2.显示货物/数量     ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       3.排序货物/数量     ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       4.修改货物/数量     ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       5.查找货物/数量     ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆               v           ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "〓〓〓〓〓〓〓〓〓★  ☆       0.安全退出系统      ☆  ★〓〓〓〓〓〓〓〓〓" << endl;
		cout << "\n\t\t\n\t\t请选择：";
	
}
//******************查找函数************************
 void Goods::Find()
{
	char GoodsName[20];
	GoodsKinds *p = NULL;

	cout << "\n\t\t********************************\n";
	cout << "\t\t请输入货物";
	cout << "\n\t\t********************************\n";
	cin >> GoodsName;
	if (p = FindGoods(GoodsName))
	{
		p->Show();
		cout << "\t\t请继续输入。。。";
		getch();
	}
	else
	{
		cout << "\t\t没有找到货物信息。。。" << '\n' << endl;
		cout << "\t\t请输入任意字符！请继续。。。";
		getch();
	}

} 
 void GoodsKinds::InPut()//输入
 {
	 cout << "\t\t请输入货物：";  cin >> GoodsName;
	 cout << "\t\t请输入货物价格：";  cin >> GoodsPrice;
	 cout << "\t\t请输入货物数量：";  cin >> GoodsNum;
	 cout << "\t\t请输入企业自有资金：";  cin >>Money;
 }
 int Goods::ListCount()//统计当前链表的记录总数，返回一个整数  
 {
	 if (!head)
		 return 0;
	 int n = 0;
	 for (GoodsKinds * p = head->next; p != End; p = p->next)
	 {
		 n++;
	 }
	 return n;
 }
void Goods::Sort()
 {
	 cout << "sorting..." << endl;
	 GoodsKinds*p = NULL, *p1 = NULL, *k = NULL;
    int n = Goods::ListCount();
	if (n < 2)
		return;
	for(p=head->next;p!=End;p=p->next)
		for(k = p->next; k != End; k = k->next)
		{
			if (p->PriceOfAllGoods>k->PriceOfAllGoods)
			{
				Swap(p, k);
			}
		}
	cout << "排序完成！" << endl;
	getch();
	return;
 }
 int main()
 {
	 int x = 0,i;
	 Goods start;
	 bool quit = false;
	 cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
	 for (i = 0; i<3; i++)
		 cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	 cout << "\t\t\t\t欢迎进入企业信息管理系统" << endl;
	 cout <<"\t\t\t\t请输入任意字符" << endl;
	 for (i = 0; i<3; i++)
		 cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	 cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
	 getch();
	 while (!quit)
	 {
		system("cls");
		start.ShowMenu();
		 cin >> x;
		 switch (x)
		 {
		 case 1:start. AddItem(); break;
		 case 2:start.DisPlay(); break;
		 case 3:start.Sort(); break;
		 case 4:start.ModifyItem(); break;
		 case 5:start.Find(); break;
		 case 0:quit = true; break;
		 default:
			 break;
		 }

	 }
	 return 0;
 }

