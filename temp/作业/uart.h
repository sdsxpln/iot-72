#ifndef __COM_H__
#define __COM_H__
#define uchar unsigned char
#define uint unsigned int
#define XTAL 11059200    // CUP ����Ƶ��
#define baudrate 9600    // ͨ�Ų�����

void sendmsg(uchar ps)
{
SBUF = ps;            // Ҫ���͵��ַ����뻺����
while(TI == 0);    // һֱ�ȵȣ�ֱ������������Ϊֹ
TI = 0;
}
uchar rcvmsg(void)   //���ô˺���ǰ��Ҫ�ȵ���RI,�鿴�Ƿ��յ����ݣ�ȷ�����յ��Ļ����ٵ��ô˺���
{

RI=0;                       //Ҫ�Ƚ�RI=0�ٷ��أ����򣬷��غ�RI=0���Ͳ�ִ���ˡ�
return SBUF;
}
void initcom()
{
TMOD = 0x20;   // ��ʱ��1������8λ�Զ�����ģʽ, ���ڲ���������
TH1=(unsigned char)(256 - (XTAL / (32L * 12L * baudrate)));
TL1=(unsigned char)(256 - (XTAL / (32L * 12L * baudrate)));                // ��ʱ��1����ֵ
SM0 = 0; //���ڹ�����ʽ����
SM1 = 1; //���ڹ�����ʽ���� //��������ͬ�����˴��ڹ�����ʽΪ 0;
REN = 1; //���ڽ�������
PCON = 0x00;
TR1 = 1; //�����ڽ���
ES = 0;   //�رմ����ж�
}
#endif