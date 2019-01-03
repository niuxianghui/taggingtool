#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <vector>

using namespace std;

// 自定义对象和方法声明
class Category;

vector<string> split(const string &str, const string &delim);

/**
 * 单词数据结构定义
 */
class Word {
public:
    set<Category*> categorySet{};

    Word() {
    }
};

/**
 * 单词类别数据结构定义
 */
class Category {
public:
    map<string, int> wordMap{};
    int totalAppearNumber = 0;

    Category() {
    }
};

void test();
int main() {
    test();
    ifstream fin("penn.txt");
    string oneLine;

    // 初始化两个map用来存放从文件中读取到的数据
    map<string, Word*> wordMap;
    map<string, Category*> categoryMap;

    // 逐行读取文件，结果存放在oneLine中
    while (getline(fin, oneLine)) {
        vector<string> items = split(oneLine, "/");
        int itemsSize = (int) items.size();

        string wordContent;
        string categoryName;
        // 分割字符串，并提取出单词和类别
        if (itemsSize < 2) {
            continue;
        } else if (itemsSize > 2) {
            categoryName = items.back();
            for (int i = 0; i < itemsSize - 1; i++) {
                if (i != 0) {
                    wordContent += "/";
                }
                wordContent += items.at(i);
            }
        } else {
            wordContent = items.at(0);
            categoryName = items.at(1);
        }

        // 将单词存入map
        Word *currentWord = new Word();
        auto ret = wordMap.insert(make_pair(wordContent, currentWord));
        // 如果map中已存在该单词，将单词取出来
        if (!ret.second) {
            currentWord = ret.first -> second;
        }

        // 将类别存入map
        Category* currentCategory = new Category();
        auto ret2 = categoryMap.insert(make_pair(categoryName, currentCategory));
        // 如果map中已存在类别，取出来
        if (!ret2.second) {
            currentCategory = ret2.first -> second;
        }

        // 获取word的类别并添加新类别
        set<Category*> categorySet = currentWord->categorySet;
        categorySet.insert(currentCategory);

        // 在当前类别中给当前单词次数加一
        auto currentWordMap = currentCategory->wordMap;
        auto categoryCountIterator = currentWordMap.find(categoryName);
        if (categoryCountIterator == currentWordMap.end()) {
            currentWordMap.insert(make_pair(wordContent, 1));
        } else {
            int currentNumber = categoryCountIterator->second;
            // 删除原来的
            currentWordMap.erase(categoryCountIterator);
            currentWordMap.insert(make_pair(wordContent, currentNumber + 1));
        }
        // 总数加一
        currentCategory->totalAppearNumber = currentCategory->totalAppearNumber + 1;

        cout << "单词" << wordContent << "      类别" << categoryName << endl;
    }
    return 0;
}

void test() {
    std::set<int> set;

    auto result_1 = set.insert(3);
    auto result = set.find(3);


    map<string, int> mapTest;
    map<string, int>::iterator iterTest;

    // 这种使用insert的插入方式，当map中没有对应键值的元素时，插入。当map中存在对应键值的元素时，不插入元素。
    pair<map<string, int>::iterator, bool> ret;
    string d1 = "d";
    string d2 = "d";
    mapTest.insert(map<string, int>::value_type(d1, 40));
    ret = mapTest.insert(make_pair(d2, 50));

    // 当使用insert函数后会返回pair<map<char, int>::iterator, bool>类型的值，bool值表示是否插入成功。迭代器指向插入的元素。
    cout << ret.second << ret.first->first << ret.first->second << true << endl;



}


vector<string> split(const string &str, const string &delim) {
    vector<string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; //不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}