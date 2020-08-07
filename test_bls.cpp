#include <iostream>
#include <ctime>

#define MR_PAIRING_BLS    // AES-256 security    定义BLS曲线
#define AES_SECURITY 256
#include "include/pairing_3.h"
int test_bls()
{   
	PFC pfc(AES_SECURITY);  // 初始化双线性对曲线
	G1 S,R;
;	G2 Q,V;
	int lsb;
	Big s,X;
	time_t seed;
	const char* message = "Be there or be square!";  //待签名消息m
	time(&seed);
    irand((long)seed);
	
	
// 创建G2常量
	pfc.random(Q);
	pfc.random(s);    // 私钥
	V=pfc.mult(Q,s);  // 公钥 V

// 用户A进行签名
	pfc.hash_and_map(R,(char*)message);//将待签名消息进行哈希至曲线中点R
	S=pfc.mult(R,s);       //R * s即生成签名S

	lsb=S.g.get(X);   // lsb和X构成签名
	cout << "The message is signed by A!" << endl;

	cout << "Signature= " << lsb << "  " << X << endl;//输出签名信息

// 用户B进行签名验证   首先恢复S
	if (!S.g.set(X,1-lsb))
	{
		cout << "Signature is invalid" << endl;
		exit(0);
	}
	pfc.hash_and_map(R,(char *)message);  //将消息进行曲线哈希至点R

// Observe that Q is a constant
// Interesting that this optimization doesn't work for the Tate pairing, only the Ate
	//首先进行线性的准备工作
	pfc.precomp_for_pairing(Q);

	G1 *g1[2];
	G2 *g2[2];
	g1[0]=&S; g1[1]=&R;
	g2[0]=&Q; g2[1]=&V;
	
	//只需验证公钥和消息的哈希值（曲线上两个点）与曲线生成点和签名（曲线上另两个点）是否映射到同一个数，如果是就说明这是一个有效的 BLS 签名
	if (pfc.multi_pairing(2,g2,g1)==1)
		cout << "Signature verifies,the message is from A!" << endl;
	else
		cout << "Signature is bad" << endl;
	
    return 1;//返回1表示运行成功
}
