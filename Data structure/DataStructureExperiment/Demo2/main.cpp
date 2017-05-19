#include <iostream>
#include <stack>
#include <cstdlib>
#include <malloc.h>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef Q_ERROR
#define Q_ERROR 0
#endif
#ifndef Q_OK
#define Q_OK 1
#endif
#ifndef Q_STATUS
#define Q_STATUS int
#endif

/** 数据结构实验-章2
 * authro : @`13
 * time   : 2016年11月5日
 * */

template<class ElementType>    // 使用类模板
class QueneByLinkedList
/** 用链表实现队列及其基本操作 */
{
private:
    struct ListNode {   //　链表构造
        ElementType val;
        ListNode *next;

        ListNode(ElementType x) : val(x), next(NULL) {}
    };

    ListNode *Q;        //  链表指针
    int Q_length;       //  队列长度

public:
    QueneByLinkedList()
    /** 构造函数 */
    { Q_length = 0; }

    int length()
    /** 返回链表长度 */
    { return Q_length; }

    bool qempty()
    /** 判断链表是否为空　*/
    { return Q_length == 0; }

    Q_STATUS push(ElementType e)
    /** 入队操作 */
    {
        ListNode* tmp;
        tmp = (ListNode *) malloc(sizeof(ListNode));
        if (!tmp)   //　错误检查
            return Q_ERROR;
        tmp->val = e, tmp->next = NULL;
        if(Q_length)    //　不是唯一节点
        {
            ListNode* tmp2 = Q;
            while(tmp2->next)
                tmp2 = tmp2->next;    // 找到尾节点
            tmp2->next = tmp;         // 在尾部插入节点
        }
        else            //  是唯一节点
            Q = tmp;
        Q_length++;
        return Q_OK;
    }

    ElementType front()
    /** 返回队首元素 */
    {return Q->val; }

    void pop()
    /** 出队操作 */
    {
        ListNode* tmp = Q;
        Q = Q->next; // 链表指针后移
        free(tmp);   // 删除头节点
        Q_length--;
    }

    ~QueneByLinkedList()
    /** 析构函数　*/
    { free(Q); }
};

class bracketMatching
/** 括号匹配检验 */
{
protected:
    stack<char> _bracket_S; //括号栈

    void _empytStack()
    /** 清空括号栈　*/
    {
        while(!_bracket_S.empty())
            _bracket_S.pop();
    }
public:
    bracketMatching(){} //空构造函数

    bool match(string bracketString)
    /**　验证括号是否匹配
     * 　是-返回true,不是－返回false */
    {
        _empytStack();
        long l = bracketString.length();    // length()方法返回值为long类型
        int i = 0;                          // 用于遍历字符串的游标
        while(l--)
        {
            if(bracketString[i] == '(')     // 遇见左括弧
                _bracket_S.push('(');
            else if(bracketString[i] == ')')// 遇见右括弧
            {
                if(!_bracket_S.empty())
                {
                    if (_bracket_S.top()=='(')
                        _bracket_S.pop();
                    else return false;
                }
                else return false;
            }
            else    // 其他符号
            {
                cout<<"输入了非法的括号字符串!退出"<<endl;
                exit(-1);
            }
            i++;    //　移动到下一位置
        }
        return true;
    }
};

class infix2suffix:private bracketMatching

/** 中缀表达式转后缀表达式　*/
{
protected:
    bool _isdigit(char d)
    /** 检查一个字符串是否是数字 */
    {return (d>='0'&&d<='9');}

    int _symbolCheck(char d)
    /** 检查输入的符号及其优先级
     * 0-非法，1-加减 2-乘除 3-( 4-) */
    {
        if(d=='+'||d=='-')
            return 1;
        else if(d=='*'||d=='/')
            return 2;
        else if(d=='(')
            return 3;
        else if(d==')')
            return 4;
        else
            return 0;
    }

public:
    infix2suffix(){} //空构造函数
    string i2s(string expression)
    /**　将中缀表达式转化为后缀表达式 */
    {   // 没有检查表达式是否正确，一律按正确处理
        _empytStack();
        long l = expression.length();       // length()方法返回值为long类型
        int i = 0;                          // 用于遍历字符串的游标
        string res = "";
        while(l--)
        {
            if(_isdigit(expression[i]))     // 判断是否是数字
                res += expression[i];   // 数字则加入
            else
                switch(_symbolCheck(expression[i]))
                {
                    case 1:
                    {
                        if (!_bracket_S.empty()) // 栈非空
                        {
                            if (_symbolCheck(expression[i]) == 2)
                                while (!_bracket_S.empty()) {
                                    res += _bracket_S.top();
                                    _bracket_S.pop();
                                }
                        } else
                            _bracket_S.push(expression[i]);
                        break;
                    }
                    case 2:
                    {
                        _bracket_S.push(expression[i]);
                        break;
                    }
                    case 3:
                    {
                        _bracket_S.push(expression[i]);
                        break;
                    }
                    case 4:
                    {
                        while(!_bracket_S.empty())
                        {
                            if(_symbolCheck(expression[i])==3)  //输出到左括号
                            {
                                //res += _bracket_S.top();
                                _bracket_S.pop();
                                break;
                            }

                            else
                            {
                                res += _bracket_S.top();
                                _bracket_S.pop();
                            }
                        }
                    }


                }
            i++;    //　移动到下一位置
        }
        while(!_bracket_S.empty())  //输出栈内元素
        {
            res += _bracket_S.top();
            _bracket_S.pop();
        }
        return res;
    }
};

// 之前编辑文件出现乱码
// 凭记忆重写医生模拟类
// 无注释

class doctorSimu
{
private:
	int _p_n;
	int _p_wt;
	int _t;
	int _d_ft;

public:
	doctorSimu()
	{
		_p_n = 0, _p_wt = 0, _t = 0，_d_ft = 0;
	}

	void pc(int ct, int vt)
	{
		++_p_n;
		if (_t > ct)
		{
			_p_wt += (_t - ct);
			_t += (ct + vt);
		}
		else
		{
			_d_ft += _t - ct;
			_t = ct + vt;

		}
	}

	void gr()
	{
		int avt_p_wt = _p_wt / _p_n;
	}
};

int main(void) {
    bracketMatching M;
    if(M.match("((()))"))
        cout << "Hello, World!" << endl;
    return 0;
}