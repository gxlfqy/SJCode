#ifndef __LINKEDLIST_H_INCLUDED__
#define __LINKEDLIST_H_INCLUDED__

template<typename T>
class LinkedList
{
protected:
	typedef struct node
	{
		//ע��, ��������Ա���ܵߵ�
		node * next;
		T data;
		node() :next(nullptr){}
		node(T d) :next(nullptr), data(d){}
	}* pnode;
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
		//�½�һ���µĽڵ�, ����ʼ���ڵ�
		pnode newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//�жϱ��Ƿ�Ϊ�ձ�, �����һ���ձ�, ���½��Ľڵ���Ϊ��ĵ�һ���ڵ�
		//�����Ϊ��, ���½��Ľڵ���ӵ������β��
		if (nullptr == m_head)
			m_rear = m_head = newnode;
		else
			m_rear = m_rear->next = newnode;
		++m_length;
		return true;
	}
	//ע���±��Ǵ�0��ʼ, ǰ��
	bool insert(int i, T data)
	{
		//�����±�ת��Ϊ���±�, ���ж�i�Ƿ�Ƿ�
		i = (i + m_length) % m_length;
		if (0 > i)
			return false;
		//�ж��Ƿ�Ϊ�ձ�, �������i�ж�, ��ִ����Ӳ���
		if (nullptr == m_head)
			return (0 == i) ? add(data) : false;
		//�����Ϊ��, �½�һ���µĽڵ�, ����ʼ���ڵ����ز���
		pnode p = m_head, newnode = new node(data);
		if (nullptr == newnode)
			return false;
		//��������λ��Ϊ��ͷ, ���½��Ľڵ���Ϊ��һ���ڵ�, �����½��ڵ��nextָ��ͷָ��ָ��Ľڵ�
		if (0 == i)
			return (m_head = (pnode)&(newnode->next = m_head)), ++m_length, true;
		//��������λ�ò��Ǳ�ͷ, ���ҳ���ǰ���ڵ�, ���½��Ľڵ����ǰ���ڵ�֮��
		while (p && --i > 0)
			p = p->next;
		if (nullptr != p)
		{
			//���ǰ���ڵ���ԭ�����β�ڵ�, �� m_rear ָ�� newnode
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
	//����ñ����ڻ�ֻ����һ���ڵ�, ֱ�ӷ���
	if (nullptr == m_head || nullptr == m_head->next)
		return;

	pnode p, r, n;
	p = n = nullptr;
	m_rear = r = m_head;
	//����ǰ���ڵ�͵�ǰ�ڵ���û������
	while (nullptr != r)
	{
		//���浱ǰ�ڵ�ĺ�̽ڵ��ַ
		n = r->next;
		//����ǰ�ڵ����һ���ڵ�ָ��ǰ���ڵ�
		r->next = p;
		//����ǰ�ڵ���Ϊǰ���ڵ�
		p = r;
		//�ƶ���ǰ�ڵ�λ��
		r = n;
	}
	m_head = p;
}

#endif // __LINKEDLIST_H_INCLUDED__