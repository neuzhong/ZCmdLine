/******************************************************************************
 *
 *  file:  ZCmdLine.h
 *
 *  Copyright (c) 2015, Yi Zhong. *
 *  All rights reserved.
 *
 *  See the file COPYING in the top directory of this distribution for
 *  more information.
 *
 *  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

#ifndef _ZCOMMANDLINE
#define _ZCOMMANDLINE


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <memory>
#include "stdlib.h"


class ZValOpt{

public:
	typedef enum {INT_OPT,FLOAT_OPT,DOUBLE_OPT,STRING_OPT,CUSTORM_OPT} OptValueType;
	ZValOpt(const std::string& strOpt,
			const std::string& strOptFullname,
			const std::string& strDesc,
			bool bReq, OptValueType valuetype);

	virtual ~ZValOpt(){};
	void setOptValue(std::string strValue);
	bool isReq();

	int			getIntvalue();
	
	float		getFloatvalue();
	double		getDoublevalue();
	bool		isMatch(std::string strArg);
	std::string getDesc();
	std::string getOptionFullname();
	std::string getOpt();
	std::string getOptStringvalue();
	OptValueType m_valuetype;

	void getValue(int& value );
	void getValue(float& value );
	void getValue(double& value );
	void getValue(std::string& value );
	
		
protected:
	std::string m_strDesc;
	std::string m_strOpt;
	std::string m_strOptFullname;
	std::string m_strOptValue;
	bool m_bReq;
};


ZValOpt::ZValOpt(const std::string& strOpt,
				 const std::string& strOptFullname,
				 const std::string& strDesc,
				 bool bReq,
				 OptValueType valuetype){
						
	m_strOpt = strOpt;
	m_strOptFullname = strOptFullname;
	m_strDesc = strDesc;
	m_bReq = bReq;
	m_valuetype = valuetype;
	
}

bool ZValOpt::isMatch(std::string strArg)
{
	std::string str = strArg;
	//transform(str.begin(),str.end(),::tolower());
	if (str.compare(m_strOpt)==0||str.compare(m_strOptFullname)==0){
		return true;
	}

	return false;
}

bool ZValOpt::isReq(){
	return m_bReq;
}

void ZValOpt::setOptValue(std::string strValue){
	m_strOptValue = strValue ;
}

std::string ZValOpt::getDesc(){
	return m_strDesc;
}
std::string ZValOpt::getOptionFullname(){
	return m_strOptFullname;
}
std::string ZValOpt::getOpt(){
	return m_strOpt;
}

std::string ZValOpt::getOptStringvalue(){
	return m_strOptValue;

}

void	ZValOpt::getValue(int& value ){
		value = atoi(m_strOptValue.c_str());
}

void	ZValOpt::getValue(float& value ){
	value = (float) atof(m_strOptValue.c_str());
}

void	ZValOpt::getValue(double& value ){
	value = atof(m_strOptValue.c_str());
}

void	ZValOpt::getValue(std::string& value ){
	value = m_strOptValue;
}

//////////////////////////////////////////////////////////////////////////
class ZCmdLine{

public:
	ZCmdLine(const std::string& strDes );	
	virtual ~ZCmdLine(void);
	
	void init();
	int parse(const std::string strcmdline);
	int parse(int argc, char** argv);
	
	int addOption(ZValOpt& valopt);
	int showOptions();
	
	//int getOption(ZValOpt valopt);

protected:
	ZValOpt* whichOption(std::string strArg);
	std::string m_strVer;
	std::string m_strDesc;
	std::string m_strProgname;

private:
		
	std::list<ZValOpt*> m_listOpts;	
};

ZCmdLine::ZCmdLine(const std::string& strDes ){
	m_strDesc = strDes;
#if _DEBUG
	std::cout<<m_strDesc<<std::endl;
#endif
	
}

ZCmdLine::~ZCmdLine(){

}

int ZCmdLine::parse(int argc, char** argv){

	std::vector<std::string> args;
	for(int i=0; i<argc; i++){
		args.push_back(argv[i]);
	}

	m_strProgname = args.front();
	args.erase(args.begin());

	for(int i=0; i<args.size(); ){
		ZValOpt* pt = whichOption(args[i]);
		if (pt != NULL && pt->isReq()){
			i++;
			if (i == argc-1){
				break;
			}

			std::string strOptValue;
			int first = i;
			while(whichOption(args[i])==NULL){
				if (i>first){
					strOptValue += " ";
				}
				
				strOptValue += args[i];
				i++;
				if (i == argc-1){
					break;
				}
			}
			pt->setOptValue(strOptValue);	
			i--;
		}		
		i++;
	}

	return 0;
}

int ZCmdLine::addOption(ZValOpt& valopt){

	m_listOpts.push_back(&valopt);
	return 0;
}

ZValOpt* ZCmdLine::whichOption(std::string strArg)
{
	std::list<ZValOpt*>::iterator it;

	for (it = m_listOpts.begin(); it != m_listOpts.end(); it++ ){
		if ((*it)->isMatch(strArg)){
			return *it;
		}		
	}
		
	return NULL;
}

int ZCmdLine::showOptions()
{
	std::list<ZValOpt*>::iterator it;

	for (it = m_listOpts.begin(); it != m_listOpts.end(); it++ ){
		std::cout<<(*it)->getDesc()<<std::endl;
		std::cout<<(*it)->getOptionFullname()<<std::endl;
		std::cout<<(*it)->getOptStringvalue()<<std::endl;
	}

	return 0;
}
#endif