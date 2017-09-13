#include <iostream>
#include <vector>
using namespace std;
class Avoid9{
  
public:
  int size_of_largest_subset = 0;

  int get_sum(vector<int> A){
    int sum = 0;
    for(int i=0;i<A.size();i++){
      sum += A[i];
    }
    return sum;
  }
  
  bool validate_subset(vector<int> sub_set,vector<int> temp,int start){

    if(temp.size() <= 3 ){
      
      for(int i=start;i<sub_set.size();i++){
	vector<int> cur_set = temp;
	cur_set.push_back(sub_set[i]);

	if(cur_set.size() == 3){
	  if( ( get_sum(cur_set) % 9 ) != 0 && size_of_largest_subset < sub_set.size()){
	    size_of_largest_subset = sub_set.size();
	  }
	}

	validate_subset(sub_set,cur_set,i+1);
      }
    }
  }

  int findSubset(vector<int> lst,vector<int> subset,int start){

    if(start < lst.size()){
      
      for(int i=start;i<lst.size();i++){

	vector<int> subset_cpy = subset;
	subset_cpy.push_back(lst[i]);

	if(subset_cpy.size() >= 3){
	  vector<int> tmp;
	  validate_subset(subset_cpy,tmp,0);
	}
	findSubset(lst,subset_cpy,i+1);
      }
      //      findSubset(lst,subset,start+1);
    }
    
  }
  
  int maxSizeOf9Free(vector<int> A){
    vector<int> sub;
    int largest_subset = findSubset(A,sub,0);
  }
};

int main(int argc,char *argv[]){
  vector<int> lt = { 10,20,30,40,50};
  Avoid9 inst;
  inst.maxSizeOf9Free(lt);
  return 0;
}
