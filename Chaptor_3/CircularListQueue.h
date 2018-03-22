#ifndef __CIRCULARLISTQUEUE_H_INCLUDED__
#define __CIRCULARLISTQUEUE_H_INCLUDED__

#include "CircularList.h"

//下溢错误
#define QUEUE_UNDERFLOW			0x00000001
//未知错误
#define QUEUE_UNKOWMEDERROR		0x00000002

//不带头结点, 循环链表, 队列, 指向队尾节点的指针, 不设头指针
template<typename Type>
class CircularListQueue : protected CircularList<Type>
{
public:
	//入队操作
	bool EnQueue(Type data)
	{
		return add(data);
	}
	//出队操作
	Type DeQueue() throw(int)
	{
		//如果循环链表为空表, 则判断该操作会抛出下溢异常
		if (0 == m_length)
			throw int(QUEUE_UNDERFLOW);

		//获取循环链表第一个节点的数据
		Type data = at(0)->data;
		//删除循环链表第一个节点, 如果删除失败, 抛出未知异常
		if (earse(0) == false)
			throw int(QUEUE_UNKOWMEDERROR);
		return data;
	}

};

#endif