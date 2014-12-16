//  Main.cpp
//  PA4


#include "binarysearchtree.h"
#include <queue>

using namespace std;

int main() {
    
    vector<string> v;
    v.push_back("./testdata/1l");
    v.push_back("./testdata/2l");
    v.push_back("./testdata/3l");
    v.push_back("./testdata/4l");
    v.push_back("./testdata/5l");
    v.push_back("./testdata/6l");
    v.push_back("./testdata/7l");
    v.push_back("./testdata/8l");
    v.push_back("./testdata/9l");
    v.push_back("./testdata/10l");
    v.push_back("./testdata/11l");
    v.push_back("./testdata/12l");
    v.push_back("./testdata/1p");
    v.push_back("./testdata/2p");
    v.push_back("./testdata/3p");
    v.push_back("./testdata/4p");
    v.push_back("./testdata/5p");
    v.push_back("./testdata/6p");
    v.push_back("./testdata/7p");
    v.push_back("./testdata/8p");
    v.push_back("./testdata/9p");
    v.push_back("./testdata/10p");
    v.push_back("./testdata/11p");
    v.push_back("./testdata/12p");
    v.push_back("./testdata/1r");
    v.push_back("./testdata/2r");
    v.push_back("./testdata/3r");
    v.push_back("./testdata/4r");
    v.push_back("./testdata/5r");
    v.push_back("./testdata/6r");
    v.push_back("./testdata/7r");
    v.push_back("./testdata/8r");
    v.push_back("./testdata/9r");
    v.push_back("./testdata/10r");
    v.push_back("./testdata/11r");
    v.push_back("./testdata/12r");
    
    
    
    cout<<setw(15)<<"File"<<setw(15)<<"Count"<<setw(15)<<"T.cost"<<setw(15)<<"Av.cost"<<endl;
    for (int i=0; i<v.size(); i++) {
        BinarySearchTree tmp(v[i]);
        
    }
    
    
    
    BinarySearchTree tmp; //should be output to screen
    tmp.read_in("./testdata/3r");
    tmp.print_in_order();
    tmp.print_by_level();
    
    BinarySearchTree tmp2; //should be output to file "output.txt"
    tmp.read_in("./testdata/5p");
    tmp.print_in_order();
    tmp.print_by_level();
    
    
    return 0;
}
