#ifndef __CHARCIRCULARLIST_H_INCLUDED__
#define __CHARCIRCULARLIST_H_INCLUDED__
#include <string>

class CharCircularList
{
protected:
	//通用节点
	typedef struct node
	{
		node * next;
		std::string data;
		node() :next(nullptr){}
		node(std::string d) :next(nullptr), data(d){}
	}*pnode;
	pnode m_rear;			//尾指针
	int m_length;			//节点个数
	//释放节点p(包括节点p)之后的节点, 直到尾节点
	void free(pnode p)
	{
		//使用递归依次释放节点所申请的空间
		if (nullptr != p)
		{
			if (m_rear != p)
				free(p->next);
			p->next = nullptr;
			delete p;
		}
	}

public:
	enum charmode{
		modeAlphabet = 0,
		modeDigital,
		modeOther,
		modeAll
	} m_mode;
	CharCircularList(charmode m) :m_mode(m), m_rear(nullptr), m_length(0){}
	~CharCircularList()
	{
		reset();
	}
	void reset()
	{
		free(m_rear->next);
		m_rear = nullptr;
		m_length = 0;
	}
	bool add(std::string data)
	{
		if (!data.empty())
		{
			const char * buffer = data.c_str();
			int i, len = strlen(buffer);
			for (i = 0; i < len; ++i)
			{
				switch (m_mode)
				{
				case CharCircularList::modeAlphabet:
					if (!isalpha(buffer[i]))
						goto False;
					break;
				case CharCircularList::modeDigital:
					if (!isdigit(buffer[i]))
						goto False;
					break;
				case CharCircularList::modeOther:
					if (isalpha(buffer[i]) || isdigit(buffer[i]))
						goto False;
				case CharCircularList::modeAll:
					if (!isprint(buffer[i]))
						goto False;
					break;
				}
			}
		}
		//新建一个新的节点, 并初始化节点
		pnode newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//判断表是否为空表, 如果是一个空表, 则将新建的节点作为表的第一个节点
		//如果表不为空, 将新建的节点添加到链表的尾部
		if (nullptr == m_rear)
		{
			m_rear = newnode;
			newnode->next = m_rear;
		}
		else
		{
			newnode->next = m_rear->next;
			m_rear->next = newnode;
			m_rear = newnode;
		}
		++m_length;
		return true;

	False:
		return false;
	}

};

#endif