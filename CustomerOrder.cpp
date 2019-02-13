#include <vector>
#include <memory>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 1;

CustomerOrder::CustomerOrder() {
	m_name[0] = '\0';
	m_product = '\0';
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& record) {
	Utilities utl;

	bool more = true;
	size_t nextpos = 0;
	std::string token;
	std::vector<std::string> tokens;
	
	while (more) {
		token = utl.extractToken(record, nextpos, more);
		tokens.push_back(token);

		CustomerOrder::m_widthField =  (utl.getFieldWidth() > CustomerOrder::m_widthField) ? utl.getFieldWidth() : CustomerOrder::m_widthField;
		if (nextpos == record.size()) {
			more = false;
		}
	}

	m_name = tokens[0];  // store name of customer
	m_product = tokens[1]; // store name of product

	//find number of items customer wants
	int vector_size = 0;
	for (size_t i = 2; i < tokens.size(); i++) {
		if (!tokens.at(i).empty()) {  //checks for at least 1 item
			vector_size++;  
		}
	}
	m_cntItem = vector_size;  //number of items customer wants

	//dynamically create array of pointers
	if (m_cntItem > 0) {
		m_lstItem = new ItemInfo*[m_cntItem];
	}
	
	//populate item
	for (size_t i = 2, item = 0; item < m_cntItem; i++,item++) {
		m_lstItem[item] = new ItemInfo(tokens.at(i));
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& src) {
	throw std::string("error! cannot call copy constructor");
}

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
	if (this != &src) {
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;

		src.m_name = '\0';
		src.m_product = '\0';
		src.m_cntItem = 0;
		src.m_lstItem = nullptr;
	}
	return *this;
}

CustomerOrder::~CustomerOrder() {
	delete[] m_lstItem; 
}

bool CustomerOrder::getItemFillState(std::string item) const {
	bool doesNotExist=true;
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item) {
			return m_lstItem[i]->m_fillState;;
		}
	}

	return doesNotExist;
}

bool CustomerOrder::getOrderFillState() const {
	//if everything in the customer order's list (m_lstItem) has all of it's items m_fillState == true, return true
	//EX: m_lstItem=[cpu (fillstate is false),gpu (fillstate is true), SSD(fillstate is true)] then return false
	// EX: m_lstItem = [cpu(fillstate is true), gpu(fillstate is true), SSD(fillstate is true)] then return true
	bool filled = true;
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_fillState == false) {
			filled = false;
			break; 
		}
	}
	return filled;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	//If the item is in the customer order's list (m_lstItem), and there is more
	//then one item in the inventory(this is in the Item module), change its m_fillState to true
	//This means you can fill the customer's order
	for (unsigned int i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item.getName()) {
			if (item.getQuantity() > 0) {
				item.updateQuantity();
				m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]\n";
			}
			else {//item is in the inventory, but none are in stock
				os << "Unable to fill " << m_name << ", " << m_product << "[" << m_lstItem[i]->m_itemName << "]\n";
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (unsigned int i = 0; i < m_cntItem; i++) {
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::setw(CustomerOrder::m_widthField) << std::left << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_fillState == 0) {
			os << "MISSING\n";
		}
		else {
			os << "FILLED\n";
		}
	}
}