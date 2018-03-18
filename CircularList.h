#ifndef __CIRCULARLIST_H_INCLUDED__
#define __CIRCULARLIST_H_INCLUDED__

//虽然LinkedList中使用通用节点觉得不是很好, 但是我认为这种结构能包含更多的信息, 所以我还是使用了
template<typename T>
class CircularList
{
protected:
	//通用节点
	typedef struct node
	{
		node * next;
		T data;
		node() :next(nullptr){}
		node(T d) :next(nullptr), data(d){}
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
	pnode at(int i)
	{
		//如果为空表, 返回一个空的指针
		if (nullptr == m_rear)
			return nullptr;

		//将下标转化为正下标, 并进行模运算
		while (i < 0)
			i = (i + m_length) % m_length;

		pnode p = m_rear;
		while (i-- >= 0)
			p = p->next;

		return p;
	}
	bool earse_prev(pnode input)
	{
		if (nullptr == input)
			return false;
		//获取工作节点和其前驱节点
		pnode r = input, p = nullptr;
		while (r->next != input)
		{
			p = r;
			r = r->next;
		}
		//如果工作节点为尾节点, 则将工作节点的下一个节点作为尾节点
		if (r == m_rear)
		{
			//如果表中只有一个节点, 重置该表
			if (m_rear == m_rear->next)
				return reset(), true;
			else
				m_rear = r->next;
		}
		//删除工作节点
		p->next = r->next;
		r->next = nullptr;
		delete r;
		//长度减一
		--m_length;
		return true;
	}

public:
	CircularList() :m_rear(nullptr), m_length(0){}
	~CircularList()
	{
		reset();
	}
	void reset()
	{
		free(m_rear->next);
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
	}
	bool earse(int index)
	{
		//获取工作节点的前驱节点, 如果获取失败, 返回 false
		pnode r, p = at(index - 1);	//前驱节点
		if (nullptr == p)
			return false;
		//设置工作节点
		r = p->next;
		//如果工作节点为尾节点, 则将工作节点的下一个节点作为尾节点
		if (r == m_rear)
		{
			//如果表中只有一个节点, 重置该表
			if (m_rear == m_rear->next)
				return reset(), true;
			else
				m_rear = r->next;
		}
		//删除工作节点
		p->next = r->next;
		r->next = nullptr;
		delete r;
		//长度减一
		--m_length;
		return true;
	}

};

#endif 