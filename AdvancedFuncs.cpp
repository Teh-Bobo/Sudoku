#include "AdvancedFuncs.h"
#include <vector>

class Point
{
private:
	int x,y;
public:
	Point(int x,int y) {this->x = x; this->y =y;};
	int getX() {return x;};
	int getY() {return y;};
	bool operator== (Point &other) {return this->x == other.x && this->y == other.y;};
	friend std::ostream& operator<< (std::ostream& out, Point p) {out << p.x << "," << p.y; return out;};
};
bool BoxPairAdvanced(int** solution, bool*** possible, bool verbose, std::ostream& out)
{
	std::vector< std::vector<Point*> > pairs(9,std::vector<Point*>(9,NULL));
	bool breakout = false;
	bool returnval = false;
	for(int i = 0; i < 9; i+=3)
		for(int j = 0; j < 9; j+=3){
			for(int k = 0; k < 9; k++){
				breakout = false;
				for(int l = i; l < i + 3 && !breakout; l++)
					for(int m = j; m < j + 3 && !breakout; m++){
						if(solution[l][m] == k+1){
							pairs[k].clear();
							breakout = true;
							break;
						}
						if(solution[l][m])
							continue;
						if(possible[l][m][k])
							//TODO delete the points at some point
							pairs[k].push_back(new Point(l,m));
					}
			}
			for(int l = 0; l < 8; l++)
				for(int m = l+1; m < 9; m++){
					if(pairs[l].size() != 2)
						break;
					if(pairs[m].size() != 2)
						continue;
					if(pairs[l][0][0] == pairs[m][0][0] && pairs[l][1][0] == pairs[m][1][0]){
						if(verbose)
							out << "Advanced pair found at " << pairs[l][0]->getX() << "," << 
								pairs[l][0]->getY() << " and " << pairs[l][1]->getX() <<
								"," << pairs[l][1]->getY() << "; with #'s " << l+1<< " and " 
								<< m+1 << std::endl;
						for(int k =0; k < 9; k++){
							if(k == l || k == m)
								continue;
							possible[pairs[l][0]->getX()][pairs[l][0]->getY()][k] = false;
							possible[pairs[l][1]->getX()][pairs[l][1]->getY()][k] = false;
						}
						returnval = true;
					}
				}
			for(int l=0; l < 9; l++)
				pairs[l].clear();
		}
	return returnval;
}
bool RowAdvanced(int** solution, bool*** possible, bool verbose, std::ostream& out)
{
	int count;
	int pos;
	bool breakout = false;
	bool returnval = false;
	for(int i = 0; i < 9; i+=3)
		for(int j = 0; j < 9; j+=3)
			for(int k = 0; k < 9; k++){
				breakout = false;
				pos = count = 0;
				for(int l = i; l < i + 3 && !breakout; l++)
					for(int m = j; m < j + 3 && !breakout; m++){
						if(solution[l][m] == k+1){
							count = 0;
							breakout = true;
							break;
						}
						if(solution[l][m])
							continue;
						if(possible[l][m][k]){
							if(count == 0)
								pos = l;
							count++;
							if(pos != l){
								count = 0;
								breakout = true;
								break;
							}
						}
					}
				//if after we step through the box all the numbers we found
				//are in one row then the rest of the row cant have that
				//number
				if(!breakout && count > 1 && count <= 3){
					if(verbose)
						out << "Removing " << k + 1 << " from row: " << pos << " except box " << i << "," << j << std::endl;
					for(int p = 0; p < 9; p++){
						if((p/3)*3 == j)
							continue;
						possible[pos][p][k] = false;
						returnval = true;
					}
				}
			}
	return returnval;
}

bool ColumnAdvanced(int** solution, bool*** possible, bool verbose, std::ostream& out)
{
	int count,pos;
	bool breakout,returnval = false;
	for(int i = 0; i < 9; i+=3)
		for(int j = 0; j < 9; j+=3)
			for(int k = 0; k < 9; k++){
				breakout = false;
				pos = count = 0;
				for(int m = j; m < j+3 && !breakout; m++)
					for(int l = i; l < i+3 && !breakout; l++){
						if(solution[l][m] == k+1){
							count = 0;
							breakout = true;
							break;
						}
						if(solution[l][m])
							continue;
						if(possible[l][m][k]){
							if(count == 0)
								pos = m;
							count++;
							if(pos != m){
								count = 0;
								breakout = true;
								break;
							}
						}
					}
				if(!breakout && count > 1 && count <= 3){
					if(verbose)
						out << "Removing " << k + 1 << " from column: " << pos << " except box " << i << "," << j << std::endl;
					for(int p = 0; p < 9; p++){
						if((p/3)*3 == i)
							continue;
						possible[p][pos][k] = false;
						returnval = true;
					}
				}
			}
	return returnval;
}
