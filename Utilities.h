#ifndef UTILITIES_H 
#define UTILITIES_H 

class Utilities {

	size_t m_widthField;
	static char m_delimiter;

public:
	Utilities();
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
	static void setDelimiter(const char);
	const char getDelimiter() const;
};

#endif // !UTILITIES_H 