#ifndef CUSTOMERORDER_H    
#define CUSTOMERORDER_H

#include <string>
#include "Item.h"


struct ItemInfo {
	std::string m_itemName;     
	unsigned int m_serialNumber = 0;     
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {

	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;

public:
	CustomerOrder();
	CustomerOrder(std::string& record);
	CustomerOrder(const CustomerOrder& src);//copy constructor
	CustomerOrder& operator=(const CustomerOrder& src) = delete;
	CustomerOrder(CustomerOrder&& src) noexcept;
	CustomerOrder& operator=(CustomerOrder&& src);
	~CustomerOrder();
	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream&);
	void display(std::ostream&) const;
};


#endif