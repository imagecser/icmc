#include "data.h"

vector<string> gvs;
vector<User> users;

pugi::xml_document doc;
pugi::xml_document dc;

bool isNum(string s) {
	std::stringstream ss(s);
	int temp;
	if (ss >> temp) return true;
	else return false;
}

pugi::xml_node Item::operator[](const char* query) {
	//string ss = query.evaluate_string;
	
	return self.select_node(query).node();
	// TODO: 在此处插入 return 语句
}

bool Item::setInt(char const* query, int s, int mod) {
	if(mod == 1)
		return self.select_node(query).node().text().set(self.select_node(query).node().text().as_int() + s);
	else return self.select_node(query).node().text().set(s);
}

bool Item::setStr(char const* query, string s) {
	return self.select_node(query).node().text().set(s.c_str());
}

string Item::getAttr(char const* query) {
	return self.select_node(query).node().text().as_string();
}

int Item::getInt(char const * query) {
	return self.select_node(query).node().text().as_int();
}

void Hero::init() {
	self = doc.select_node("//hero").node();
}


