//time		：	2016年4月5日
//author	：	@`13
//func		：	game—entrance


//为了获得更好的显示效果，请把CMD背景色设置为白色
//请检查音频文件的位置  D盘根目录
//只有3关


#include<iostream>
#include<Windows.h>
#include<vector>
#include<time.h>
#include<string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define input_interval 200 
#define show_interval 200
#define chessboard_top 3
#define chessboard_left 2
#define count_top 4
#define count_left 40
#define help_top 10
#define help_left 40


class FLAG
{
protected:
	int _flag;

public:

	FLAG()
	{
		_flag = 0;
	}
	FLAG(int flag_num)
	{
		_flag = flag_num;
	}

	void show_flag(int _flag )
	{
		//cout <<"\t"<< _flag;
		if (_flag == 0)
		{
			cout << "  ";
			return;
		}
		else if (_flag / 1000 == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
				| FOREGROUND_RED);
			cout << "⊙";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			return;
		}
		else if (_flag / 10%10 == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_GREEN);
			cout << "X";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		} 
		
		else if (_flag / 100 %10 == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE |FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			cout << "◆";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			return;
		}
		
		else if (_flag % 10 == 1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY
				 | FOREGROUND_GREEN);
			cout << "○";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
				| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		}
		else
		{
			cout << "  ";
			return;
		}
	}
	friend ostream& operator<< (ostream& os, FLAG temp)
	{
		temp.show_flag(temp._flag);
		return os;
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
};

void gotoxy(int x, int y)
{
	HANDLE h;
	COORD c;
	c.X = x;
	c.Y = y;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

void messy_code()
{
	//#MAX messy_code_num = 10;

	int i;
	i = rand() % 26;

	switch (i)
	{
	case(1) :
	{
				cout << "@";
				break;
	}
	case(2) :
	{
				cout << "#";
				break;
	}
	case(3) :
	{
				cout << "$";
				break;
	}
	case(4) :
	{
				cout << "%";
				break;
	}
	case(5) :
	{
				cout << "^";
				break;
	}
	case(6) :
	{
				cout << "&";
				break;
	}
	case(7) :
	{
				cout << "*";
				break;
	}
	case(8) :
	{
				cout << "-";
				break;
	}
	case(9) :
	{
				cout << "=";
				break;
	}
	case(11) :
	{
				 cout << "/";
				 break;
	}
	case(12) :
	{
				 cout << "a";
				 break;
	}
	case(13) :
	{
				 cout << "b";
				 break;
	}
	case(14) :
	{
				 cout << "c";
				 break;
	}
	case(15) :
	{
				 cout << "d";
				 break;
	}
	case(16) :
	{
				 cout << "e";
				 break;
	}
	case(17) :
	{
				 cout << "f";
				 break;
	}
	case(18) :
	{
				 cout << "g";
				 break;
	}
	case(19) :
	{
				 cout << "h";
				 break;
	}
	case(20) :
	{
				 cout << "j";
				 break;
	}
	case(21) :
	{
				 cout << "w";
				 break;
	}
	case(22) :
	{
				 cout << "r";
				 break;
	}
	case(23) :
	{
				 cout << "t";
				 break;
	}
	case(24) :
	{
				 cout << "x";
				 break;
	}
	case(25) :
	{
				 cout << "n";
				 break;
	}

	}
}

void output_messy_code(int x, int y, int i, int length, int timer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
		| FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int l;
	int j = 10;
	int time = timer;
	clock_t t;
	t = clock();
	while (j--)
	{
		if (clock() - t > timer)
		{
			for (l = 0; l <= length; ++l)
			{
				gotoxy(x + i + l + 2, y);
				messy_code();
				gotoxy(x + i + l + 3, y);
			}
			gotoxy(x, y + 1);
			t = clock();
		}
		else
		{
			++j;
		}
	}

}

void output_messy_code_W(int x, int y, int i, int length, int timer)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
		| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE );
	int l;
	int j = 10;
	int time = timer;
	clock_t t;
	t = clock();
	while (j--)
	{
		if (clock() - t > timer)
		{
			for (l = 0; l <= length; ++l)
			{
				gotoxy(x + i + l + 2, y);
				messy_code();
				gotoxy(x + i + l + 3, y);
			}
			gotoxy(x, y + 1);
			t = clock();
		}
		else
		{
			++j;
		}
	}

}

//输出乱码动画函数 (阻塞)
//绿色
//参数说明
// sent：需要生成的字符串，x 屏幕x轴坐标 ，y 屏幕y轴坐标，time 乱码动画持续时间（毫秒 数字越小，动画越快）
void animation_messy_code_G_B(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
			| FOREGROUND_GREEN);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//红色
void animation_messy_code_R_B(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
			| FOREGROUND_RED);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//蓝色
void animation_messy_code_B_B(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
			| FOREGROUND_BLUE | FOREGROUND_GREEN);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//绿色
void animation_messy_code_G_W(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
			| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY
			| FOREGROUND_GREEN);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code_W(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//红色
void animation_messy_code_R_W(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
			| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| FOREGROUND_INTENSITY
			| FOREGROUND_RED);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code_W(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//蓝色
void animation_messy_code_B_W(string sent, int x, int y, int time)
{
	int i;
	for (i = 0; i < sent.size(); ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY
			| BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE|FOREGROUND_INTENSITY
			| FOREGROUND_BLUE | FOREGROUND_GREEN);
		gotoxy(x + i, y);
		cout << sent[i] << " ";
		output_messy_code_W(x, y, i, sent.size() - i, time);
	}
	gotoxy(x + sent.size() + 1, y);
	cout << "    ";

}
//渐变文字动画
void animation_change_code(char sent[], int input_x, int input_y, int time)
{
	clock_t t = clock();
	HANDLE  setcolor;
	setcolor = GetStdHandle(STD_OUTPUT_HANDLE);
	int color_code;

	while (true)
	{
		color_code = rand() % 15 + 240;
		SetConsoleTextAttribute(setcolor, color_code);
		gotoxy(input_x, input_y);
		cout << sent << endl;
		Sleep(100);
		if (clock() - t > time)
		{
			break;
		}
	}

	SetConsoleTextAttribute(setcolor, 240);
	gotoxy(input_x, input_y);
	cout << sent << endl;
	Sleep(200);

	SetConsoleTextAttribute(setcolor, 248);
	gotoxy(input_x, input_y);
	cout << sent << endl;
	Sleep(500);

	SetConsoleTextAttribute(setcolor, 247);
	gotoxy(input_x, input_y);
	cout << sent << endl;
	Sleep(500);

	SetConsoleTextAttribute(setcolor, 255);
	gotoxy(input_x, input_y);
	cout << sent << endl;
	Sleep(500);
}

class Game_chess :public FLAG
{
protected:

	int _flag[8][8];
	int x, y;
	int move_x, move_y;
	int move_count;
	int life;
	int quene_x, quene_y;
	bool show_flag;
	bool show_menu_flag;
	bool setting_menu_flag;
	bool show_menu_setting_flag;
	


	clock_t t_draw;
	clock_t t_input;
	clock_t t_time;
	clock_t t_menu_draw;
	clock_t t_menu_input;
	clock_t t_menu_setting_draw;
	clock_t t_menu_setting_input;
	int time;
	int level;
	int menu[4];
	int now_menu_setting;
	int menu_setting[2];
	int now_menu;
	int menu_finsh;

	MCIDEVICEID  dev[10];
	MCI_OPEN_PARMS mciOpen;
	MCI_PLAY_PARMS mciPlay;

public:

	bool BGM_switch;
	bool EM_switch;
	Game_chess()
	{
		int i, j;
		for (i = 0; i < 8; ++i)
		{
			for (j = 0; j < 8; ++j)
			{
				_flag[i][j] = 0;
			}
		}


		x = 1;
		y = 1;

		life = 15;

		move_x = 0;
		move_y = 0;
		_flag[move_x][move_y] = 10;

		t_draw = clock();
		t_input = clock();
		t_time = clock();
		t_menu_input = clock();
		t_menu_draw = clock();
		t_menu_setting_input = clock();
		t_menu_setting_draw = clock();
		
		

		time = 0;

		show_flag = true;
		show_menu_flag = true;
		BGM_switch = true;
		EM_switch = true;
		show_menu_setting_flag = true;
		menu_finsh = 0;
		setting_menu_flag = 0;
		move_count = 0;
		now_menu = 0;
		menu[0] = 1;
		menu[1] = 0;
		menu[2] = 0;
		menu[3] = 0;
		menu[4] = 0;
		now_menu_setting = 1;
		menu_setting[0] = 1;
		menu_setting[1] = 0;


	}

	void set_quene(int input_x, int input_y)
	{
		quene_x = input_x -1;
		quene_y = input_y -1;
		_flag[quene_x][quene_y] = 1000;
	}

	void set_pawn(int input_x, int input_y)
	{
		_flag[input_x - 1][input_y - 1] = 100;
	}

	void set_life(int input_life)
	{
		life = input_life;
	}

	void set_level(int input_level)
	{
		level = input_level;
	}

	void show_level()
	{
		gotoxy(chessboard_top, chessboard_left-1);
		cout << "		LEVEL - " << level;
	}

	void erase_all()
	{
		int i;
		for (i = 0; i < 30; i++)
		{
			gotoxy(i, 0);
			cout << " ";
		}
	}

	void show_chessboard()
	{
		gotoxy(chessboard_top, chessboard_left);
		cout << "   A   B   C   D   E   F   G   H" << endl;
		gotoxy(chessboard_top, chessboard_left + 1);
		cout << " ┏━━┳━━┳━━┳━━┳━━┳━━┳━━┳━━┓" << endl;
		gotoxy(chessboard_top, chessboard_left + 2);
		cout << "1┃" << FLAG(_flag[0][0]) << "┃" << FLAG(_flag[0][1]) << "┃" << FLAG(_flag[0][2]) << "┃" << FLAG(_flag[0][3]) << "┃" << FLAG(_flag[0][4]) << "┃" << FLAG(_flag[0][5]) << "┃" << FLAG(_flag[0][6]) << "┃" << FLAG(_flag[0][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 3);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 4);
		cout << "2┃" << FLAG(_flag[1][0]) << "┃" << FLAG(_flag[1][1]) << "┃" << FLAG(_flag[1][2]) << "┃" << FLAG(_flag[1][3]) << "┃" << FLAG(_flag[1][4]) << "┃" << FLAG(_flag[1][5]) << "┃" << FLAG(_flag[1][6]) << "┃" << FLAG(_flag[1][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 5);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 6);
		cout << "3┃" << FLAG(_flag[2][0]) << "┃" << FLAG(_flag[2][1]) << "┃" << FLAG(_flag[2][2]) << "┃" << FLAG(_flag[2][3]) << "┃" << FLAG(_flag[2][4]) << "┃" << FLAG(_flag[2][5]) << "┃" << FLAG(_flag[2][6]) << "┃" << FLAG(_flag[2][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 7);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 8);
		cout << "4┃" << FLAG(_flag[3][0]) << "┃" << FLAG(_flag[3][1]) << "┃" << FLAG(_flag[3][2]) << "┃" << FLAG(_flag[3][3]) << "┃" << FLAG(_flag[3][4]) << "┃" << FLAG(_flag[3][5]) << "┃" << FLAG(_flag[3][6]) << "┃" << FLAG(_flag[3][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 9);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 10);
		cout << "5┃" << FLAG(_flag[4][0]) << "┃" << FLAG(_flag[4][1]) << "┃" << FLAG(_flag[4][2]) << "┃" << FLAG(_flag[4][3]) << "┃" << FLAG(_flag[4][4]) << "┃" << FLAG(_flag[4][5]) << "┃" << FLAG(_flag[4][6]) << "┃" << FLAG(_flag[4][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 11);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 12);
		cout << "6┃" << FLAG(_flag[5][0]) << "┃" << FLAG(_flag[5][1]) << "┃" << FLAG(_flag[5][2]) << "┃" << FLAG(_flag[5][3]) << "┃" << FLAG(_flag[5][4]) << "┃" << FLAG(_flag[5][5]) << "┃" << FLAG(_flag[5][6]) << "┃" << FLAG(_flag[5][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 13);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 14);
		cout << "7┃" << FLAG(_flag[6][0]) << "┃" << FLAG(_flag[6][1]) << "┃" << FLAG(_flag[6][2]) << "┃" << FLAG(_flag[6][3]) << "┃" << FLAG(_flag[6][4]) << "┃" << FLAG(_flag[6][5]) << "┃" << FLAG(_flag[6][6]) << "┃" << FLAG(_flag[6][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 15);
		cout << " ┣━━╋━━╋━━╋━━╋━━╋━━╋━━╋━━┫" << endl;
		gotoxy(chessboard_top, chessboard_left + 16);
		cout << "8┃" << FLAG(_flag[7][0]) << "┃" << FLAG(_flag[7][1]) << "┃" << FLAG(_flag[7][2]) << "┃" << FLAG(_flag[7][3]) << "┃" << FLAG(_flag[7][4]) << "┃" << FLAG(_flag[7][5]) << "┃" << FLAG(_flag[7][6]) << "┃" << FLAG(_flag[7][7]) << "┃" << endl;
		gotoxy(chessboard_top, chessboard_left + 17);
		cout << " ┗━━┻━━┻━━┻━━┻━━┻━━┻━━┻━━┛" << endl;
	}

	void show_help()
	{
		gotoxy(help_left, help_top);
		cout << "Tips:";
		gotoxy(help_left, help_top+2);
		cout << "⊙	：后";
		gotoxy(help_left, help_top+4);
		cout << "◆	：兵";
		gotoxy(help_left, help_top+6);
		cout << "○	：后可移动的位置";

	}

	void show_count()
	{
		if (clock() - t_time > 1000)
		{
			time += 1;
			t_time = clock();
		}
		
		gotoxy(count_left, count_top );
		cout << "C H E S S";
		gotoxy(count_left, count_top+2);
		cout << "Game time	:\t" << time;
		gotoxy(count_left, count_top + 3);
		cout << "                                      ";
		gotoxy(count_left, count_top + 3);
		cout << "Game chance	:\t" << life - move_count;
	}

	void draw()
	{
		if (show_flag == true)
		{
			show_level();
			show_count();
			show_help();
			move_available();
			show_chessboard();
			move_available_fresh();
			show_flag = false;
		}
		if (clock() - t_draw > show_interval)
		{
			erase_all();
			show_flag = true;
			t_draw = clock();
		}
	}

	void move()
	{
		if (clock() - t_input > input_interval)
		{
			if (GetAsyncKeyState(VK_LEFT))
			{
				if (move_y >= 1)
				{
					_flag[move_x][move_y] -= 10;
					move_y -= 1;
					_flag[move_x][move_y] += 10;
				}

			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				if (move_y <= 6)
				{
					_flag[move_x][move_y] -= 10;
					move_y += 1;
					_flag[move_x][move_y] += 10;
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (move_x >= 1)
				{
					_flag[move_x][move_y] -= 10;
					move_x -= 1;
					_flag[move_x][move_y] += 10;
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (move_x <= 6)
				{
					_flag[move_x][move_y] -= 10;
					move_x += 1;
					_flag[move_x][move_y] += 10;
				}
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (quene_x == move_x || quene_y == move_y || (quene_x - move_x) == (quene_y - move_y) || (quene_x - move_x) == -(quene_y - move_y))
				{
					effect_sound_move();
					++move_count;
					_flag[quene_x][quene_y] -= 1000;
					quene_x = move_x; quene_y = move_y;
					_flag[quene_x][quene_y] += 1000;

					if ((_flag[quene_x][quene_y] - 1000) / 100 == 1)
					{
						//cout << "catch!";
						_flag[quene_x][quene_y] -= 100;
					}

				}
			}

			t_input = clock();
		}
	}

	void move_available()
	{
		int i, j;

		//横向
		for (i = 0; i <= 7; ++i)
		{
			if (_flag[i][quene_y] % 10 == 0)
			{
				_flag[i][quene_y] += 1;
			}
		}

		//竖向
		for (j = 0; j <= 7; ++j)
		{
			if (_flag[quene_x][j] % 10 == 0)
			{
				_flag[quene_x][j] += 1;
			}
		}

		//右下斜
		for (i = quene_x+1, j = quene_y+1; i <= 7 &&j <= 7; ++i, ++j)
		{
			if (_flag[i][j] % 10 == 0)
			{
				_flag[i][j] += 1;
			}
		}

		//左上斜
		for (i = quene_x, j = quene_y; i >= 0 && j >= 0; --i, --j)
		{
			if (_flag[i][j] % 10 == 0)
			{
				_flag[i][j] += 1;
			}
		}

		//右上斜
		for (i = quene_x, j = quene_y; i <= 7 && j >= 0; ++i, --j)
		{
			if (_flag[i][j] % 10 == 0)
			{
				_flag[i][j] += 1;
			}
		}

		//左下斜
		for (i = quene_x, j = quene_y; i >= 0 && j <= 7; --i, ++j)
		{
			if (_flag[i][j] % 10 == 0)
			{
				_flag[i][j] += 1;
			}
		}
	}

	void move_available_fresh()
	{
		int i, j;
		for (i = 0; i <= 7; ++i)
		{
			for (j = 0; j <= 7; ++j)
			{
				if (_flag[i][j] % 10 == 1)
					_flag[i][j] -= 1;
			}
		}
	}

	int check_alive()
	{
		int i, j;
		for (i = 0; i <= 7; i++)
		{
			for (j = 0; j < +7; j++)
			{
				if (_flag[i][j] < 1000 && _flag[i][j] / 100 % 10 == 1)
					return 1;
			}
		}
		return 0;		
	}

	int check_finsh()
	{
		if (move_count >= life)
		{
			return 1;
		}

		if (!check_alive())
		{
			return 0;
		}
		
		return 100;

	}

	void effect_sound_move()
	{
		// if (!EM_switch)
		// 	return;
		// mciOpen.lpstrElementName = L"D:\\move.wav";
		// if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT,
		// 	(DWORD)&mciOpen) == 0)
		// 	dev[1] = mciOpen.wDeviceID;
		// else
		// 	mciOpen.wDeviceID = dev[1];

		// mciPlay.dwFrom = 0;
		// mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
	}

	void effect_sound_win()
	{
	// 	if (!EM_switch)
	// 		return;
	// 	mciOpen.lpstrElementName = L"D:\\win.wav";
	// 	if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT,
	// 		(DWORD)&mciOpen) == 0)
	// 		dev[2] = mciOpen.wDeviceID;
	// 	else
	// 		mciOpen.wDeviceID = dev[2];

	// 	mciPlay.dwFrom = 0;
	// 	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
	// 
	}

	void effect_sound_finsh()
	{
		// if (!EM_switch)
		// 	return;
		// mciOpen.lpstrElementName = L"D:\\finsh.wav";
		// if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT,
		// 	(DWORD)&mciOpen) == 0)
		// 	dev[3] = mciOpen.wDeviceID;
		// else
		// 	mciOpen.wDeviceID = dev[3];

		// mciPlay.dwFrom = 0;
		// mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
	}

	void effect_sound_over()
	{
		// if (!EM_switch)
		// 	return;
		// mciOpen.lpstrElementName = L"D:\\lose.wav";
		// if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT,
		// 	(DWORD)&mciOpen) == 0)
		// 	dev[4] = mciOpen.wDeviceID;
		// else
		// 	mciOpen.wDeviceID = dev[4];

		// mciPlay.dwFrom = 0;
		// mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
	}

	void background_music()
	{
		// if (!BGM_switch)
		// 	return;
		// mciOpen.lpstrElementName = L"D:\\A.wav";
		// if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT,
		// 	(DWORD)&mciOpen) == 0)
		// 	dev[0] = mciOpen.wDeviceID;
		// else
		// 	mciOpen.wDeviceID = dev[0];

		// mciPlay.dwFrom = 0;
		// mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD)&mciPlay);
	}

	void menu_move()
	{
		if (clock() - t_menu_input > input_interval)
		{
			if (GetAsyncKeyState(VK_UP))
			{
				if (now_menu > 0)
				{
					menu[now_menu] = 0;
					now_menu -= 1;
					menu[now_menu] = 1;
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (now_menu < 3)
				{
					
					menu[now_menu] = 0;
					now_menu += 1;
					menu[now_menu] = 1;	
					//cout << "test:nowmenu" << now_menu << "menu" << menu[now_menu];
				}
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (now_menu == 0)
				{
					menu_finsh = 1;
				}
				
				else if(now_menu == 1)
				{
					game_instruction();
				}
				
				else if(now_menu == 2)
				{
					setting_menu_flag = 0;
					game_setting();
				}
				else if(now_menu == 3)
				{
					game_about();
				}
			}

			t_menu_input = clock();
		}
	}

	void draw_menu()
	{
		gotoxy(0, 0);
		cout << "	****************************************" << endl;
		cout << "	***           C H E S S - menu        **	" << endl;
		cout << "	****************************************" << endl << endl << endl;

		//◇◆
		cout << "          ";
		if (menu[0] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【1】	开始游戏" << endl;

		cout << "          ";
		if (menu[1] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【2】	游戏说明" << endl;

		cout << "          ";
		if (menu[2] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【3】	游戏选项" << endl;

		cout << "          ";
		if (menu[3] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【4】	关于游戏" << endl<<endl;

		cout << "	****************************************" << endl;
		cout << "	***	                  author:`13  **" << endl;
		cout << "	****************************************" << endl;


		
	}

	int check_menu_finsh()
	{
		return 	menu_finsh;
	}

	void game_instruction()
	{
		system("cls");
		cout << "	****************************************" << endl;
		cout << "	***           C H E S S - menu        **	" << endl;
		cout << "	****************************************" << endl << endl << endl;

		while (true)
		{	
			if (GetAsyncKeyState(VK_ESCAPE))
				return;
		}

	}

	void game_setting()
	{
		while (true)
		{
			show_setting();
			move_setting();
			if (setting_menu_flag)
			{
				system("cls");
				break;
			}
		}

	}

	void draw_setting()
	{
		gotoxy(0, 0);
		cout << "	****************************************" << endl;
		cout << "	***           C H E S S - menu        **	" << endl;
		cout << "	****************************************" << endl << endl << endl;

		//◇◆
		cout << "          ";
		if (menu_setting[0] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【1】	背景音乐开关：";
		if (BGM_switch)
			cout << "   开启中" << endl;
		else
			cout << "   关闭中" << endl;

		cout << "          ";
		if (menu_setting[1] == 0)
			cout << "◇";
		else
			cout << "◆";

		cout << "	【2】	音效音乐开关：" ;
		if (EM_switch)
			cout << "   开启中" << endl;
		else
			cout << "   关闭中" << endl;

	}

	void show_setting()
	{
		if (show_menu_setting_flag == true)
		{
			draw_setting();
			show_menu_setting_flag = false;
		}
		if (clock() - t_menu_setting_draw > show_interval)
		{
			system("cls");
			show_menu_setting_flag = true;
			t_menu_setting_draw = clock();
		}
	}

	void move_setting()
	{

		if (clock() - t_menu_setting_input > input_interval)
		{	
			if (GetAsyncKeyState(VK_ESCAPE))
				setting_menu_flag = 1;

			if (GetAsyncKeyState(VK_UP))
			{
				if (now_menu_setting ==1)
				{
					now_menu_setting = 0;
					menu_setting[0] = 1;
					menu_setting[1] = 0;
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (now_menu_setting ==0)
				{
					menu_setting[now_menu_setting] = 0;
					++now_menu_setting;
					menu_setting[now_menu_setting] = 1;
				}
			}
			if (GetAsyncKeyState(VK_SPACE))
			{
				if (menu_setting[0] == 1)
					BGM_switch = !BGM_switch;

				if (menu_setting[1] == 1)
					EM_switch = !EM_switch;
			}

			t_menu_setting_input = clock();
		}	
	}

	void game_about()
	{
		system("cls");
		cout << "	****************************************" << endl;
		cout << "	***           C H E S S - menu        **	" << endl;
		cout << "	****************************************" << endl << endl << endl;

		while (true)
		{
			if (GetAsyncKeyState(VK_ESCAPE))
				return;
		}

	}

	void show_menu()
	{
		if (show_menu_flag == true)
		{
			draw_menu();
			show_menu_flag = false;
		}
		if (clock() - t_menu_draw > show_interval)
		{
			erase_all();
			show_menu_flag = true;
			t_menu_draw = clock();
		}
	}
	
};





int main(void)
{
	//char welcome[1000] = "***************************************************\n*												  *\n*        										  *\n*		 C       H      E       S      S		  \n*												  *\n*												  *\n***************************************************\n\n	 Please input anykey to start:\n\n***************************************************\n";
	//animation_change_code(welcome, 0, 0, 5000);


	cout << "Loading...";
	Game_chess g,g1,g2,g3;

	system("title C H E S S");
	while (true)
	{
		g.show_menu();
		g.menu_move();
		if (g.check_menu_finsh())
		{
			g.erase_all();
			break;
		}
	}
	system("cls");
	g.background_music();

	system("cls");
	g1.BGM_switch = g.BGM_switch;
	g1.EM_switch = g.EM_switch;
	g1.set_level(1);
	g1.set_life(13);
	g1.set_quene(8, 4);
	g1.set_pawn(8, 6);
	g1.set_pawn(7, 1);
	g1.set_pawn(7, 4);
	g1.set_pawn(6, 6);
	g1.set_pawn(5, 4);
	g1.set_pawn(4, 2);
	g1.set_pawn(4, 8);
	g1.set_pawn(2, 2);
	g1.set_pawn(2, 7);
	while (true)
	{

		g1.draw();
		g1.move();

		if (g1.check_finsh() == 1)
		{
			g1.effect_sound_finsh();
			system("cls");
			string end = "Game over";
			animation_messy_code_B_W(end, 5, 5, 50);
			system("pause");
			exit(-1);
			break;
		}
		if (g1.check_finsh() == 0)
		{
			g1.effect_sound_win();
			break;
		}
	}


	system("cls");
	g2.BGM_switch = g.BGM_switch;
	g2.EM_switch = g.EM_switch;
	g2.set_level(2);
	g2.set_life(14);
	g2.set_quene(8, 4);
	g2.set_pawn(7, 3);
	g2.set_pawn(7, 7);
	g2.set_pawn(6, 5);
	g2.set_pawn(6, 6);
	g2.set_pawn(5, 3);
	g2.set_pawn(5, 4);
	g2.set_pawn(5, 5);
	g2.set_pawn(4, 5);
	g2.set_pawn(4, 6);
	g2.set_pawn(3, 5);
	while (true)
	{

		g2.draw();
		g2.move();

		if (g2.check_finsh() == 1)
		{
			g1.effect_sound_finsh();
			system("cls");
			string end = "Game over";
			animation_messy_code_B_W(end, 5, 5, 50);
			system("pause");
			exit(-1);
			break;
		}
		if (g2.check_finsh() == 0)
		{
			g1.effect_sound_win();
			break;
		}
	}


	system("cls");
	g3.BGM_switch = g.BGM_switch;
	g3.EM_switch = g.EM_switch;
	g3.set_level(3);
	g3.set_life(14);
	g3.set_quene(8, 4);
	g3.set_pawn(8, 2);
	g3.set_pawn(8, 6);
	g3.set_pawn(7, 1);
	g3.set_pawn(7, 6);
	g3.set_pawn(5, 4);
	g3.set_pawn(4, 2);
	g3.set_pawn(4, 5);
	g3.set_pawn(3, 6);
	g3.set_pawn(2, 5);
	g3.set_pawn(1, 1);
	while (true)
	{

		g3.draw();
		g3.move();

		if (g3.check_finsh() == 1)
		{
			g1.effect_sound_finsh();
			system("cls");
			string end = "Game over";
			animation_messy_code_B_W(end, 5, 5, 50);
			system("pause");
			exit(-1);
			break;
		}
		if (g3.check_finsh() == 0)
		{
			g1.effect_sound_win();
			break;
		}
	}


	system("cls");
	string sent = "YOU WIN! BUT THIS LITTLE GAME IS NOT FINSH SORRY";
	animation_messy_code_R_W(sent, 2, 2, 50);		
	system("pause");
}


