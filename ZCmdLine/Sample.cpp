// Sample.cpp : Defines the entry point for the console application.
//


#include <string>
#include "ZCmdLine.h"

using namespace std;

int main(int argc, char* argv[])
{
	ZCmdLine cmd("Command description message.");

	string strfilename;
	float nthred;

	ZValOpt filenameOpt("-f","-filename","input file name",true,ZValOpt::STRING_OPT);
	ZValOpt thresholdOpt("-t","-threshold","threshold for mask image",true,ZValOpt::FLOAT_OPT);

	cmd.addOption(filenameOpt);
	cmd.addOption(thresholdOpt);
	
	cmd.parse(argc,argv);

	cmd.showOptions();

	filenameOpt.getValue(strfilename);
	thresholdOpt.getValue(nthred);

	cout<<strfilename<<std::endl;
	cout<<nthred<<std::endl;

	return 0;
}

