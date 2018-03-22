#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

//下溢错误
#define STACK_UNDERFLOW			0x00000004
//内存错误
#define ALLOC_FAIL_ERROR		0x00000008
//溢出
#define STACK_FLOW				0x00000010

template<typename Type>
class CMyStack
{
protected:
	int m_nMaxSize;				//最大大小
	Type * m_data;				//数据指针
	int m_top;					//栈顶指针

public:
	//size 的最大值为256
	CMyStack(int size = 20) throw(int) : m_nMaxSize((size <= 0 || size > 256) ? 20 : size), m_top(-1)
	{
		//进行堆的申请, 如果申请失败, 抛出内存错误
		m_data = new Type[m_nMaxSize];
		if (nullptr == m_data)
			throw int(ALLOC_FAIL_ERROR);
	}
	//压栈
	void push(Type data) throw(int)
	{
		//如果栈顶等于m_nMaxSize - 1抛出溢出异常
		if (m_top >= m_nMaxSize - 1)
			throw int(STACK_FLOW);
		m_data[++m_top] = data;
	}
	//弹栈
	Type pop() throw(int)
	{
		//如果-1 <= m_top, 抛出下溢异常
		if (-1 >= m_top)
			throw int(STACK_UNDERFLOW);
		return m_data[m_top--];
	}
};

template<typename Type>
void StackAdjust(CMyStack<Type> stack)
{
	CircularListQueue<Type> queue;
	//对栈中的元素进行倒置
	while (true)
	{
		try{ queue.EnQueue(stack.pop()); }
		catch (...){ break; }
	}
	while (true)
	{
		try{ stack.push(queue.DeQueue()); }
		catch (...){ break; }
	}
	while (true)
	{
		try{ queue.EnQueue(stack.pop()); }
		catch (...){ break; }
	}
	int i = 0;
	while (true)
	{
		try{
			//如果是偶数
			if ((i & 1) == 0)
				stack.push(queue.DeQueue());
			else
				queue.EnQueue(queue.DeQueue());
			++i;
		}
		catch (...){ break; }
	}
}

#endif