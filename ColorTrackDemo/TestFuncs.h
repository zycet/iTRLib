#include "itrbase.h"
#include "itrvision.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace itr_vision;
using namespace itr_math;

void PrintMatrix(Matrix Mat);
void PrintBlocks(vector<Block> blocks,S32 BlkNum);
void ReadFromFile(ifstream &file,void* data,S32 Length);
void PrintTargetInfo(Block blk);
void CheckOpennable(ifstream &infile);
void AddFileName(ifstream &infile,string filename,vector<string> &filenames);
void TestTrack(ifstream &InFiles,S32 Width,S32 Height);
