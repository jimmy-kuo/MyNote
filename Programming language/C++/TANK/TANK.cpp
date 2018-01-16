//time		：	2016年3月31日12:54:58
//author	：	 @`13
//func		：	小游戏-炮台

#include<iostream>
#include<Windows.h>
#include<vector>
#include<time.h>

using namespace std;

class Game_paotai
{
private:

	int x;
	int y;
	int t_bul;
	int t_move;
	int t_targ;
	int p_forw;
	clock_t t_p, t_b, t_b_u, t_b_d, t_b_l, t_b_r, t_tar,t_tar_alive;
	vector <COORD> bul;
	vector <COORD> bul_U;
	vector <COORD> bul_D;
	vector <COORD> bul_L;
	vector <COORD> bul_R;
	vector <COORD> targ;
	bool flag;

public:

	//构造函数
	Game_paotai()
	{
		x = 13; y = 13;
		t_bul = 10;
		t_move = 20;
		t_targ = 20;

		flag = true;
		p_forw = 1;
		t_p = clock();
		t_b = clock();
		t_b_u = clock();
		t_b_d = clock();
		t_b_l = clock();
		t_b_r = clock();
		t_tar = clock();
		t_tar_alive = clock();
	}
	//构造函数，带参数重载
	Game_paotai(int input_x, int input_y, int input_t_bul, int input_t_move, int input_t_targ)
	{
		x = input_x;
		y = input_y;
		t_bul = input_t_bul;
		t_move = input_t_move;
		t_targ = input_t_targ;

		flag = true;
		p_forw = 1;
		t_p = clock();
		t_b = clock();
		t_b_u = clock();
		t_b_d = clock();
		t_b_l = clock();
		t_b_r = clock();
		t_tar = clock();
		t_tar_alive = clock();
	}

	void gotoxy(int x, int y)
	{
		//光标移动到指定坐标处
		HANDLE h;//句柄,对象的索引
		COORD c;//结构体,坐标值
		c.X = x;
		c.Y = y;
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}
	//清除函数
	void erase()
	{
		gotoxy(x, y);
		cout << "  ";
	}

	//绘制炮台本体函数
	int get_forward()
	{
		return p_forw;
	}
	void draw()
	{
		switch (get_forward())
		{
		case 1:
		{
				  draw_U();
				  break;
		}
		case 2:
		{
				  draw_D();
				  break;
		}
		case 3:
		{
				  draw_L();
				  break;
		}
		case 4:
		{
				  draw_R();
				  break;
		}

		}
	}
	void draw_L()
	{
		gotoxy(x, y);
		cout << "┫";
	}
	void draw_R()
	{
		gotoxy(x, y);
		cout << "┣";
	}
	void draw_U()
	{
		gotoxy(x, y);
		cout << "┻";
	}
	void draw_D()
	{
		gotoxy(x, y);
		cout << "┳";
	}

	//炮台移动函数
	void move()
	{
		if (flag == true)
		{
			draw();
			flag = false;
		}
		if (clock() - t_p > t_move)
		{
			if (GetAsyncKeyState(VK_ESCAPE)) exit(0);


			if (GetAsyncKeyState(VK_NUMPAD4))
			{
				p_forw = 3;
			}
			if (GetAsyncKeyState(VK_NUMPAD6))
			{
				p_forw = 4;
			}
			if (GetAsyncKeyState(VK_NUMPAD8))
			{
				p_forw = 1;
			}
			if (GetAsyncKeyState(VK_NUMPAD2))
			{
				p_forw = 2;
			}

			if (GetAsyncKeyState(VK_SPACE))
			{
				switch (get_forward())
				{
				case 1:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y - 1;
						  bul_U.push_back(temp);
						  break;
				}
				case 2:
				{
						  COORD temp;
						  temp.X = x; temp.Y = y + 1;
						  bul_D.push_back(temp);
						  break;
				}
				case 3:
				{
						  COORD temp;
						  temp.X = x-1; temp.Y = y ;
						  bul_L.push_back(temp);
						  break;
				}
				case 4:
				{
						  COORD temp;
						  temp.X = x+1; temp.Y = y ;
						  bul_R.push_back(temp);
						  break;
				}
				}
				
			}

			if (GetAsyncKeyState(VK_LEFT))
			{
				erase();
				--x;
				if (x < 0) x = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				erase();
				++x;
				if (x>80) x = 80;
				draw();
			}
			if (GetAsyncKeyState(VK_UP))
			{
				erase();
				--y;
				if (y < 0) y = 0;
				draw();
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				erase();
				++y;
				if (y>25) y = 25;
				draw();
			}

			flag = true;
			t_p = clock();
		}
	}

	//射击子弹函数
	void butl()
	{
		if (clock() - t_b > t_bul)
		{
			for (int i = 0; i<bul.size(); ++i)
			{
				gotoxy(bul[i].X, bul[i].Y);
				cout << "  ";
				switch (get_forward())
				{
				case 1:
				{
						  if (bul[i].Y>0)
						  {
							  --bul[i].Y;
							  gotoxy(bul[i].X, bul[i].Y);
							  cout << "*";
						  }
						  else
						  {
							  bul.erase(bul.begin() + i);
						  }
						  break;
				}
				case 2:
				{
						  if (bul[i].Y < 25)
						  {
							  ++bul[i].Y;
							  gotoxy(bul[i].X, bul[i].Y);
							  cout << "*";
						  }
						  else
						  {
							  bul.erase(bul.begin() + i);
						  }
						  break;
				}
				case 3:
				{
						  if (bul[i].X > 1)
						  {
							  --bul[i].X;
							  gotoxy(bul[i].X, bul[i].Y);
							  cout << "*";
						  }
						  else
						  {
							  bul.erase(bul.begin() + i);
						  }
						  break;
				}
				case 4:
				{
						  if (bul[i].X < 80)
						  {
							  ++bul[i].X;
							  gotoxy(bul[i].X, bul[i].Y);
							  cout << "*";
						  }
						  else
						  {
							  bul.erase(bul.begin() + i);
						  }
						  break;
				}
				}

			}
			t_b = clock();
		}
	}

	void butl_U()
	{
		if (clock() - t_b_u > t_bul)
		{
			for (int i = 0; i<bul_U.size(); ++i)
			{
				gotoxy(bul_U[i].X, bul_U[i].Y);
				cout << "  ";
				if (bul_U[i].Y>0)
				{
					--bul_U[i].Y;
					gotoxy(bul_U[i].X, bul_U[i].Y);
					cout << "|";
				}
				else
				{
					bul_U.erase(bul_U.begin() + i);
				}
			}
			t_b_u = clock();
		}
	}
	void butl_D()
	{
		if (clock() - t_b_d > t_bul)
		{
			for (int i = 0; i<bul_D.size(); ++i)
			{
				gotoxy(bul_D[i].X, bul_D[i].Y);
				cout << "  ";
				if (bul_D[i].Y<25)
				{
					++bul_D[i].Y;
					gotoxy(bul_D[i].X, bul_D[i].Y);
					cout << "|";
				}
				else
				{
					bul_D.erase(bul_D.begin() + i);
				}
			}
			t_b_d = clock();
		}
	}
	void butl_L()
	{
		if (clock() - t_b_l > t_bul)
		{
			for (int i = 0; i < bul_L .size(); ++i)
			{
				gotoxy(bul_L[i].X, bul_L[i].Y);
				cout << "  ";
				if (bul_L[i].X>0)
				{
					--bul_L[i].X;
					gotoxy(bul_L[i].X, bul_L[i].Y);
					cout << "-";
				}
				else
				{
					bul_L.erase(bul_L.begin() + i);
				}
			}
			t_b_l = clock();
		}
	}
	void butl_R()
	{
		if (clock() - t_b_r > t_bul)
		{
			for (int i = 0; i<bul_R.size(); ++i)
			{
				gotoxy(bul_R[i].X, bul_R[i].Y);
				cout << "  ";
				if (bul_R[i].X<70)
				{
					++bul_R[i].X;
					gotoxy(bul_R[i].X, bul_R[i].Y);
					cout << "-";
				}
				else
				{
					bul_R.erase(bul_R.begin() + i);
				}
			}
			t_b_r = clock();
		}
	}

	//产生射击目标函数
	void create_target()
	{

		if (clock() - t_tar > t_bul*100)
		{
			srand(time(NULL));
			COORD temp;
			temp.X = rand() % 80; temp.Y = rand() % 25;
			targ.push_back(temp);

			for (int i = 0; i<targ.size(); ++i)
			{
				gotoxy(targ[i].X, targ[i].Y);
				cout << "@";
			}
			t_tar = clock();
		}
	}

	//检查是否击中目标
	void check_target_alive()
	{
		//if (clock() - t_tar_alive > t_bul)
		//{
			//srand(time(NULL));
			for (int i = 0; i<targ.size(); ++i)
			{
				for (int i = 0; i < bul_U.size(); ++i)
				{
					if (bul_U[i].X == targ[i].X && bul_U[i].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						targ.erase(targ.begin() + i);

					}
				}
				/*for (int i = 0; i < bul_D.size(); ++i)
				{
					if (bul_D[i].X == targ[i].X && bul_D[i].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						COORD temp;
						temp.X = rand() % 80; temp.Y = rand() % 25;
						targ.push_back(temp);
					}
				}
				for (int i = 0; i < bul_L.size(); ++i)
				{
					if (bul_L[i].X == targ[i].X && bul_L[i].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						COORD temp;
						temp.X = rand() % 80; temp.Y = rand() % 25;
						targ.push_back(temp);
					}
				}
				for (int i = 0; i < bul_R.size(); ++i)
				{
					if (bul_R[i].X == targ[i].X && bul_R[i].Y == targ[i].Y)
					{
						gotoxy(targ[i].X, targ[i].Y);
						cout << "  ";
						COORD temp;
						temp.X = rand() % 80; temp.Y = rand() % 25;
						targ.push_back(temp);
					}
				}*/
				//cout << "@";
			}
			//t_b_r = clock();
		//}
		//t_tar_alive = clock();
	}

	//显示当前目标数
	void show_target_num()
	{
		gotoxy(2,29);
		cout << "Targer num:" << targ.size() << endl;
	}
};

int main(void)
{
	Game_paotai g(13,13,40,50,10);
	while (true)
	{
		g.create_target();
		g.move();
		g.butl_U();
		g.butl_D();
		g.butl_L();
		g.butl_R();
		g.check_target_alive();
		g.show_target_num();
	}
}