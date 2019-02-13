#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField = 1;

Item::Item(const std::string& str) {
	//EXAMPLE: str is CPU,123456,5,Central Processing Unit
	//Memory, 654321, 10, Basic Flash Memory
	//GPU, 56789, 7, General Porcessing Unit

	Utilities utl;
	std::string token;
	std::vector<std::string> tokens;
	size_t position = 0;
	bool more = true;

	while (more) {
		//EXAMPLE: str is:CPU,123456,5,Central Processing Unit
		token = utl.extractToken(str, position, more);
		tokens.push_back(token);
		m_widthField = (tokens.size() == 1 && utl.getFieldWidth() > m_widthField) ? utl.getFieldWidth() : m_widthField;
		
		if (position == str.size()) { 
			more = false; 
		}
	}
	// populate item object with name, serial number, quantity, and description
	m_name = tokens[0];

	int serial = atoi(tokens[1].c_str());
	m_serialNumber = serial;
	
	int qty = atoi(tokens[2].c_str());
	m_quantity = qty;

	m_description = tokens[3];
	
	tokens.clear();
}

const std::string& Item::getName() const {
	return m_name;
}

const unsigned int Item::getSerialNumber() {
	const unsigned int sn = m_serialNumber;
	m_serialNumber++;
	return sn;
}

const unsigned int Item::getQuantity() {
	return m_quantity;
}

void Item::updateQuantity() {
	if (m_quantity > 0) {
		m_quantity--;
	}
}

void Item::display(std::ostream&  os, bool  full)  const {
	if (full) {
		os << std::left << std::setw(m_widthField) << m_name << " " << "[" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << "]" << std::setfill(' ')
			<< " Quantity: " << std::left << std::setw(m_widthField) << m_quantity << " Description: " << m_description << std::endl;
	}
	else {
		os << std::left << std::setw(m_widthField) << getName() << " " << "[" << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << "]" << std::setfill(' ') << std::endl;
	}
}