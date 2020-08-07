#include <iostream>
#include <ctime>

#define MR_PAIRING_BLS    // AES-256 security    ����BLS����
#define AES_SECURITY 256
#include "include/pairing_3.h"
int test_bls()
{   
	PFC pfc(AES_SECURITY);  // ��ʼ��˫���Զ�����
	G1 S,R;
;	G2 Q,V;
	int lsb;
	Big s,X;
	time_t seed;
	const char* message = "Be there or be square!";  //��ǩ����Ϣm
	time(&seed);
    irand((long)seed);
	
	
// ����G2����
	pfc.random(Q);
	pfc.random(s);    // ˽Կ
	V=pfc.mult(Q,s);  // ��Կ V

// �û�A����ǩ��
	pfc.hash_and_map(R,(char*)message);//����ǩ����Ϣ���й�ϣ�������е�R
	S=pfc.mult(R,s);       //R * s������ǩ��S

	lsb=S.g.get(X);   // lsb��X����ǩ��
	cout << "The message is signed by A!" << endl;

	cout << "Signature= " << lsb << "  " << X << endl;//���ǩ����Ϣ

// �û�B����ǩ����֤   ���Ȼָ�S
	if (!S.g.set(X,1-lsb))
	{
		cout << "Signature is invalid" << endl;
		exit(0);
	}
	pfc.hash_and_map(R,(char *)message);  //����Ϣ�������߹�ϣ����R

// Observe that Q is a constant
// Interesting that this optimization doesn't work for the Tate pairing, only the Ate
	//���Ƚ������Ե�׼������
	pfc.precomp_for_pairing(Q);

	G1 *g1[2];
	G2 *g2[2];
	g1[0]=&S; g1[1]=&R;
	g2[0]=&Q; g2[1]=&V;
	
	//ֻ����֤��Կ����Ϣ�Ĺ�ϣֵ�������������㣩���������ɵ��ǩ�����������������㣩�Ƿ�ӳ�䵽ͬһ����������Ǿ�˵������һ����Ч�� BLS ǩ��
	if (pfc.multi_pairing(2,g2,g1)==1)
		cout << "Signature verifies,the message is from A!" << endl;
	else
		cout << "Signature is bad" << endl;
	
    return 1;//����1��ʾ���гɹ�
}
