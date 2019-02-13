#include <iostream>
#include "Task.h"

Task::Task(const std::string& record) : Item(record), m_pNextTask(nullptr) {}

void Task::runProcess(std::ostream& os) {
	if (m_orders.size() > 0) {  // if there is any customer order in the current task, fill it with the current item
		m_orders.back().fillItem(*this, os);
	}
}

bool Task::moveTask() {

	bool moved = false;
	if (!m_orders.empty() && m_pNextTask != nullptr) {  // checks if orders deque is not empty and if the task is not at the end of line
		if (m_orders.back().getItemFillState(getName()) == true) {  // checks if the customer order in the order deque, has their item filled
			*m_pNextTask += std::move(m_orders.back());   // move current customer order to next task, and put's it into that task's orders deque
			m_orders.pop_back();  
			moved = true;
		}
		else {  // customer order in order deque does not have their item filled yet, therefore cannot move customer order to next task
			moved = false;
		}
	}
	else {  // orders deque is empty or it is at the end of the line, therefore cannot move customer order to next task
		moved = false;
	}
	
	return moved;
}

void Task::setNextTask(Task& task) {
	m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& CO) {
	bool completed = false;
	if (m_orders.empty() == false && m_orders.back().getOrderFillState() == true) {  // checks to see if customer order is completely filled
		CO = std::move(m_orders.back());
		m_orders.pop_back();
		completed = true;
	}

	return completed;
}

void Task::validate(std::ostream& os) {
	if (m_pNextTask != nullptr) {
		os << getName() << " --> " << m_pNextTask->getName() << std::endl; 
	}
	else {
		os << getName() << " --> END OF LINE" << std::endl;  
	}
}

Task& Task::operator+=(CustomerOrder&& CO) {
	m_orders.push_front(std::move(CO));     

	return *this;
}