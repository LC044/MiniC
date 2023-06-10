#include<stdio.h>
#include <string>
#include <unordered_map>
// #include<string.h>
int a;
int a;
int add(int a, int b)
{
    return a + b;
}
struct test {
    std::string name;
    std::unordered_map<std::string, int *> localVarsMap;

    /* data */
};
static std::unordered_map<std::string, test *> VarsMap;
int main(int argc, char **argv)
{
    test *t = new test();
    t->name = "test";
    VarsMap.emplace(t->name, t);
    test *t1 = new test();
    t1->name = "test0";
    VarsMap.emplace(t1->name, t1);
    // auto pt = VarsMap.find("test");
    for (auto pt : VarsMap) {
        printf("%s\n", pt.second->name.c_str());
    }

    printf("--------------------------------");
    int q[5] = { 0, 1, 2, 3, 4 };
    int *i = q;
    printf("%d\n", i[3]);
    printf("%d\n", ">=" == ">=");
    int a = 2, b;
    b = --a + a-- - b++;

    return 0;
}