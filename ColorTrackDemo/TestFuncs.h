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
void ReadFromFile(istream &file,F32* H,F32* S,F32* L,S32 Length);
void PrintTargetInfo(Block blk);
void CheckOpennable(istream &infile);
void AddFileName(istream &infile,string filename,vector<string> &filenames);
void TestTrack(istream &InFiles,S32 Width,S32 Height);
void Takeoff();
void Land();
