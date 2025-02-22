#include "python_executor.h"

#include "Python.h"

PythonExecutor::PythonExecutor()
{	//��һ������ʼ��Python
	//�ڵ���Python���ṩ�ĸ�C��API֮ǰ��ͨ��ִ�г�ʼ��
	//�����Python���ڽ�ģ�顢__main__��sys��
	Py_Initialize();

	//char *argv[2];
	//argv[0] = "arg1";
	//argv[1] = "arg2";
	//PySys_SetArgv(2, argv);

	//���Ĳ���ִ�е��ýű��ļ�����,ע���ļ���·��
	
}

PythonExecutor::~PythonExecutor()
{
	Py_Finalize();
}

bool PythonExecutor::Init()
{	//����ʼ���Ƿ����
	if (!Py_IsInitialized())
	{
		return false;
	}
	PyRun_SimpleString("import sys");
	return true;
}

void PythonExecutor::SetRunPath(const std::string & path)
{

	PyRun_SimpleString("import os");
	std::string exe_cmd = "os.chdir('" + path + "')";
	PyRun_SimpleString(exe_cmd.c_str());
}

bool PythonExecutor::RunExe(const std::string & path)
{
	std::string exe_cmd = "os.system('python " + path + "')";
	PyRun_SimpleString(exe_cmd.c_str());
	return true;
}
