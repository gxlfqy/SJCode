#ifndef __LINKEDLIST_H_INCLUDED__
#define __LINKEDLIST_H_INCLUDED__

template<typename T>
class LinkedList
{
protected:
	typedef struct node
	{
		//注意, 这两个成员不能颠倒
		node * next;
		T data;
		node() :next(nullptr){}
		node(T d) :next(nullptr), data(d){}
	}* pnode;
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
			}
			delete p;
		}
	}

public:
	LinkedList() :m_head(nullptr), m_rear(nullptr), m_length(0){}
	~LinkedList()
	{
		reset();
	}
	void reset()
	{
		free(m_head);
		m_head = m_rear = nullptr;
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
			m_rear = m_rear->next = newnode;
		++m_length;
		return true;
	}
	//注意下标是从0开始, 前插
	bool insert(int i, T data)
	{
		//将负下标转化为正下标, 并判断i是否非法
		i = (i + m_length) % m_length;
		if (0 > i)
			return false;
		//判断是否为空表, 如果根据i判断, 并执行添加操作
		if (nullptr == m_head)
			return (0 == i) ? add(data) : false;
		//如果表不为空, 新建一个新的节点, 并初始化节点的相关参数
		pnode p = m_head, newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//如果插入的位置为表头, 将新建的节点作为第一个节点, 并将新建节点的next指向头指针指向的节点
		if (0 == i)
			return (m_head = (pnode)&(newnode->next = m_head)), ++m_length, true;
		//如果插入的位置不是表头, 则找出其前驱节点, 将新建的节点插在前驱节点之后
		while (p && --i > 0)
			p = p->next;
		if (nullptr != p)
		{
			//如果前驱节点是原链表的尾节点, 将 m_rear 指向 newnode
			if (nullptr == p->next)
				m_rear = newnode;
			p->next = (pnode)&(newnode->next = p->next), ++m_length;
			return true;
		}
		else
			return false;
	}
	void LinkedList::reverse();

};

template<typename T>
void LinkedList<T>::reverse()
{
	//如果该表不存在或只存在一个节点, 直接返回
	if (nullptr == m_head || nullptr == m_head->next)
		return;

	pnode p, r, n;
	p = n = nullptr;
	m_rear = r = m_head;
	//假设前驱节点和当前节点中没有连接
	while (nullptr != r)
	{
		//保存当前节点的后继节点地址
		n = r->next;
		//将当前节点的下一个节点指向前驱节点
		r->next = p;
		//将当前节点作为前驱节点
		p = r;
		//移动当前节点位置
		r = n;
	}
	m_head = p;
}

#endif // __LINKEDLIST_H_INCLUDED__