#include <vector>
#include <sstream>
#include "sock.h"
#include <map>

class Item;
class Hero;
class Enemy;
struct User;

extern Item cur;
extern Hero him;
extern vector<string> gvs;
extern vector<User> users;
bool isNum(string s);


class Item {
public:
	pugi::xml_node self;
	pugi::xml_node operator[](const char* query);
	bool setInt(char const* query, int s, int mod = 1);
	bool setStr(char const* query, string s);
	string getAttr(char const* query);
	int getInt(char const* query);
};

class Hero : public Item {
public:
	void init();
};

struct User {
	string name;
	string word;
};