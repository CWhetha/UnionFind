#include <string>
#include "uandf.h"

uandf::uandf(int n) {
	end = 0;
	total = 0;
	int x = 0;
	parent = new int[n];//creates the corect sized arrays
	topv = new int[n];
	while (x < (n)) {
		parent[x] = -1;//defaults all parents to -1
		x++;
	}
}
void uandf::makeSet(int i) {
	if (end == 0) {
		parent[i] = i; //make each new sets parent equal itself
		total++;//keps track of the total number of sets
	}
}
void uandf::unionSets(int i, int j) {
	int x, y, fin=0;
	if (end == 0) {//makes sure final_set hasnt been called
		x = findSet(i);//finds the root nodes of both values
		y = findSet(j);
		if (x != y) { //if they arent part of the same tree continue
				parent[y] = x;	//make the j tree a child of the i tree
				total--; //deincrement the number of sets
		}
	}
}

int uandf::findSet(int i) {
		int v = parent[i];
		while (v != i && v!=-1) {//cycles through parent to get to a root 
			i = parent[i];
			v = parent[v];
		}
		if (v == -1){//not a set so return -1
			return -1;
		}
		else {
			return i;
		}
}
int uandf::topvalue(int i) {
	return topv[i];
}
int uandf::getTotal(int i, char pic[71][71]) {
	int x = 0,y=0;
	total = 0;
	while (x < 71) {
		y = 0;
		while (y < 71) {
			if (topv[((x * 71) + y)] == i && pic[x][y] == '+') {//counts the number of the given value in the sets
				total++;
			}
			y++;
		}
		x++;
	}
	return total;
}
int uandf::finalSets() {
	int count = 0;
	int val = 0;
	end = 1;//stops makeset and union from working
	while(count<(71*71)){
		if (parent[count] == count) {
			topv[count] = val;//for each set representative store a different number 
			val++;
		}
		else {
			topv[count] = 27; //otherwise set a default of 27
		}
		count++;
	}
	count = 0;
	while (count < (71 * 71)) {
		if (topv[count] == 27) {
			if (findSet(count) != -1) {//makes sure it is a set
					topv[count] = topv[findSet(count)]; //for all defaults find their roots value and make that new value 
			}
			else {
				topv[count] = -1;
			}
		}
		count++;
	}
	return total;
}