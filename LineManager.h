#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <deque>
#include "Task.h"

class LineManager {
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;

public:
	LineManager(const std::string& record, std::vector<Task*>& task, std::vector<CustomerOrder>& co);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif // !LINEMANAGER_H