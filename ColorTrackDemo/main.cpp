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
    const S32 width  = 40;
    const S32 height = 40;
    ifstream infile("filelist.txt");
    string fname;
    vector<string> filenames;
    ifstream in;
    CheckOpennable(infile);
    AddFileName(infile,fname,filenames);
    for(S32 i = 0;i < filenames.size();i++)
    {
        cout << filenames[i].c_str() << endl;
        in.open(filenames[i].c_str());
        TestTrack(in,width,height);
        in.close();
    }
    return 0;
}
