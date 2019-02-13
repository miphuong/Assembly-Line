#include <iostream>  //for validateTasks
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Task.h"
#include "Utilities.h"


LineManager::LineManager(const std::string& record, std::vector<Task*>& task, std::vector<CustomerOrder>& co) {

	std::ifstream file;
	file.open(record);  // open file for reading
	std::string line;

	std::string token; 
	std::vector<std::string> tokens;

	while (!file.eof()) {  // puts everything in the file (Assembly Line) into tokens vector, each line is: task|task, except last line is task
		std::getline(file, line);
		tokens.push_back(line);
	}

	Utilities utl;
	std::vector<std::string> tokens2;
	std::string token2;

	for (size_t i = 0; i < tokens.size(); i++) { // extracts the tasks [which are in this form: (task|task)] from tokens vector 
		bool more = true;
		size_t position = 0;

		while (more) {
			token2 = utl.extractToken(tokens[i], position, more);  // seperates (task|task) into task, task 
			tokens2.push_back(token2);  

			if (position == tokens[i].size()) {
				more = false;
			}
		}
	}

	//link task objects
	for (size_t i = 0; i < task.size(); i++) {
			for (size_t y = 0; y < tokens2.size(); y++, y++) { // increment y by 2 because every 2 tasks in tokens2 vector has the linking task next to current task
				if (task[i]->getName() == tokens2[y]) { 
					if (task[i]->getName() == "SSD") { break; }    
					for (size_t z = 0; z < task.size(); z++) {  // loop through task vector
						if (tokens2[y + 1] == task[z]->getName()) {  // if the task next to tokens2[y] is the same as task[z], link them
							task[i]->setNextTask(*task[z]);
							break;
						}
					}
					break;
				}
			}
	}

	//move all CustomerObjects onto the front of ToBeFilled queue
	unsigned size = 0;
	for (size_t z = 0; z < co.size(); z++) {
		ToBeFilled.push_back(std::move(co[z]));
		size++;
	}
	m_cntCustomerOrder = size;  // number of customers in the ToBeFilled queue

	//reverse order of ToBeFilled queue
	std::reverse(ToBeFilled.begin(), ToBeFilled.end());

	//copy Task objects into AssemblyLine container
	for (size_t a = 0; a < task.size(); a++) {
		AssemblyLine.push_back(task[a]);
	}
}

bool LineManager::run(std::ostream& os) {
	//Put the last customer order in the ToBeFilled queu to the front of the assembly line
	if (!ToBeFilled.empty()) {
		auto iter = ToBeFilled.end() - 1;
		*AssemblyLine[4] += std::move(*iter);  
		ToBeFilled.pop_back();
	}

	//run one cycle of the current task's process
	bool run = true;
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}

	//move customerorder objects down the line
	for (size_t i = 0; i < AssemblyLine.size(); i++) {  
		AssemblyLine[i]->moveTask();
		if (AssemblyLine[i]->getName() == "SSD") {
			CustomerOrder co;
			if (AssemblyLine[i]->getCompleted(co) == true ) {  // if the customer order in SSD task is completed, move it to Completed deque
				Completed.push_back(std::move(co));
			}
		}
	}

	if (Completed.size() != 4) {
		run = false;
	}

	return run;
}

void LineManager::displayCompleted(std::ostream& os) const {
	for (size_t i = 0; i < Completed.size(); i++) {
		if (Completed[i].getOrderFillState()) {
			Completed[i].display(os);
		}
	}
}

void LineManager::validateTasks() const {
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->validate(std::cout);
	}
}