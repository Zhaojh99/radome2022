#include <fstream>

#include "gen_FDTD_meta.h"
#include "../Qt/global_config.h"


bool GenFDTDCalcMeta::WriteMetaMsg(const std::string & path)
{
	std::ofstream outfile(path);
	if (!outfile.is_open())
	{
		return false;
	}
	const auto& materials_index = data_manager_.GetRadomeData()->GetAllMaterials();
	outfile << fre_ << std::endl;
	outfile << point_path_.size() - 1 << std::endl;
	outfile << cpu_core_ << std::endl;
	for (auto& index : materials_index) {
		auto mat = data_manager_.GetMaterialData(index);
		if (mat == nullptr) {
			return false;
		}
		outfile << mat->GetEps0() << " " << mat->GetMu0() << std::endl;
	}
	for (int i = point_path_.size() - 1; i >= 0; --i) {
		outfile << point_path_[i] << std::endl;
	}
	outfile << mesh_type_ << std::endl;
	outfile << 0 << std::endl;
	outfile << source_path_ << std::endl;
	double ExcPos = 0.0;
	if (data_manager_.GetSource()->getGraphTrans().getTrans_z() > 0) ExcPos = data_manager_.GetSource()->getGraphTrans().getTrans_z();
	outfile << ExcPos << std::endl;
	outfile << result_path_ << std::endl;
	outfile.close();
	return true;
}
/*
1 ��1�� ����Ƶ��(��λHz)
2 ��2�� ���Ӳ�����ע����������������
3 ��3�� CPU�߳���(����)
4 ��4-6�У���糣��ʵ�����鲿�������Ӧ3�㣬������3�С�
5 ͬ�� 4-6�У����ϵ�������������㣬�м�㣬���ڲ�
6 ͬ��
7 ��7-10�У���ת�����ļ�Ŀ¼��ע�⣺3�����ӣ�4�����棬
8 ͬ�ϣ�7-10�У����ϵ�������������㣬�м�㣬���ڲ�
9
10
11 �ʷּ�����ƣ�0: 1/20, 1: 1/25, 2: 1/30; 3: 1/40.
12 ��ת����ģʽ�����2.2��˵��
13 ���뼤�����ļ�Ŀ¼ ���2.3��˵��
14 ���볡����λ�� ExcPos(��λm)�����2.2��˵��
15 ������Ŀ¼
*/
