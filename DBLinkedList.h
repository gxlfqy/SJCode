#ifndef __DBLINKEDLIST_H_INCLUDED__
#define __DBLINKEDLIST_H_INCLUDED__

template<typename T>
class DBLinkedList
{
protected:
	typedef struct node
	{
		//注意, 这两个成员不能颠倒
		node * next;
		T data;
		node * prev;
		node() :next(nullptr), prev(nullptr) {}
		node(T d) :next(nullptr), prev(nullptr), data(d) {}
	}*pnode;
	pnode m_head;		//头指针
	pnode m_rear;		//尾指针
	int m_length;		//长度
	void free(pnode p)
	{
		//使用递归依次释放节点所申请的空间
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
		//新建一个新的节点, 并初始化节点
		pnode newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//判断表是否为空表, 如果是一个空表, 则将新建的节点作为表的第一个节点
		//如果表不为空, 将新建的节点添加到链表的尾部
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
		//如果该表是空表, 返回false
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
