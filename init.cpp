#include "init.h"
#include <sstream>
#include <fstream> 
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define linux 
#ifdef linux  
#include <unistd.h>  
#include <dirent.h>  
#endif  
#ifdef WIN32  
#include <direct.h>  
#include <io.h>  
#endif  

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

stringstream ss;

void printic(){
fstream f("qr", ios::in);
string s;
while(true){
getline(f, s);
if(s.size() == 0) break;
skout(s); skout("\n");
}
return;
}

bool isdig(string s) {
	for (int m = 0; m < s.size(); ++m) 
		if (s[m] < '0' || s[m] > '9')
			return false;
	return true;
}

vector<string> getFiles() {
	vector<string> files;// 存放文件名  

#ifdef WIN32  
	char basePath[100];
	///get the current absoulte path  
	memset(basePath, '\0', sizeof(basePath));
	_getcwd(basePath, 999);
	string path(basePath);
	// 文件句柄  
	long hFile = 0;
	// 文件信息  
	struct _finddata_t fileinfo;
	string p;
	
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			// 如果是目录, 迭代之  
			// 如果不是, 加入列表   p.assign(path).append("\\").append(fileinfo.name)
				files.push_back(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
#endif  

#ifdef linux  
	DIR *dir;
	struct dirent *ptr;
	char base[1000];
	char basePath[100];

	///get the current absoulte path  
	memset(basePath, '\0', sizeof(basePath));
	getcwd(basePath, 999);
	string cate_dir(basePath);
	if ((dir = opendir(cate_dir.c_str())) == NULL) {
		perror("Open dir error...");
		exit(1);
	}

	while ((ptr = readdir(dir)) != NULL) {
		if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir  
			continue;
		else if (ptr->d_type == 8)    ///file  
									  //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
			files.push_back(ptr->d_name);
		else if (ptr->d_type == 10)    ///link file  
									   //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
			continue;
		else if (ptr->d_type == 4)    ///dir  
		{
			files.push_back(ptr->d_name);
			/*
			memset(base,'\0',sizeof(base));
			strcpy(base,basePath);
			strcat(base,"/");
			strcat(base,ptr->d_nSame);
			readFileList(base);
			*/
		}
	}
	closedir(dir);
#endif  

	// 排序，按从小到大排序  
	sort(files.begin(), files.end());
	for (int m = 0; m < files.size(); ++m) 
		if (files[m].find(".xml") != string::npos) {
			skout(files[m], WHITE); skout("\n");
		}
	return files;
}

void init() {
	him.init();
	skout("Welcome to ImageCser Minecraft. \n");
	printic();
	me();
	skout("It is the east, and she is the sun. \n", CYAN);
	skout("Type \"man\" for your help. \n", MAGENTA);
}

int icHash(string s) {
	int sum = 0;
	for(int i = 0; i < s.size(); ++i)	
		sum += (int)s[i];
	return sum;
}

int processStr(string s) {
	std::stringstream ss;
	string ps;
	ss << s;
	getline(ss, ps, ' ');
	gvs.clear();
	while (getline(ss, s, ' ')) {
		if (s.size() == 0) break;
		gvs.push_back(s);
	}
	ss.clear();
	return icHash(ps);
}

void shows() {
	if (gvs.size() == 0) {
		pugi::xpath_node_set nodes = cur.self.select_nodes("block");
		if (nodes.size() != 0) {
			skout("blocks: ", RED);
			for (int m = 0; m < nodes.size(); ++m) {
				skout(nodes[m].node().text().as_string(), GREEN);
				skout(" x", BLUE);
				skout((string)nodes[m].node().attribute("num").value(), BLUE);
				skout("  ");
			}
			skout("\n");
		}
		nodes = cur.self.select_nodes("creature");
		if (nodes.size() != 0) {
			skout("creatures: ", RED);
			for (int m = 0; m < nodes.size(); ++m) {
				skout(nodes[m].node().text().as_string(), GREEN);
				skout(" x", BLUE);
				skout((string)nodes[m].node().attribute("num").value(), BLUE);
				skout("  ");
			}
			skout("\n");
		}
		return;
	}
	else if (gvs[0].compare("scene") == 0) {
		pugi::xpath_node_set scenes = doc.select_nodes("game/map/scene");
		for (int i = 0; i < scenes.size(); ++i) {
			skout(scenes[i].node().child("name").text().as_string(), BLUE);
			skout(" / ");
		}
		skout("\n");
		return;
	}
	else skout("Smooth runs the water where the brook is deep. \n", CYAN);
}

void mines() {
	if (gvs.size() == 0) {
		skout("Out, out, brief candle, life is but a walking shadow. \n", CYAN);
		return;
	}
	string query = "block[text()=\"" + gvs[0] + "\"]";
	pugi::xpath_node_set blocks = cur.self.select_nodes(query.c_str());
	if (blocks.size() == 0) {
		skout("Cowards die many times before their deaths. \n", CYAN);
		return;
	}
	else {
		pugi::xml_node block = blocks[0].node();
		block.attribute("num").set_value(block.attribute("num").as_int() - 1);
		string link = block.attribute("link").as_string();
		int linknum = block.attribute("linknum").as_int();
		string bagquery = "*[text()=\"" + link + "\"]";
		pugi::xml_node bagblock = him["bag"].select_node(bagquery.c_str()).node();
		bagblock.attribute("num").set_value(bagblock.attribute("num").as_int() + linknum);
		ss << linknum;
		skout("get: ", WHITE); skout(link); skout(" x", BLUE); skout(ss.str(), BLUE); ss.str("");
		skout(ss.str()); ss.str("");
		if ((double)rand() / RAND_MAX > 0.7) {
			link = block.attribute("luck").as_string();
			bagquery = "*[text()=\"" + link + "\"]";
			pugi::xml_node bagblock = him["bag"].select_node(bagquery.c_str()).node();
			bagblock.attribute("num").set_value(bagblock.attribute("num").as_int() + 1);
			skout(" and ", WHITE); skout(link); skout(" x1", BLUE);
		}
		skout("\n");
		if (block.attribute("num").as_int() == 0) cur.self.remove_child(cur.self.select_node(query.c_str()).node());
	}
}

void craft() {
	if (gvs.size() == 0) {
		pugi::xpath_node_set nodes = him["bag"].select_nodes("tool");
		for (int m = 0; m < nodes.size(); ++m) {
			skout(nodes[m].node().text().as_string());  skout("\t\tattr: ", WHITE);
			skout(nodes[m].node().attribute("attr").as_string(), GREEN); skout("\taddition: +", WHITE);
			skout(nodes[m].node().attribute("re").as_string(), GREEN); skout("\tNeed: ", WHITE);
			skout(nodes[m].node().attribute("link").as_string(), GREEN); skout(" x", BLUE);
			skout(nodes[m].node().attribute("linknum").as_string(), BLUE); skout("\t\t"); skout("\n");
		}
		return;
	}
	for (int m = 0; m < gvs.size(); ++m) {
		string toolquery = "tool[text()=\"" + gvs[m] + "\"]";
		if (him["bag"].select_nodes(toolquery.c_str()).size() != 0) {
			string query = him["bag"].select_node(toolquery.c_str()).node().attribute("link").as_string();
			int linknum = him["bag"].select_node(toolquery.c_str()).node().attribute("linknum").as_int();
			query = "item[text()=\"" + query + "\"]";
			if (him["bag"].select_node(query.c_str()).node().attribute("num").as_int() < linknum)
				skout("Nothing will come of nothing.\n", CYAN);
			else {
				him["bag"].select_node(query.c_str()).node().attribute("num").set_value(him["bag"].select_node(query.c_str()).node().attribute("num").as_int() - linknum);
				him["bag"].select_node(toolquery.c_str()).node().attribute("num").set_value(him["bag"].select_node(toolquery.c_str()).node().attribute("num").as_int() + 1);
				skout("The valiant never taste of death but once. \n", CYAN); skout("get: "); skout(gvs[m], BOLDMAGENTA); skout("\n");
			}
		}
		else {
			skout("Cowards die many times before their deaths. \n", CYAN);
		}
	}
}

bool atack() {
	if (gvs.size() == 0) {
		skout("Keep up your bright swords, for the dew will rust them. \n", CYAN);
		return true;
	}
	string query = "creature[text()=\"" + gvs[0] + "\"]";
	pugi::xpath_node_set blocks = cur.self.select_nodes(query.c_str());
	if (blocks.size() == 0) {
		skout("Cowards die many times before their deaths. \n", CYAN); 
		return true;
	}
	else {
		pugi::xml_node block = blocks[0].node();
		block.attribute("num").set_value(block.attribute("num").as_int() - 1);
		int atk = block.attribute("atk").as_int();
		int hp = block.attribute("hp").as_int();
		if(atk != 0)
			if ((him.getInt("hp") + him.getInt("armor")) * 10 / atk < hp * 10/ him.getInt("atk")) {
				skout("you die. \nGAME OVER.\n", BOLDRED);
				string s; skin(s);
				return false;
			}
		int dec = 0 - (int)(hp * (double)atk / him.getInt("atk"));
		if (him["bag"].select_nodes("tool[@attr=\"atk\" and @on=\"1\"]").size() != 0) {
			if (him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("dur").as_int() + dec <= 0) {
				skout("your sword is exhausted. \n");
				him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("on").set_value(0);
				him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("dur").set_value(200);
			}
			else {
				him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("dur").set_value((int)him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("dur").as_int() + ((double)dec * atk / him.getInt("atk")));
				skout("durability of your sword: "); skout(him["bag"].select_node("tool[@attr=\"atk\" and @on=\"1\"]").node().attribute("dur").as_string(), BOLDGREEN); skout("\n");
			}
		}
		if (him.getInt("armor") == 0) {
			him.setInt("hp", dec);
			skout("hp: "); skout(him.getAttr("hp"), BOLDRED); skout("\n");
		}
		else if (him.getInt("armor") + dec <= 0) {
			skout("your armor is exhausted. \n");
			him["bag"].select_node("tool[@attr=\"armor\" and @on=\"1\"]").node().attribute("on").set_value(0);
			him.setInt("hp", him.getInt("armor") + dec);
			him.setInt("armor", -him.getInt("armor"));
			skout("hp: "); skout(him.getAttr("hp"), BOLDRED); skout("\n");
		}
		else {
			him.setInt("armor", dec);
			skout("armor: "); skout(him.getAttr("armor"), BOLDRED); skout("\n");
			skout("hp: "); skout(him.getAttr("hp"), BOLDRED); skout("\n");
		}
		string link = block.attribute("link").as_string();
		int linknum = block.attribute("linknum").as_int();
		string bagquery = "*[text()=\"" + link + "\"]";
		pugi::xml_node bagblock = him["bag"].select_node(bagquery.c_str()).node();
		bagblock.attribute("num").set_value(bagblock.attribute("num").as_int() + linknum);
		ss << linknum;
		skout("get: ", WHITE); skout(link); skout(" x", BLUE); skout(ss.str(), BLUE); ss.str("");
		if ((double)rand() / RAND_MAX > 0.6) {
			link = block.attribute("luck").as_string();
			bagquery = "*[text()=\"" + link + "\"]";
			pugi::xml_node bagblock = him["bag"].select_node(bagquery.c_str()).node();
			bagblock.attribute("num").set_value(bagblock.attribute("num").as_int() + 1);
			skout(" and ", WHITE); skout(link); skout(" x1", BLUE);
		}
		skout("\n");
		if (block.attribute("num").as_int() == 0) cur.self.remove_child(cur.self.select_node(query.c_str()).node());
}
	return true;
}

void equip() {
	for (int m = 0; m < gvs.size(); ++m) {
		if (him["bag"].select_nodes("tool[@num!=0]").size() != 0) {
			cout << him["bag"].select_nodes("tool[@num!=0]").size();
		}
	}
}

void news() {
	dc.load_file("game.xml");
	docs[i] = dc;
	doc = dc;
	skout("Tis this times' plague, when madmen lead the blind.\n", CYAN);
	him.init();
	init();
	string scur = him.getAttr("cur");
	string query = "//scene/name[text()=\"" + scur + "\"]/..";
	cur.self = doc.select_node(query.c_str()).node();
}

void saves() {
	if (username.size() == 0) {
		skout("Please login first!\n");
		skout("You speak an infinite deal of nothing.\n", CYAN);
		return;
	}
	string location = username + ".xml";
	doc.save_file(location.c_str());
	skout("saved by your username!\n");
	skout("What's done cannot be undone. \n", CYAN);
}

void loads() {
	if (gvs.size() == 0) {
		if (username.size() == 0) {
			skout("Please login first!\n");
			skout("You speak an infinite deal of nothing.\n", CYAN);
			return;
		}
		string location = username + ".xml";
		if (dc.load_file(location.c_str())) {
			docs[i] = dc;
			doc = dc;
			skout("Tis this times' plague, when madmen lead the blind.\n", CYAN);
			him.init();
			init();
			string scur = him.getAttr("cur");
			string query = "//scene/name[text()=\"" + scur + "\"]/..";
			cur.self = doc.select_node(query.c_str()).node();
		}
		else {
			skout("You haven't save any game xml.\n");
			skout("No matter how dark long, may eventually in the day arrival. \n", CYAN);
		}
		return;
	}
	if (gvs[0] == "all") {
		getFiles();
		return;
	}
	vector<string> files = getFiles();
	bool isfile = false;
	for (int m = 0; m < files.size(); ++m)
		if (files[m] == gvs[0])
			isfile = true;
	if (!isfile) {
		skout("File not existed! \n");
		skout("No matter how dark long, may eventually in the day arrival. \n", CYAN);
		return;
	}
	if (dc.load_file(gvs[0].c_str())) {
		docs[i] = dc;
		doc = dc;
		skout("Tis this times' plague, when madmen lead the blind.\n", CYAN);
		him.init();
		init();
		string scur = him.getAttr("cur");
		string query = "//scene/name[text()=\"" + scur + "\"]/..";
		cur.self = doc.select_node(query.c_str()).node();
	}
	else {
		skout("File error!\n");
		skout("No matter how dark long, may eventually in the day arrival. \n", CYAN);
	}
}

void me() {
	skout("Your properties: \n", WHITE);

	skout("hp\t"); skout(him.getAttr("hp"), BOLDRED);
	skout("\nattack\t"); skout(him.getAttr("atk"), BOLDRED); 
	if (him["bag"].select_nodes("tool[@on = \"1\" and @attr=\"atk\"]").size() == 1) {
		skout("\t(");
		pugi::xml_node node = him["bag"].select_node("tool[@on = \"1\" and @attr=\"atk\"]").node();
		skout(node.text().as_string()); skout(" +"); skout(node.attribute("re").as_string()); skout(")\n");
	}
	else skout("\n");

	skout("armor\t"); skout(him.getAttr("armor"), BOLDRED);
	if (him["bag"].select_nodes("tool[@on = \"1\" and @attr=\"armor\"]").size() == 1) {
		skout("\t(");
		pugi::xml_node node = him["bag"].select_node("tool[@on = \"1\" and @attr=\"armor\"]").node();
		skout(node.text().as_string()); skout(" +"); skout(node.attribute("re").as_string()); skout(")\n");
	}
	else skout("\n");
}

void help() {
	skout("icMC, version 1.1-release (x86_64-pc-linux-icmc).\nThese shell commands are defined internally. Type 'man' to see this list.\nConnect the imagecser to find out more about commands not in this list.\n\nThe plus sign '+' indicates one or more occurrences of the preceding element.\n\nme\nbag\nshow (scene) \ngoto <scene>\nmine <block>+\ncraft (<tool>)\nattack <enemy>\nuse <tool>\neat <food>\nnew \nsave \nload (<filename> / all)\nlogin <username> <password>\nsee (<creature> / <block>)\ncreate <everything>\n");
}

void bag() {
	for (pugi::xml_node node : him["bag"].children()) {
		if (node.attribute("num").as_int() > 0) {
			skout(node.text().as_string());
			skout(" x", BLUE);
			skout(node.attribute("num").as_string(), BLUE);
			skout("\n");
		}
	}
}

void use() {
	if (gvs.size() == 0) {
		skout("Love looks not with the eyes but with the mind.\n", CYAN);
		return;
	}
	string query = "tool[text()=\"" + gvs[0] + "\"]";
	pugi::xpath_node_set nodes = him["bag"].select_nodes(query.c_str());
	if (nodes.size() == 0) {
		skout("Love looks not with the eyes but with the mind.\n", CYAN);
		return;
	}
	pugi::xml_node node = nodes[0].node();
	if (node.attribute("num").as_int() == 0) {
		skout("Nothing will come with nothing.\n", CYAN);
		return;
	}
	string attr = node.attribute("attr").as_string();
	if (attr.compare("atk") == 0) {
		him.setInt("atk", 20 + node.attribute("re").as_int(), 0);
		node.attribute("on").set_value("1");
		node.attribute("num").set_value(node.attribute("num").as_int() - 1);
		node.attribute("dur").set_value("200");
	}
	else if (attr.compare("armor") == 0) {
		him.setInt("armor", node.attribute("re").as_int(), 0);
		node.attribute("on").set_value("1");
		node.attribute("num").set_value(node.attribute("num").as_int() - 1);
	}
	skout("equiped: ", WHITE); skout(gvs[0]);
	skout("\nNow is the winter of our discontent.\n", CYAN);
}

void gotos() {
	if (gvs.size() == 0) {
		skout("There is nothing either good or bad, but thinking makes it so.\n", CYAN);
		return;
	}
	string query = "//scene/name[text()=\"" + gvs[0] + "\"]/..";
	pugi::xpath_node_set nodes = doc.select_nodes(query.c_str());
	if (nodes.size() == 0) {
		skout("There is nothing either good or bad, but thinking makes it so.\n", CYAN);
		return;
	}
	pugi::xml_node node = nodes[0].node();
	cur.self = node;
	him.setStr("cur", gvs[0]);
	skout("focused: ", WHITE); skout(gvs[0]); skout("\n");
	skout(cur.getAttr("intro"), CYAN); skout("\n");
}

void eat() {
	if (gvs.size() == 0) {
		skout("Brevity is the soul of wit.\n", CYAN);
		return;
	}
	string query = "food[text()=\"" + gvs[0] + "\"]";
	pugi::xpath_node_set nodes = him["bag"].select_nodes(query.c_str());
	if (nodes.size() == 0) {
		skout("Brevity is the soul of wit.\n", CYAN);
		return;
	}
	pugi::xml_node node = nodes[0].node();
	if (node.attribute("num").as_int() == 0) {
		skout("Nothing will come with nothing.\n", CYAN);
		return;
	}
	string attr = node.attribute("attr").as_string();
	if (attr.compare("hp") == 0) {
		him.setInt("hp", node.attribute("re").as_int());
		if (him.getInt("hp") > 100)
			him.setInt("hp", 100, 0);
		node.attribute("num").set_value(node.attribute("num").as_int() - 1);
	}
	skout("hp updated: +"); skout(node.attribute("re").as_string());
	skout(" -> "); skout(him.getAttr("hp"));
	skout("\nWe have seen better days.\n", CYAN);
}

void see() {
	Item add;
	add.self = doc.select_node("game/add").node();
	if (gvs.size() == 0) {
		skout("see <item> (<number>)\n");
		for (auto node : add.self.children()) {
			stringstream pss; node.print(pss);
			skout(pss.str()); pss.str("");
		}
		skout("All that glisters is not gold.\n", CYAN);
		return;
	}
	string query = "*[text()=\"" + gvs[0] + "\"]";
	pugi::xpath_node_set nodes = add.self.select_nodes(query.c_str());
	if (nodes.size() == 0) {
		skout("Nothing will come with nothing. \n", CYAN);
		skout("To find new function... You can <create> it! \n");
		return;
	}
	pugi::xpath_node_set ords = cur.self.select_nodes(query.c_str());
	if (ords.size() > 0) {
		if (gvs.size() > 1 && isdig(gvs[1])) {
			stringstream ss; ss << gvs[1]; int num; ss >> num; ss.str("");
			ords[0].node().attribute("num").set_value(ords[0].node().attribute("num").as_int() + num);
		}
		else ords[0].node().attribute("num").set_value(ords[0].node().attribute("num").as_int() + 1);
	}
	else {
		pugi::xml_node node = nodes[0].node();
		pugi::xml_node added = cur.self.append_copy(node);
		if (gvs.size() > 1 && isdig(gvs[1]))
			added.attribute("num").set_value(gvs[1].c_str());
	}
	skout("added: "); skout(gvs[0]); skout(" x", BLUE); skout(gvs.size() > 1 && isdig(gvs[1]) ? gvs[1] : "1", BLUE); 
	skout(" \nI would challenge you to a battle of wits, but I see you are unarmed!\n", CYAN);
}

bool isnotcreate() {
	string query = "//*[text()=\"" + gvs[1] + "\"]";
	pugi::xpath_node_set set = doc.select_nodes(query.c_str());
	if (set.size() == 0) return true;
	else return false;
}

void create() {
	if (gvs.size() < 2) {
		skout("types: item, weapon, armor, food, creature, block.\n");
		skout("Type: create <type> <name> (+)\n");
		skout("Thus with a kiss I die.\n", CYAN);
		return;
	}
	if (!isnotcreate()) {
		skout("The item has already existed.\n");
		skout("Thus with a kiss I die.\n", CYAN);
		return;
	}
	if (gvs[0] == "block") {
		Item add;
		add.self = doc.select_node("game/add").node();
		pugi::xpath_node_set nodes = him["bag"].select_nodes("item");
		int index = (int)((double)rand() / RAND_MAX * nodes.size());
		index = nodes.size() == index ? index - 1 : index;
		string link = nodes[index].node().text().as_string();
		int linknum = (int)((double)rand() / RAND_MAX * 5) + 1;
		nodes = him["bag"].select_nodes("food|item");
		int luckindex = (int)((double)rand() / RAND_MAX * nodes.size());
		luckindex = nodes.size() == luckindex ? luckindex - 1 : luckindex;
		string luck = nodes[luckindex].node().text().as_string();
		nodes = add.self.select_nodes("block");
		pugi::xml_node added = add.self.insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.text().set(gvs[1].c_str());
		added.attribute("link").set_value(link.c_str());
		added.attribute("linknum").set_value(linknum);
		added.attribute("luck").set_value(luck.c_str());
		skout("create: \nblock: ", WHITE);
		string ptext = added.text().as_string();
		if (ptext.size() < 7) ptext += "      ";
		skout(ptext);
		skout("drop:  ", WHITE); skout(added.attribute("link").as_string()); skout(" x", BLUE);
		skout(added.attribute("linknum").as_string(), BLUE); skout("\t(", MAGENTA); skout(added.attribute("luck").as_string(), MAGENTA); skout(")\n", MAGENTA);
	}
	else if (gvs[0] == "creature") {
		Item add;
		add.self = doc.select_node("game/add").node();
		pugi::xpath_node_set nodes = him["bag"].select_nodes("food");
		int index = (int)((double)rand() / RAND_MAX * nodes.size());
		index = nodes.size() == index ? index - 1 : index;
		string link = nodes[index].node().text().as_string();
		int linknum = (int)((double)rand() / RAND_MAX * 5) + 1;
		nodes = him["bag"].select_nodes("food|item");
		int luckindex = (int)((double)rand() / RAND_MAX * nodes.size());
		luckindex = luckindex == nodes.size() ? luckindex - 1 : luckindex;
		int atk = (int)((double)rand() / RAND_MAX * 20) * 5;
		int hp = (int)((double)rand() / RAND_MAX * 10) * 20;
		string luck = nodes[luckindex].node().text().as_string();
		nodes = add.self.select_nodes("creature");
		pugi::xml_node added = add.self.insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.text().set(gvs[1].c_str());
		added.attribute("num").set_value("1");
		added.attribute("link").set_value(link.c_str());
		added.attribute("linknum").set_value(linknum);
		added.attribute("luck").set_value(luck.c_str());
		added.attribute("atk").set_value(atk);
		added.attribute("hp").set_value(hp); 
		skout("create: \ncreature: ", WHITE);
		string ptext = added.text().as_string();
		if (ptext.size() < 7) ptext += "      ";
		skout(ptext);
		skout("\t\t\thp: "); skout(added.attribute("hp").as_string()); skout("  atk: "); skout(added.attribute("atk").as_string());
		skout("drop:  ", WHITE); skout(added.attribute("link").as_string()); skout(" x", BLUE);
		skout(added.attribute("linknum").as_string(), BLUE); skout("\t(", MAGENTA); skout(added.attribute("luck").as_string(), MAGENTA);
		 skout(")\n");
	}
	else if (gvs[0] == "item") {
		pugi::xpath_node_set nodes = him["bag"].select_nodes("item");
		pugi::xml_node added = him["bag"].insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.attribute("num").set_value("0");
		added.text().set(gvs[1].c_str());
		skout("create: \nitem: ", WHITE); skout(added.text().as_string()); skout("\n");
	}
	else if (gvs[0] == "weapon") {
		pugi::xpath_node_set nodes = him["bag"].select_nodes("item");
		int index = (int)((double)rand() / RAND_MAX * nodes.size());
		index = nodes.size() == index ? index - 1 : index;
		string link = nodes[index].node().text().as_string();
		int linknum = (int)((double)rand() / RAND_MAX * 10) + 3;
		int re = ((int)((double)rand() / RAND_MAX * 40) + 1) * 10;
		nodes = him["bag"].select_nodes("tool[@attr=\"atk\"]");
		pugi::xml_node added = him["bag"].insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.attribute("on").set_value("0");
		added.attribute("num").set_value("0");
		added.attribute("re").set_value(re);
		added.attribute("dur").set_value("200");
		added.attribute("link").set_value(link.c_str());
		added.attribute("linknum").set_value(linknum);
		added.text().set(gvs[1].c_str());
		string ptext = added.text().as_string();
		if (ptext.size() < 7) ptext += "      ";
		skout("create: \nweapon: ", WHITE);
		skout(ptext);  skout("\t\tattr: ", WHITE);
		skout(added.attribute("attr").as_string(), GREEN); skout("\taddition: +", WHITE);
		skout(added.attribute("re").as_string(), GREEN); skout("\tNeed: ", WHITE);
		skout(added.attribute("link").as_string(), GREEN); skout(" x", BLUE);
		skout(added.attribute("linknum").as_string(), BLUE); skout("\n");
	}
	else if (gvs[0] == "armor") {
		pugi::xpath_node_set nodes = him["bag"].select_nodes("item");
		int index = (int)((double)rand() / RAND_MAX * nodes.size());
		index = nodes.size() == index ? index - 1 : index;
		string link = nodes[index].node().text().as_string();
		int linknum = (int)((double)rand() / RAND_MAX * 10) + 3;
		int re = ((int)((double)rand() / RAND_MAX * 40) + 1) * 10;
		nodes = him["bag"].select_nodes("tool[@attr=\"armor\"]");
		pugi::xml_node added = him["bag"].insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.attribute("on").set_value("0");
		added.attribute("num").set_value("0");
		added.attribute("re").set_value(re);
		added.attribute("link").set_value(link.c_str());
		added.attribute("linknum").set_value(linknum);
		added.text().set(gvs[1].c_str());
		string ptext = added.text().as_string();
		skout("create: \narmor: ", WHITE);
		if(ptext.size() < 7) ptext += "      ";
		skout(ptext);  skout("\t\tattr: ", WHITE);
		skout(added.attribute("attr").as_string(), GREEN); skout("\taddition: +", WHITE);
		skout(added.attribute("re").as_string(), GREEN); skout("\tNeed: ", WHITE);
		skout(added.attribute("link").as_string(), GREEN); skout(" x", BLUE);
		skout(added.attribute("linknum").as_string(), BLUE); skout("\n");
	}
	else if (gvs[0] == "food") {
		pugi::xpath_node_set nodes = him["bag"].select_nodes("food");
		int re = ((int)((double)rand() / RAND_MAX * 20)) + 5;
		nodes = him["bag"].select_nodes("food");
		pugi::xml_node added = him["bag"].insert_copy_after(nodes[0].node(), nodes[nodes.size() - 1].node());
		added.attribute("re").set_value(re);
		added.attribute("num").set_value("0");
		added.text().set(gvs[1].c_str()); 
		string ptext = added.text().as_string();
		skout("create: \nfood: ", WHITE);
		if (ptext.size() < 7) ptext += "      ";
		skout(ptext); skout("\thp: +"); skout(added.attribute("re").as_string()); skout("\n");
	}
	else if (gvs[0] == "scene") {
		pugi::xml_node source = doc.select_node("game/add/scene").node();
		pugi::xml_node parent = doc.select_node("game/map").node();
		pugi::xml_node added = parent.append_copy(source);
		added.child("name").text().set(gvs[1].c_str());
		skout("create: \nscene: ", WHITE);
		skout(gvs[1]); skout("\n");
	}
	else {
		skout("Nothing will come with nothing. \n", CYAN);
		return;
	}
	skout("Though this be madness, yet there is method in't.\n", CYAN);
}

void readuser() {
	fstream f("user", ios::in);
	stringstream ss;
	string line, ps;
	while (getline(f, line)) {
		ss.str("");
		if (line.size() == 0) break;
		ss << line;
		User *puser = new User;
		getline(ss, puser->name, '|');
		getline(ss, puser->word, '|');
		users.push_back(*puser);
	}
	f.close();
}

void login() {
	if (gvs.size() < 2) {
		skout("Uncorrect username or password!\nIt is not in the stars to hold our destiny but in ourselves.\n", CYAN);
		return;
	}
	if (gvs[0].find("|") != string::npos || gvs[1].find("|") != string::npos) {
		skout("No character\'|\'.\nIt is not in the stars to hold our destiny but in ourselves.\n", CYAN);
		return;
	}
	readuser();
	bool isuser = false, isword = false;
	for (int m = 0; m < users.size(); ++m) {
		if (gvs[0] == users[m].name)
			if (gvs[1] == users[m].word) {
				isuser = true; isword = true;
			}
			else isuser = true;
	}
	if (isuser == true && isword == true)
		skout("Logined! ");
	else if (isuser == true) {
		skout("Uncorrect username or password!\nIt is not in the stars to hold our destiny but in ourselves.\n", CYAN);
		return;
	}
	else {
		fstream f("user", ios::app);
		f << gvs[0] << "|" << gvs[1] << endl;
		f.close();
		skout("Registered! ");
	}
	username = gvs[0];
	password = gvs[1];
	skout("You can save and load game file now!\n");
	skout("Hell is empty and all the devils are here.\n", CYAN);
}

