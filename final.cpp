// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2016

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &l);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

Data * addresses[1000000];
int counts[1000000];
int cleardecimal;
list<Data *> bins[1000000];
int group, firstdigs;
list<Data *> tmpList;
list<Data *>::iterator itt; 
list<Data *>::iterator itt2;   
list<Data *>::iterator temp1;
list<Data *>::iterator temp2;
int i, data1, data2, c1, c2;

int larger(Data * first, Data * second) {
    c1=20;
    c2=20;
    while ((first->data)[c1] != '.') c1--;
    while ((second->data)[c2] != '.') c2--;
    if (c1 == c2) return (first->data).compare((second->data)) < 0;
    else return (c1 < c2);
}

int findDecimal(string s) {
    return strchr(s.c_str(), '.') - s.c_str();
}

void radixSort(list<Data *> &l) { //T1, T2
    for (itt = l.begin(); itt != l.end(); itt++) {
        firstdigs = findDecimal((*itt)->data) - 15;
        if (firstdigs < 0)
            group = 0;
        else
            group = atoi((*itt)->data.substr(0, firstdigs).c_str());
        bins[group].push_back(*itt);
    }
    l.clear();
    for (int i = 0; i <= 100000; i++) {
        bins[i].sort(larger); //GOTTA OVERLOAD THAT OPERATOR
        l.splice(l.end(), bins[i]);
    }
}

void countSort(list<Data *> &l) { //T3

    for (itt = l.begin(); itt != l.end(); itt++) {
        cleardecimal = (int) ((atof(((*itt)->data).c_str())+.000001) * 1000);
        addresses[cleardecimal] = *itt;        
        counts[cleardecimal]++;
    }
    
    for (i = 0, itt = l.begin(); i < 1000000 && itt != l.end(); i++) {
        for (int j = 0; j < counts[i]; j++) {
            *itt = addresses[i];
            itt++;
        }
    }
}  

void insertionSort(list<Data *> &l) { //T4

    for (itt = l.begin(); itt != l.end(); ++itt) {
        temp1 = itt;
        temp2 = itt;
        temp2--;
        while (temp1 != l.begin() && !((*temp2)->data.compare((*temp1)->data) < 0)) {
            iter_swap(temp2, temp1);
            temp2--;
            temp1--;
        }
    }
}

void sortDataList(list<Data *> &l) {  //PICK T1, T2, T3, OR T4
    list<Data *>::iterator itt = l.begin();
    if (l.size() < 200000) { //T1
        cout << "TRYING T1.TXT" << endl;
        radixSort(l);
        return; }
    else if ((atoi(((*itt)->data).c_str()) < 1001) && (atoi(((*itt)->data).c_str()) > 0)) { //T3
        countSort(l); 
        cout << "TRYING T3.TXT" << endl; //T3
        return; }
    itt = l.begin();
    advance(itt,1);
    itt2 = itt;
    itt = l.begin();
    if ((*itt)->data.substr(0,9) == (*itt2)->data.substr(0,9)) { //T4
        cout << "TRYING T4.TXT" << endl; //T4
        insertionSort(l);
        return; }
    else {
        cout << "TRYING T2.TXT" << endl; //T2
        radixSort(l);
        return; }
}
//END






