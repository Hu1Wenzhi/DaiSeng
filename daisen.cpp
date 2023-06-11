#include <iostream>
#include <stdio.h>
using namespace std;

/*
	float make(float rate, float coef=1) {
		float fac = rate / output_v[0];
		*facility += fac / coef;

		for (int i=0; i<input; i++) {
			*input_list[i] -= input_v[i] * fac;
		}

		for (int i=0; i<output; i++) {
			*output_list[i] += output_v[i] * fac;
		}
		return fac;
	}*/

// 材料类产品产量
static int shui;
static int qing;
static int chuan;
static int tie_kuang;
static int tong_kuang;
static int shi_kuang;
static int tai_kuang;
static int tan_kuang;
static int ke_ran_bing;
static int yuan_you;
static int tie_kuai;
static int tong_kuai;
static int gui_kuai;
static int tai_kuai;
static int shi_cai;
static int shi_mo;
static int su_liao;
static int jing_you;
static int shi_mo_xi;

static int ci_tie;
static int xian_quan;
static int jing_ge;
static int bo_li;
static int tai_he_jing;
static int jing_gang_shi;
static int jing_ti;
static int qing_bang;

static int gang_cai;
static int dian_dong_ji;
static int tai_bo_li;
static int leng_jing;
static int tai_jing;
static int tui_jing_qi;
static int jia_li_tui;

static int chi_lun;
static int wo_lun;
static int gui_kuang;
static int dian_lu_ban;
static int liu_suan;
static int na_mi_guan;
static int pei_song;
static int yun_shu_ji;
static int yun_shu_chuan;

static int dian_jiang;
static int ci_chang_huan;
static int kuan_dai;
static int chu_li_qi;
static int li_zi;
static int ka_xi_mier;
static int qi_yi;
static int wei_mian;
static int tou_jing;

static int guang_zi;
static int wei_jing;
static int liang_zi;

static int lan_tang;
static int hong_tang;
static int huang_tang;
static int zi_tang;
static int lv_tang;

// 建筑类产品产量
static int dian_li;
static int wu_xian;
static int feng_li;
static int huo_li;

static int chuan_song;
static int chuan_song_h;
static int chuan_song_s;
static int si_xiang;
static int xiao_chu;
static int chu_ye_qi;
static int xing_xing_zhan;
static int xing_ji_zhan;

static int feng_lian;
static int feng_lian_h;
static int feng_lian_s;
static int gao_feng;
static int liu_su;
static int cai_kuang;
static int chou_shui;
static int cui_qu;
static int jing_lian;

static int zhi_zuo;
static int zhi_zuo_2;
static int dian_hu_rong;
static int yan_jiu;
static int hua_gong;

// 生产设施建筑所需
static float cai_kuang_ji;
static float rong_lu;
static float zhi_zuo_tai;
static float jing_lian_chang;
static float hua_gong_chang;
static float yan_jiu_zhan;
static float li_zi_dui_zhuang;

const float		ye_v		=1; // 冶炼速度系数；
const float		make_v		=1; // 制造速度系数；
const float		hua_v		=1; // 化工速度系数；

void Sum(){
	if (rong_lu !=0)
		cout << "熔炉 " << rong_lu << "; ";
	if (zhi_zuo_tai !=0)
		cout << "制作台 " << zhi_zuo_tai << "; ";
	if (jing_lian_chang !=0)
		cout << "精炼厂 " << jing_lian_chang << "; ";
	if (hua_gong_chang !=0)
		cout << "化工厂 " << hua_gong_chang << "; ";
	if (yan_jiu_zhan !=0)
		cout << "研究站 " << yan_jiu_zhan << "; ";


	cout << endl;
}

// 工艺
class Technology {
public:
	Technology():input(1),
				 output(1){}



	// 所需设备
	float *facility;

	// 原材料
	int input; // 种类数量
	int *input_list[10];
	float input_v[10]; // 1min

	// 产出
	int output;
	int *output_list[10];
	float output_v[10]; // 1min产量列表，第一个为主产物。

	// rate: 件/min
	float make(float rate, float coef=1) {
		
		float fac = rate / output_v[0];
		*facility += fac / coef;
		// cout << fac << " " << coef << *facility << endl;

		for (int i=0; i<input; i++) {
			*input_list[i] -= input_v[i] * fac;
		}

		for (int i=0; i<output; i++) {
			*output_list[i] += output_v[i] * fac;
		}
		return fac / coef;
	}
};

class CaiKuang: public Technology {
public:
	CaiKuang(float rate, int *output) {
		facility = &cai_kuang_ji;

		input = 0;

		output_list[0] = output;
		output_v[0] = 36;
		make(rate, 1);
	}
};

class YeTie: public Technology {
public:
	YeTie(float rate) {
		// 用熔炉
		facility = &rong_lu;

		input_list[0] = &tie_kuang;
		input_v[0] = 60;

		// 产出铁块
		output_list[0] = &tie_kuai;
		output_v[0] = 60;

		new CaiKuang(rate, &tie_kuang);
		
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YeTie " << num << endl;
	}
	static float num;
};
float YeTie::num = 0;

class YeTong: public Technology {
public:
	YeTong(float rate) {
		facility = &rong_lu;

		input_list[0] = &tong_kuang;
		input_v[0] = 60;

		output_list[0] = &tong_kuai;
		output_v[0] = 60;

		new CaiKuang(rate, &tong_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YeTong " << num << endl;
	}
	static float num;
};
float YeTong::num = 0;

class YeGui: public Technology {
public:
	YeGui(float rate) {
		facility = &rong_lu;

		input_list[0] = &gui_kuang;
		input_v[0] = 60;

		output_list[0] = &gui_kuai;
		output_v[0] = 30;

		new CaiKuang(rate*2, &gui_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YeGui " << num << endl;
	}
	static float num;
};
float YeGui::num = 0;

class YeTai: public Technology {
public:
	YeTai(float rate) {
		facility = &rong_lu;

		input_list[0] = &tai_kuang;
		input_v[0] = 60;

		output_list[0] = &tai_kuai;
		output_v[0] = 30;

		new CaiKuang(rate*2, &tai_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YeTai " << num << endl;
	}
	static float num;
};
float YeTai::num = 0;

class Chuan: public Technology {
public:
	Chuan(float rate) {
		facility = &li_zi_dui_zhuang;

		input_list[0] = &qing;
		input_v[0] = 240;

		output_list[0] = &chuan;
		output_v[0] = 120;

		new CaiKuang(rate*2, &qing);
		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "Chuan " << num << endl;
	}
	static float num;
};
float Chuan::num = 0;

class JingGe: public Technology {
public:
	JingGe(float rate) {
		facility = &rong_lu;

		input_list[0] = &tai_kuai;
		input_v[0] = 30;

		output_list[0] = &jing_ge;
		output_v[0] = 30;

		new YeTai(rate);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "JingGe " << num << endl;
	}
	static float num;
};
float JingGe::num = 0;

class BoLi: public Technology {
public:
	BoLi(float rate) {
		facility = &rong_lu;

		input_list[0] = &shi_kuang;
		input_v[0] = 60;

		output_list[0] = &bo_li;
		output_v[0] = 30;

		new CaiKuang(rate*2, &shi_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "BoLi " << num << endl;
	}
	static float num;
};
float BoLi::num = 0;

class ShiCai: public Technology {
public:
	ShiCai(float rate) {
		facility = &rong_lu;

		input_list[0] = &shi_kuang;
		input_v[0] = 60;

		output_list[0] = &shi_cai;
		output_v[0] = 60;

		new CaiKuang(rate, &shi_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ShiCai " << num << endl;
	}
	static float num;
};
float ShiCai::num = 0;

class ShiMo: public Technology {
public:
	ShiMo(float rate) {
		facility = &rong_lu;

		input_list[0] = &tan_kuang;
		input_v[0] = 60;

		output_list[0] = &shi_mo;
		output_v[0] = 30;

		new CaiKuang(rate*2, &tan_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ShiMo " << num << endl;
	}
	static float num;
};
float ShiMo::num = 0;

class JingGang: public Technology {
public:
	JingGang(float rate) {
		facility = &rong_lu;

		input_list[0] = &shi_mo;
		input_v[0] = 30;
		new ShiMo(rate);

		output_list[0] = &jing_gang_shi;
		output_v[0] = 30;

		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "JingGang " << num << endl;
	}
	static float num;
};
float JingGang::num = 0;

class JingLian: public Technology {
public:
	JingLian(float rate) {
		facility = &jing_lian_chang;

		input_list[0] = &yuan_you;
		input_v[0] = 30;

		output = 2;
		output_list[0] = &jing_you;
		output_v[0] = 30;
		output_list[1] = &qing;
		output_v[1] = 15;

		new CaiKuang(rate, &yuan_you);
		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "JingLian " << num << endl;
	}
	static float num;
};
float JingLian::num = 0;

class ShiMoXiH: public Technology {
public:
	ShiMoXiH(float rate) {
		facility = &hua_gong_chang;

		input_list[0] = &ke_ran_bing;
		input_v[0] = 60;
		new CaiKuang(rate, &ke_ran_bing);

		output_list[0] = &shi_mo_xi;
		output_v[0] = 60;
		output_list[1] = &qing;
		output_v[1] = 30;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "ShiMoXiH " << num << endl;
	}
	static float num;
};
float ShiMoXiH::num = 0;

class LieJie: public Technology {
public:
	LieJie(float rate) {
		facility = &jing_lian_chang;

		input = 2;
		input_list[0] = &jing_you;
		input_v[0] = 15;
		new JingLian(rate*4/3);
		input_list[1] = &qing;
		input_v[1] = 30;

		output_list[0] = &qing;
		output_v[0] = 45;
		output_list[1] = &shi_mo;
		output_v[1] = 15;

		num += make(rate*2, 1); // 产出4个氢消耗2个氢，所以这里为了达到rate目标产量，设置2条产线。
	}
	static void Num(){
		if (num!=0)
		cout << "LieJie " << num << endl;
	}
	static float num;
};
float LieJie::num = 0;

class CiTie: public Technology {
public:
	CiTie(float rate) {
		facility = &rong_lu;

		input_list[0] = &tie_kuang;
		input_v[0] = 40;

		output_list[0] = &ci_tie;
		output_v[0] = 40;

		new CaiKuang(rate*2/3, &tie_kuang);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "CiTie " << num << endl;
	}
	static float num;
};
float CiTie::num = 0;

class XianQuan: public Technology {
public:
	XianQuan(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &ci_tie;
		input_v[0] = 120;
		new CiTie(rate);
		input_list[1] = &tong_kuai;
		input_v[1] = 60;
		new YeTong(rate/2);

		output_list[0] = &xian_quan;
		output_v[0] = 120;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "XianQuan " << num << endl;
	}
	static float num;
};
float XianQuan::num = 0;

class ChiLun: public Technology {
public:
	ChiLun(float rate) {
		facility = &zhi_zuo_tai;

		input_list[0] = &tie_kuai;
		input_v[0] = 60;

		output_list[0] = &chi_lun;
		output_v[0] = 60;

		new YeTie(rate*1);
		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ChiLun " << num << endl;
	}
	static float num;
};
float ChiLun::num = 0;

class GangCai: public Technology {
public:
	GangCai(float rate) {
		facility = &rong_lu;

		input_list[0] = &tie_kuai;
		input_v[0] = 60;

		output_list[0] = &gang_cai;
		output_v[0] = 20;

		new YeTie(rate*3);
		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "GangCai " << num << endl;
	}
	static float num;
};
float GangCai::num = 0;

class DianDongJi: public Technology {
public:
	DianDongJi(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &tie_kuai;
		input_v[0] = 60;
		new YeTie(rate*2);
		input_list[1] = &chi_lun;
		input_v[1] = 30;
		new ChiLun(rate);
		input_list[2] = &xian_quan;
		input_v[2] = 30;
		new XianQuan(rate);

		output_list[0] = &dian_dong_ji;
		output_v[0] = 30;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "DianDongJi " << num << endl;
	}
	static float num;
};
float DianDongJi::num = 0;

class LengJing: public Technology {
public:
	LengJing(float rate) {
		facility = &zhi_zuo_tai;

		input_list[0] = &bo_li;
		input_v[0] = 90;

		output_list[0] = &leng_jing;
		output_v[0] = 60;

		new BoLi(rate*3/2);
		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "LengJing " << num << endl;
	}
	static float num;
};
float LengJing::num = 0;

class ChongZheng: public Technology {
public:
	ChongZheng(float rate) {
		facility = &jing_lian_chang;

		input = 3;
		input_list[0] = &jing_you;
		input_v[0] = 30;
		input_list[1] = &qing;
		input_v[1] = 15;
		new JingLian(rate*2/3);
		input_list[2] = &tan_kuang;
		input_v[2] = 15;
		new CaiKuang(rate/3, &tan_kuang);

		output_list[0] = &jing_you;
		output_v[0] = 45;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "ChongZheng " << num << endl;
	}
	static float num;
};
float ChongZheng::num = 0;

class SuLiao: public Technology {
public:
	SuLiao(float rate) {
		facility = &hua_gong_chang;

		input = 2;
		input_list[0] = &jing_you;
		input_v[0] = 40;
		new ChongZheng(rate*2);
		input_list[1] = &shi_mo;
		input_v[1] = 20;
		new ShiMo(rate);

		output_list[0] = &su_liao;
		output_v[0] = 20;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "SuLiao " << num << endl;
	}
	static float num;
};
float SuLiao::num = 0;

class YouJi: public Technology {
public:
	YouJi(float rate) {
		facility = &hua_gong_chang;

		input = 3;
		input_list[0] = &su_liao;
		input_v[0] = 20;
		new SuLiao(rate*2);
		input_list[1] = &jing_you;
		input_v[1] = 10;
		new ChongZheng(rate);
		input_list[2] = &shui;
		input_v[2] = 10;
		new CaiKuang(rate, &shui);

		output_list[0] = &jing_ti;
		output_v[0] = 10;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "YouJi " << num << endl;
	}
	static float num;
};
float YouJi::num = 0;

class TaiJing: public Technology {
public:
	TaiJing(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &jing_ti;
		input_v[0] = 15;
		new YouJi(rate);
		input_list[1] = &tai_kuai;
		input_v[1] = 45;
		new YeTai(rate*3);

		output_list[0] = &tai_jing;
		output_v[0] = 15;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "TaiJing " << num << endl;
	}
	static float num;
};
float TaiJing::num = 0;

class WoLun: public Technology {
public:
	WoLun(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &dian_dong_ji;
		input_v[0] = 60;
		new DianDongJi(rate*2);
		input_list[1] = &xian_quan;
		input_v[1] = 60;
		new XianQuan(rate*2);

		output_list[0] = &wo_lun;
		output_v[0] = 30;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "WoLun " << num << endl;
	}
	static float num;
};
float WoLun::num = 0;

class CiChangHuan: public Technology {
public:
	CiChangHuan(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &wo_lun;
		input_v[0] = 40;
		new WoLun(rate*2);
		input_list[1] = &ci_tie;
		input_v[1] = 60;
		new CiTie(rate*3);
		input_list[2] = &shi_mo;
		input_v[2] = 20;
		new ShiMo(rate);

		output_list[0] = &ci_chang_huan;
		output_v[0] = 20;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "CiChangHuan " << num << endl;
	}
	static float num;
};
float CiChangHuan::num = 0;

class DianLuBan: public Technology {
public:
	DianLuBan(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &tie_kuai;
		input_v[0] = 120;
		new YeTie(rate);
		input_list[1] = &tong_kuai;
		input_v[1] = 60;
		new YeTong(rate/2);

		output_list[0] = &dian_lu_ban;
		output_v[0] = 120;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "DianLuBan " << num << endl;
	}
	static float num;
};
float DianLuBan::num = 0;

class LiuSuan: public Technology {
public:
	LiuSuan(float rate) {
		facility = &hua_gong_chang;

		input = 3;
		input_list[0] = &jing_you;
		input_v[0] = 60;
		new ChongZheng(rate*3/2);
		input_list[1] = &shi_kuang;
		input_v[1] = 80;
		new CaiKuang(rate*2, &shi_kuang);
		input_list[2] = &shui;
		input_v[2] = 30;
		new CaiKuang(rate, &shui);

		output_list[0] = &liu_suan;
		output_v[0] = 40;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "LiuSuan " << num << endl;
	}
	static float num;
};
float LiuSuan::num = 0;

class TaiHeJing: public Technology {
public:
	TaiHeJing(float rate) {
		facility = &rong_lu;

		input = 3;
		input_list[0] = &tai_kuai;
		input_v[0] = 20;
		new YeTai(rate);
		input_list[1] = &gang_cai;
		input_v[1] = 20;
		new GangCai(rate);
		input_list[2] = &liu_suan;
		input_v[2] = 40;
		new LiuSuan(rate*2);

		output_list[0] = &tai_he_jing;
		output_v[0] = 20;

		num += make(rate, ye_v);
	}
	static void Num(){
		if (num!=0)
		cout << "TaiHeJing " << num << endl;
	}
	static float num;
};
float TaiHeJing::num = 0;

class ShiMoXi: public Technology {
public:
	ShiMoXi(float rate) {
		facility = &hua_gong_chang;

		input = 2;
		input_list[0] = &shi_mo;
		input_v[0] = 60;
		new ShiMo(rate*3/2);
		input_list[1] = &liu_suan;
		input_v[1] = 20;
		new LiuSuan(rate/2);

		output_list[0] = &shi_mo_xi;
		output_v[0] = 40;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "ShiMoXi " << num << endl;
	}
	static float num;
};
float ShiMoXi::num = 0;

class NaMiGuan: public Technology {
public:
	NaMiGuan(float rate) {
		facility = &hua_gong_chang;

		input = 2;
		input_list[0] = &shi_mo_xi;
		input_v[0] = 45;
		new ShiMoXiH(rate*3/2);
		input_list[1] = &tai_kuai;
		input_v[1] = 15;
		new YeTai(rate/2);

		output_list[0] = &na_mi_guan;
		output_v[0] = 30;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "NaMiGuan " << num << endl;
	}
	static float num;
};
float NaMiGuan::num = 0;

class KuanDai: public Technology {
public:
	KuanDai(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &wo_lun;
		input_v[0] = 15;
		new NaMiGuan(rate*2);
		input_list[1] = &ci_tie;
		input_v[1] = 15;
		new JingGe(rate*2);
		input_list[2] = &shi_mo;
		input_v[2] = 7.5;
		new SuLiao(rate);

		output_list[0] = &kuan_dai;
		output_v[0] = 7.5;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "KuanDai " << num << endl;
	}
	static float num;
};
float KuanDai::num = 0;

class DianJiang: public Technology {
public:
	DianJiang(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &xian_quan;
		input_v[0] = 120;
		new XianQuan(rate*4);
		input_list[1] = &leng_jing;
		input_v[1] = 60;
		new LengJing(rate*2);

		output_list[0] = &dian_jiang;
		output_v[0] = 30;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "DianJiang " << num << endl;
	}
	static float num;
};
float DianJiang::num = 0;

class WeiJing: public Technology {
public:
	WeiJing(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &gui_kuai;
		input_v[0] = 60;
		new YeGui(rate*2);
		input_list[1] = &tong_kuai;
		input_v[1] = 30;
		new YeTong(rate);

		output_list[0] = &wei_jing;
		output_v[0] = 30;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "WeiJing " << num << endl;
	}
	static float num;
};
float WeiJing::num = 0;

class ChuLiQi: public Technology {
public:
	ChuLiQi(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &dian_lu_ban;
		input_v[0] = 40;
		new DianLuBan(rate*2);
		input_list[1] = &wei_jing;
		input_v[1] = 40;
		new WeiJing(rate*2);

		output_list[0] = &chu_li_qi;
		output_v[0] = 20;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ChuLiQi " << num << endl;
	}
	static float num;
};
float ChuLiQi::num = 0;

class LiZi: public Technology {
public:
	LiZi(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &wo_lun;
		input_v[0] = 30;
		new WoLun(rate*2);
		input_list[1] = &tong_kuai;
		input_v[1] = 30;
		new YeTong(rate*2);
		input_list[2] = &shi_mo_xi;
		input_v[2] = 30;
		new ShiMoXiH(rate*2);

		output_list[0] = &li_zi;
		output_v[0] = 15;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "LiZi " << num << endl;
	}
	static float num;
};
float LiZi::num = 0;

class TuiJingQi: public Technology {
public:
	TuiJingQi(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &gang_cai;
		input_v[0] = 30;
		new GangCai(rate*2);
		input_list[1] = &tong_kuai;
		input_v[1] = 45;
		new YeTong(rate*3);

		output_list[0] = &tui_jing_qi;
		output_v[0] = 15;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "TuiJingQi " << num << endl;
	}
	static float num;
};
float TuiJingQi::num = 0;

class JiaLiTui: public Technology {
public:
	JiaLiTui(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &tai_he_jing;
		input_v[0] = 50;
		new TaiHeJing(rate*5);
		input_list[1] = &wo_lun;
		input_v[1] = 50;
		new WoLun(rate*5);

		output_list[0] = &jia_li_tui;
		output_v[0] = 10;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "JiaLiTui " << num << endl;
	}
	static float num;
};
float JiaLiTui::num = 0;

class YunShuJi: public Technology {
public:
	YunShuJi(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &tie_kuai;
		input_v[0] = 75;
		new YeTie(rate*5);
		input_list[1] = &chu_li_qi;
		input_v[1] = 30;
		new ChuLiQi(rate*2);
		input_list[2] = &tui_jing_qi;
		input_v[2] = 30;
		new TuiJingQi(rate*2);

		output_list[0] = &yun_shu_ji;
		output_v[0] = 15;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YunShuJi " << num << endl;
	}
	static float num;
};
float YunShuJi::num = 0;

class YunShuChuan: public Technology {
public:
	YunShuChuan(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &tai_he_jing;
		input_v[0] = 100;
		new TaiHeJing(rate*10);
		input_list[1] = &chu_li_qi;
		input_v[1] = 100;
		new ChuLiQi(rate*10);
		input_list[2] = &jia_li_tui;
		input_v[2] = 20;
		new JiaLiTui(rate*2);

		output_list[0] = &yun_shu_chuan;
		output_v[0] = 10;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "YunShuChuan " << num << endl;
	}
	static float num;
};
float YunShuChuan::num = 0;

class QiYi: public Technology {
public:
	QiYi(float rate) {
		facility = &li_zi_dui_zhuang;

		input = 3;
		input_list[0] = &li_zi;
		input_v[0] = 15;
		new LiZi(rate*2);
		input_list[1] = &tie_kuai;
		input_v[1] = 15;
		new YeTie(rate*2);
		input_list[2] = &chuan;
		input_v[2] = 75;
		new Chuan(rate*10);

		output_list[0] = &qi_yi;
		output_v[0] = 7.5;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "QiYi " << num << endl;
	}
	static float num;
};
float QiYi::num = 0;

class TouJing: public Technology {
public:
	TouJing(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &jing_gang_shi;
		input_v[0] = 40;
		new JingGang(rate*4);
		input_list[1] = &qi_yi;
		input_v[1] = 10;
		new QiYi(rate);

		output_list[0] = &tou_jing;
		output_v[0] = 10;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "TouJing " << num << endl;
	}
	static float num;
};
float TouJing::num = 0;

class TaiBoLi: public Technology {
public:
	TaiBoLi(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &bo_li;
		input_v[0] = 24;
		new BoLi(rate);
		input_list[1] = &tai_kuai;
		input_v[1] = 24;
		new YeTai(rate);
		input_list[2] = &shui;
		input_v[2] = 24;
		new CaiKuang(rate, &shui);

		output_list[0] = &tai_bo_li;
		output_v[0] = 24;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "TaiBoLi " << num << endl;
	}
	static float num;
};
float TaiBoLi::num = 0;

class KaXiMier: public Technology {
public:
	KaXiMier(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &tai_jing;
		input_v[0] = 15;
		new TaiJing(rate);
		input_list[1] = &shi_mo_xi;
		input_v[1] = 30;
		new ShiMoXiH(rate*2);
		input_list[2] = &qing;
		input_v[2] = 180;
		new CaiKuang(rate*12, &qing);

		output_list[0] = &ka_xi_mier;
		output_v[0] = 15;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "KaXiMier " << num << endl;
	}
	static float num;
};
float KaXiMier::num = 0;

class WeiMian: public Technology {
public:
	WeiMian(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &ka_xi_mier;
		input_v[0] = 5;
		new KaXiMier(rate);
		input_list[1] = &tai_bo_li;
		input_v[1] = 10;
		new TaiBoLi(rate*2);

		output_list[0] = &wei_mian;
		output_v[0] = 5;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "WeiMian " << num << endl;
	}
	static float num;
};
float WeiMian::num = 0;

class LiangZi: public Technology {
public:
	LiangZi(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &chu_li_qi;
		input_v[0] = 20;
		new ChuLiQi(rate*2);
		input_list[1] = &wei_mian;
		input_v[1] = 20;
		new WeiMian(rate*2);

		output_list[0] = &liang_zi;
		output_v[0] = 10;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "LiangZi " << num << endl;
	}
	static float num;
};
float LiangZi::num = 0;

class LanTang: public Technology {
public:
	LanTang(float rate) {
		facility = &yan_jiu_zhan;

		input = 2;
		input_list[0] = &xian_quan;
		input_v[0] = 20;
		new XianQuan(rate);
		input_list[1] = &dian_lu_ban;
		input_v[1] = 20;
		new DianLuBan(rate);

		output_list[0] = &lan_tang;
		output_v[0] = 20;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "LanTang " << num << endl;
	}
	static float num;
};
float LanTang::num = 0;

class HongTang: public Technology {
public:
	HongTang(float rate) {
		facility = &yan_jiu_zhan;

		input = 2;
		input_list[0] = &shi_mo;
		input_v[0] = 20;
		new ShiMo(rate*2);
		input_list[1] = &qing;
		input_v[1] = 20;
		new LieJie(rate*2); // 精炼工艺，氢只有油的一半产量，所以这里再*2。

		output_list[0] = &hong_tang;
		output_v[0] = 10;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "HongTang " << num << endl;
	}
	static float num;
};
float HongTang::num = 0;

class HuangTang: public Technology {
public:
	HuangTang(float rate) {
		facility = &yan_jiu_zhan;

		input = 2;
		input_list[0] = &jing_gang_shi;
		input_v[0] = 7.5;
		new JingGang(rate);
		input_list[1] = &tai_jing;
		input_v[1] = 7.5;
		new TaiJing(rate);

		output_list[0] = &huang_tang;
		output_v[0] = 7.5;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "HuangTang " << num << endl;
	}
	static float num;
};
float HuangTang::num = 0;

class ZiTang: public Technology {
public:
	ZiTang(float rate) {
		facility = &yan_jiu_zhan;

		input = 2;
		input_list[0] = &chu_li_qi;
		input_v[0] = 12;
		new ChuLiQi(rate*2);
		input_list[1] = &kuan_dai;
		input_v[1] = 6;
		new KuanDai(rate);

		output_list[0] = &zi_tang;
		output_v[0] = 6;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "ZiTang " << num << endl;
	}
	static float num;
};
float ZiTang::num = 0;

class LvTang: public Technology {
public:
	LvTang(float rate) {
		facility = &yan_jiu_zhan;

		input = 2;
		input_list[0] = &tou_jing;
		input_v[0] = 2.5;
		new TouJing(rate/2);
		input_list[1] = &liang_zi;
		input_v[1] = 2.5;
		new LiangZi(rate/2);

		output_list[0] = &lv_tang;
		output_v[0] = 5;

		num += make(rate, 1);
	}
	static void Num(){
		if (num!=0)
		cout << "LvTang " << num << endl;
	}
	static float num;
};
float LvTang::num = 0;

class ChuanSong: public Technology {
public:
	ChuanSong(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &tie_kuai;
		input_v[0] = 120;
		new YeTie(rate/3*2);
		input_list[1] = &chi_lun;
		input_v[1] = 60;
		new ChiLun(rate/3);

		output_list[0] = &chuan_song;
		output_v[0] = 180;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ChuanSong " << num << endl;
	}
	static float num;
};
float ChuanSong::num = 0;

class ChuanSongH: public Technology {
public:
	ChuanSongH(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &chuan_song;
		input_v[0] = 180;
		new ChuanSong(rate);
		input_list[1] = &wo_lun;
		input_v[1] = 60;
		new WoLun(rate/3);

		output_list[0] = &chuan_song_h;
		output_v[0] = 180;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ChuanSongH " << num << endl;
	}
	static float num;
};
float ChuanSongH::num = 0;

class FengLian: public Technology {
public:
	FengLian(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &tie_kuai;
		input_v[0] = 60;
		new YeTie(rate);
		input_list[1] = &dian_lu_ban;
		input_v[1] = 60;
		new DianLuBan(rate);

		output_list[0] = &feng_lian;
		output_v[0] = 60;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "FengLian " << num << endl;
	}
	static float num;
};
float FengLian::num = 0;

class FengLianH: public Technology {
public:
	FengLianH(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &feng_lian;
		input_v[0] = 120;
		new FengLian(rate);
		input_list[1] = &dian_dong_ji;
		input_v[1] = 60;
		new DianDongJi(rate/2);

		output_list[0] = &feng_lian_h;
		output_v[0] = 120;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "FengLianH " << num << endl;
	}
	static float num;
};
float FengLianH::num = 0;

class FengLianS: public Technology {
public:
	FengLianS(float rate) {
		facility = &zhi_zuo_tai;

		input = 2;
		input_list[0] = &feng_lian_h;
		input_v[0] = 120;
		new FengLianH(rate);
		input_list[1] = &wo_lun;
		input_v[1] = 60;
		new WoLun(rate/2);

		output_list[0] = &feng_lian_s;
		output_v[0] = 120;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "FengLianS " << num << endl;
	}
	static float num;
};
float FengLianS::num = 0;

class ZhiZuo: public Technology {
public:
	ZhiZuo(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &tie_kuai;
		input_v[0] = 120;
		new YeTie(rate*2);
		input_list[1] = &chi_lun;
		input_v[1] = 240;
		new ChiLun(rate*4);
		input_list[2] = &dian_lu_ban;
		input_v[2] = 120;
		new DianLuBan(rate*2);

		output_list[0] = &zhi_zuo;
		output_v[0] = 120;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "ZhiZuo " << num << endl;
	}
	static float num;
};
float ZhiZuo::num = 0;

class DianHu: public Technology {
public:
	DianHu(float rate) {
		facility = &zhi_zuo_tai;

		input = 4;
		input_list[0] = &tie_kuai;
		input_v[0] = 80;
		new YeTie(rate*4);
		input_list[1] = &shi_cai;
		input_v[1] = 40;
		new ShiCai(rate*2);
		input_list[2] = &dian_lu_ban;
		input_v[2] = 80;
		new DianLuBan(rate*4);
		input_list[3] = &xian_quan;
		input_v[3] = 40;
		new XianQuan(rate*2);

		output_list[0] = &dian_hu_rong;
		output_v[0] = 20;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "DianHu " << num << endl;
	}
	static float num;
};
float DianHu::num = 0;

class XingXingZhan: public Technology {
public:
	XingXingZhan(float rate) {
		facility = &zhi_zuo_tai;

		input = 4;
		input_list[0] = &gang_cai;
		input_v[0] = 120;
		new GangCai(rate*40);
		input_list[1] = &tai_kuai;
		input_v[1] = 120;
		new YeTai(rate*40);
		input_list[2] = &chu_li_qi;
		input_v[2] = 120;
		new ChuLiQi(rate*40);
		input_list[3] = &li_zi;
		input_v[3] = 60;
		new LiZi(rate*20);

		output_list[0] = &xing_xing_zhan;
		output_v[0] = 3;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "XingXingZhan " << num << endl;
	}
	static float num;
};
float XingXingZhan::num = 0;

class XingJiZhan: public Technology {
public:
	XingJiZhan(float rate) {
		facility = &zhi_zuo_tai;

		input = 3;
		input_list[0] = &xing_xing_zhan;
		input_v[0] = 120;
		new XingXingZhan(rate);
		input_list[1] = &tai_he_jing;
		input_v[1] = 120;
		new TaiHeJing(rate*40);
		input_list[2] = &li_zi;
		input_v[2] = 120;
		new LiZi(rate*20);

		output_list[0] = &xing_ji_zhan;
		output_v[0] = 2;

		num += make(rate, make_v);
	}
	static void Num(){
		if (num!=0)
		cout << "XingJiZhan " << num << endl;
	}
	static float num;
};
float XingJiZhan::num = 0;



int main() {
	Technology* list;
	list = new KaXiMier(60);
	// list = new ChuLiQi(60);
	// list = new WoLun(120);
	// cout << "keranbing " << ke_ran_bing << endl;

	Sum();
    YeTie::Num();
    YeTong::Num();
    YeGui::Num();
    YeTai::Num();
    JingGe::Num();
    BoLi::Num();
    ShiCai::Num();
    ShiMo::Num();
    JingGang::Num();
    JingLian::Num();
    ShiMoXiH::Num();
    LieJie::Num();
    CiTie::Num();
    XianQuan::Num();
    ChiLun::Num();
    GangCai::Num();
    DianDongJi::Num();
    LengJing::Num();
    ChongZheng::Num();
    SuLiao::Num();
    YouJi::Num();
    TaiJing::Num();
    WoLun::Num();
    CiChangHuan::Num();
    DianLuBan::Num();
    LiuSuan::Num();
    TaiHeJing::Num();
    ShiMoXi::Num();
    NaMiGuan::Num();
    KuanDai::Num();
    DianJiang::Num();
    WeiJing::Num();
    ChuLiQi::Num();
    LiZi::Num();
    TuiJingQi::Num();
    JiaLiTui::Num();
    YunShuJi::Num();
    YunShuChuan::Num();
    QiYi::Num();
    TouJing::Num();
    TaiBoLi::Num();
    KaXiMier::Num();
    WeiMian::Num();
    LiangZi::Num();
    LanTang::Num();
    HongTang::Num();
    HuangTang::Num();
    ZiTang::Num();
    LvTang::Num();
    ChuanSong::Num();
    ChuanSongH::Num();
    FengLian::Num();
    FengLianH::Num();
    FengLianS::Num();
    ZhiZuo::Num();
    DianHu::Num();
    XingXingZhan::Num();
    XingJiZhan::Num();

	return 0;
}


/*

熔炉 70; 制作台 63; 精炼厂 13.3333; 化工厂 16; 研究站 12; 
YeTie 15
YeTong 9
YeGui 8
YeTai 10
BoLi 4
ShiMo 8
JingGang 4
JingLian 6.66667
ShiMoXiH 4
CiTie 12
XianQuan 4
ChiLun 4
DianDongJi 8
ChongZheng 6.66667
SuLiao 6
YouJi 6
TaiJing 4
WoLun 4
DianLuBan 1
WeiJing 4
ChuLiQi 3
LiZi 4
QiYi 4
TouJing 3
TaiBoLi 5
KaXiMier 4
WeiMian 12
LiangZi 3
LvTang 12

*/