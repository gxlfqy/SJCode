#ifndef __CHARCIRCULARLIST_H_INCLUDED__
#define __CHARCIRCULARLIST_H_INCLUDED__
#include <string>

class CharCircularList
{
protected:
	//ͨ�ýڵ�
	typedef struct node
	{
		node * next;
		std::string data;
		node() :next(nullptr){}
		node(std::string d) :next(nullptr), data(d){}
	}*pnode;
	pnode m_rear;			//βָ��
	int m_length;			//�ڵ����
	//�ͷŽڵ�p(�����ڵ�p)֮��Ľڵ�, ֱ��β�ڵ�
	void free(pnode p)
	{
		//ʹ�õݹ������ͷŽڵ�������Ŀռ�
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
		//�½�һ���µĽڵ�, ����ʼ���ڵ�
		pnode newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//�жϱ��Ƿ�Ϊ�ձ�, �����һ���ձ�, ���½��Ľڵ���Ϊ��ĵ�һ���ڵ�
		//�����Ϊ��, ���½��Ľڵ���ӵ������β��
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