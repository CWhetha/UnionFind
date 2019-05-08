#include <vector> 

class uandf {
private:
	int end,total;
	int *topv;
	int *parent;
public:
	uandf(int n);
	void makeSet(int i);
	void unionSets(int i, int j);
	int findSet(int i);
	int getTotal(int i,char pic[71][71]);
	int finalSets();
	int topvalue(int i);
};
