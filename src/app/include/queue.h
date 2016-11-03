#ifndef _myqueue_h_
#define _myqueue_h_

#define MAX_QUEUE 2048

template<class T1>
class YTQueue{
private:
	int front;
	int rear;
	T1   queue[MAX_QUEUE];
public:
	YTQueue()
	{
		front=rear=0;
	}
	inline bool IsFull() const 
	{
		return ((rear+1)%MAX_QUEUE==front)?1:0;
	}
	
	inline bool IsEmpty() const
	{
		return front==rear;
	}
	
	inline bool RemoveHead(T1& x)
	{
		if(IsEmpty())
			return false;
		front=(front+1)%MAX_QUEUE;
		memcpy(&x,&queue[front],sizeof(T1));
		return true;
	}
	
	inline bool AddTail(const T1& x)
	{
		if(IsFull())
			return false;
		rear=(rear+1)%MAX_QUEUE;
		memcpy(&queue[rear],&x,sizeof(T1));
		return true;
	}
	inline bool RemoveAll()
	{
		if (IsEmpty())
			return false;
		front=rear=0;
		return true;
	}
	~YTQueue(){};
};
/*
template <class T> 
class CMyFifo{
public:
	T queue[MAX_QUEUE];
	int	 m_pHead;
	int  m_pTail;
public:
	CMyFifo()
	{
		m_pHead = 0;
		m_pTail = 0;
		memset(queue,0,sizeof(T)*MAX_QUEUE);
	}

	void RemoveHead(T &msg)
	{
		memcpy(&msg,&queue[m_pHead],sizeof(T));
		m_pHead++;
		if(m_pHead >= MAX_QUEUE)
			m_pHead = 0;
	}

	void GetHead(T &msg)
	{
		memcpy(&msg,&queue[m_pHead],sizeof(T));
	}

	void RemoveAll()
	{
		m_pHead = 0;
		m_pTail = 0;
		memset(queue,0,sizeof(T)*MAX_QUEUE);
	}

	int AddTail(T f1)
	{
		if(GetCount() == MAX_QUEUE - 1){
			return -1;
		}
		memcpy(&queue[m_pTail],&f1,sizeof(T));
		m_pTail++;
		if(m_pTail >= MAX_QUEUE)
			m_pTail = 0;

		return m_pTail;
	}

	int GetCount()
	{
		if(m_pHead <= m_pTail)
			return m_pTail-m_pHead;
		else
			return MAX_QUEUE - m_pHead + m_pTail;
	}


	int IsEmpty()
	{
		if(m_pTail == m_pHead)
			return 1;
		else 
			return 0;
	}

	~CMyFifo(){};
};
*/
#endif