#include <string>
#include <iostream>
#include "Utilities.h"

char Utilities::m_delimiter = 0;

Utilities::Utilities() {
	m_widthField = 1;
}

void Utilities::setFieldWidth(size_t fieldWidth) {
	m_widthField = fieldWidth;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token;

	while (next_pos < str.size()) {
		if (str.at(next_pos) == m_delimiter) {
			next_pos++;
			break;
		}
		else {
			token += str.at(next_pos); // creates the token, letter by letter
			next_pos++;
		}
	}

	setFieldWidth(token.size());

	return std::move(token);
}

void Utilities::setDelimiter(const char delim) {
	m_delimiter = delim;
}

const char Utilities::getDelimiter() const {
	return m_delimiter;
}