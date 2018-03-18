#ifndef __CIRCULARLIST_H_INCLUDED__
#define __CIRCULARLIST_H_INCLUDED__

//��ȻLinkedList��ʹ��ͨ�ýڵ���ò��Ǻܺ�, ��������Ϊ���ֽṹ�ܰ����������Ϣ, �����һ���ʹ����
template<typename T>
class CircularList
{
protected:
	//ͨ�ýڵ�
	typedef struct node
	{
		node * next;
		T data;
		node() :next(nullptr){}
		node(T d) :next(nullptr), data(d){}
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
	pnode at(int i)
	{
		//���Ϊ�ձ�, ����һ���յ�ָ��
		if (nullptr == m_rear)
			return nullptr;

		//���±�ת��Ϊ���±�, ������ģ����
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
		//��ȡ�����ڵ����ǰ���ڵ�
		pnode r = input, p = nullptr;
		while (r->next != input)
		{
			p = r;
			r = r->next;
		}
		//��������ڵ�Ϊβ�ڵ�, �򽫹����ڵ����һ���ڵ���Ϊβ�ڵ�
		if (r == m_rear)
		{
			//�������ֻ��һ���ڵ�, ���øñ�
			if (m_rear == m_rear->next)
				return reset(), true;
			else
				m_rear = r->next;
		}
		//ɾ�������ڵ�
		p->next = r->next;
		r->next = nullptr;
		delete r;
		//���ȼ�һ
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
	}
	bool earse(int index)
	{
		//��ȡ�����ڵ��ǰ���ڵ�, �����ȡʧ��, ���� false
		pnode r, p = at(index - 1);	//ǰ���ڵ�
		if (nullptr == p)
			return false;
		//���ù����ڵ�
		r = p->next;
		//��������ڵ�Ϊβ�ڵ�, �򽫹����ڵ����һ���ڵ���Ϊβ�ڵ�
		if (r == m_rear)
		{
			//�������ֻ��һ���ڵ�, ���øñ�
			if (m_rear == m_rear->next)
				return reset(), true;
			else
				m_rear = r->next;
		}
		//ɾ�������ڵ�
		p->next = r->next;
		r->next = nullptr;
		delete r;
		//���ȼ�һ
		--m_length;
		return true;
	}

};

#endif 