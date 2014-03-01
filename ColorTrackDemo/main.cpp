#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "itrbase.h"
#include "itrvision.h"
#include "TestFuncs.h"
#include <list>
using namespace std;
using namespace itr_vision;
using namespace itr_math;

int main()
{
    const S32 width  = 64;
    const S32 height = 36;
//    ifstream infile("filelist.txt");
//    string fname;
//    vector<string> filenames;
//    ifstream in;
//    CheckOpennable(infile);
//    AddFileName(infile,fname,filenames);
//    Takeoff();
//    for(S32 i = 0;i < filenames.size();i++)
    while(1)
    {
//        cout << filenames[i].c_str() << endl;
//        in.open(filenames[i].c_str());
        TestTrack(cin,width,height);
//        in.close();
    }
    //Land();
    return 0;
}
