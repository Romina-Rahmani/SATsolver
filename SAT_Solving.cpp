//ENSC 251, LAB05
//SAT Solving
//Romina Rahmani
//301325094

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <set>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

set<int> propose_solution(int variables_count){
	set<int> solution;
	for(int i=0; i<variables_count; i++ ){
		int true_or_false= -1;
		if (rand()%2 == 1){ //If the random number is odd then
			true_or_false= 1;  // the random number we input in our solution is true.
		}
		solution.insert((i+1)*true_or_false);
	}
return solution;
}

set<int> get_clause(string file_line){
	set<int> clause_set;
	stringstream stream(file_line);
	int j= 1;
	while (j!= 0){
		stream >> j;
		if(!stream)
			break;
		if(j==0) 
			break;
	clause_set.insert(j);
	}
return clause_set;
}

int main (){
	string fileName= "DIMACS.txt";
	string ignored_string1;
	string ignored_string2;
	string file_line;
	int var_count;
	int clause_count;
	ifstream inFile;
	set<int> proof; 
	vector<set <int> > clauses_list;

	do {
		inFile.open(fileName.c_str());
		if(inFile.fail()){
				cerr << "File could not be opened." << endl;
			}
		} while (inFile.fail());
	if (!(inFile >> ignored_string1)){
		if (inFile.eof()){
			cerr << "Error: Input data file is empty";
			inFile.close();
			return 0;
		}
	}
	inFile >> ignored_string2; 	//Read charactars on first line and assign.
	inFile >> var_count;
	inFile >> clause_count;
	getline(inFile,file_line);
	//Put set made from each line of the file into a vector clauses_list.
	do {
		getline (inFile,file_line);
		set<int> clause= get_clause(file_line);
		clauses_list.push_back(clause);
	} while (inFile.fail());
	bool solved= false; 
	bool valid_clause= true;
	size_t clauses_list_length= clauses_list.size();
	while (true){
		set<int> solution= propose_solution(var_count);
		for (size_t i=0; i<clauses_list_length; i++){
			set<int> checking_clause= clauses_list[i];
			if (checking_clause.size() == 0)
				break;
		proof.clear();
		set_intersection(solution.begin(),solution.end(),checking_clause.begin(),
						checking_clause.end(), inserter(proof, proof.begin()));
		size_t matching_num_count= proof.size();
		if (matching_num_count == 0){
			valid_clause= false;
			break;
		}
	}
	if (valid_clause == false){
		valid_clause= true;
	}
	else {
		cout << "V";
		for (set<int>::iterator it2=solution.begin(); it2!=solution.end(); ++it2)
			{ cout << ' ' << *it2; }
return 0;
		}
	}
}