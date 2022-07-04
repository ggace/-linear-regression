#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <string.h>
#include <cmath>
#include <iostream>

using namespace std;

/* ====== 변수 ====== */
map<double, double> VALUES;

int repeat = 1000000000;
double learning_mate = 0.001;

int value_x_max = 4;
int value_x_min = 1;

double min_w, min_b;
double min_cost;

/* ====== 함수 ====== */
//values 가져오기
map<double, double> stringToMap_double_double(char* text);
void setValues();
//선형회귀
double getCost(double w, double b);
double getWInclination(double w, double b);
double getBInclination(double w, double b);

void printResult(double w, double b);

double getFx(double w, double b, double x){
    return w * x + b;
}

void clearFile(){
    string filePath = "../files/result.txt";
    ofstream file(filePath);

    if(file.is_open()){
        file << "";
	} else {
		return;
	}

	file.close();
	
}

void writeFile(double w, double b){
    string filePath = "../files/result.txt";
    ofstream file(filePath, std::ios_base::out | std::ios_base::app);

    if(file.is_open()){
        
		file << to_string(w).c_str() << ": ";
	    file << to_string(b).c_str() << "\n"; 
        cout << "executed" << endl;
	} else {
		return;
	}

	file.close();
	
}

int main(void){
    
    clearFile();
    double w = 1.0;
    double b = 0.0;

    double cost;
    int i = 0;

    double beforeCost;

    setValues();
    
    
    
        
    while(true){
        cost = getCost(w, b);

        

        if(i == 0){
            
            min_cost = cost;
            min_w = w;
            min_b = b;
        }

        if(min_cost > cost){
            min_w = w;
            min_b = b;
            min_cost = cost;
            writeFile(w, b);

            cout << w << ", " << b << " : " << cost << endl;
        }

        if(cost == 0){
            printResult(w, b);
            return 0;
        }
        
        w -= getWInclination(w, b) * learning_mate;

        if(i >= 1000){
            break;
        }
        i++;
        
    }

    printResult(min_w, min_b);

    system("python ../python/graph.py");

    return 0;

    
}

map<double, double> stringToMap_double_double(char* text){
    
    map<double, double> mymap;
    char *token;
    
    token = strtok(text, "\n");
    while (token != NULL) {
        string s(token);
        size_t pos = s.find(":");
        mymap[atoi(s.substr(0, pos).c_str())] = atoi(s.substr(pos + 1, string::npos).c_str());
        token = strtok(NULL, "\n");
    }

    return mymap;
}

void setValues(){
    string lines;
    
    string line;
    ifstream file("../files/values.txt"); // example.txt 파일을 연다. 없으면 생성. 
	if(file.is_open()){
		while(getline(file, line)) {
			lines += line + "\n";
		}
		file.close(); // 열었떤 파일을 닫는다. 
	} else {
		return;
	}

    VALUES = stringToMap_double_double((char*)lines.c_str());
}

double getCost(double w, double b){
    double sum = 0;
    for (auto keyval : VALUES){
        sum += pow(keyval.second - (w * keyval.first + b), 2);
    }

    
    
    return sum / VALUES.size();
}

double getWInclination(double w, double b){
    double sum = 0;
    
    for (auto keyval : VALUES){
        sum += 2*pow(keyval.first, 2)*w + 2*keyval.first*b - 2*keyval.second*keyval.first;
    }

    return sum / VALUES.size();
}

double getBInclination(double w, double b){
    double sum = 0;
    
    for (auto keyval : VALUES){
        sum += 2*keyval.first*w - 2*keyval.second - 2*b;
    }

    return sum / VALUES.size();
}

void printResult(double w, double b){
    cout << endl << "result: " << w << "x + " << b << endl;
}