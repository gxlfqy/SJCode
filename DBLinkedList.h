#ifndef __DBLINKEDLIST_H_INCLUDED__
#define __DBLINKEDLIST_H_INCLUDED__

template<typename T>
class DBLinkedList
{
protected:
	typedef struct node
	{
		//ע��, ��������Ա���ܵߵ�
		node * next;
		T data;
		node * prev;
		node() :next(nullptr), prev(nullptr) {}
		node(T d) :next(nullptr), prev(nullptr), data(d) {}
	}*pnode;
	pnode m_head;		//ͷָ��
	pnode m_rear;		//βָ��
	int m_length;		//����
	void free(pnode p)
	{
		//ʹ�õݹ������ͷŽڵ�������Ŀռ�
		if (nullptr != p)
		{
			if (nullptr != p->next)
			{
				free(p->next);
				p->next = nullptr;
				p->prev = nullptr;
			}
			delete p;
		}
	}

public:
	LinkedList() :m_head(nullptr), m_rear(nullptr), m_length(0) {}
	~LinkedList()
	{
		reset();
	}
	void reset()
	{
		if (nullptr != m_head)
		{
			free(m_head);
			m_head = nullptr;
		}
		m_rear = nullptr;
		m_length = 0;
	}
	bool add(T data)
	{
		//�½�һ���µĽڵ�, ����ʼ���ڵ�
		pnode newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//�жϱ��Ƿ�Ϊ�ձ�, �����һ���ձ�, ���½��Ľڵ���Ϊ��ĵ�һ���ڵ�
		//�����Ϊ��, ���½��Ľڵ���ӵ������β��
		if (nullptr == m_head)
			m_rear = m_head = newnode;
		else
		{
			newnode->prev = m_rear;
			m_rear = m_rear->next = newnode;
		}
		++m_length;
		return true;
	}
	bool isSymmetry(bool(*equal)(T d1, T d2))
	{
		//����ñ��ǿձ�, ����false
		if (nullptr == m_head || nullptr == m_head->next)
			return false;
		pnode left = m_head, right = m_rear;
		int i;
		for (i = 0; i < m_length / 2; ++i)
		{
			if (!equal(left->data, right->data))
				goto False;
			left = left->next;
			right = right->prev;
		}
		return true;
	False:
		return false;
	}

};

#endif
