#ifndef TASK_H
#define TASK_H

#include <deque>
#include "Item.h"
#include "CustomerOrder.h"

class Task: public Item {

	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;  

public:
	Task(const std::string& record);
	Task(const Task& src) = delete; //copy constructor
	Task(Task && ) = delete; //move constructor
	Task& operator=(const Task& src) = delete; //copy assignment 
	Task & operator=(Task && ) = delete;  //move assignment 
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};

#endif // !TASK_H