
#ifdef E71Csw41
#define	DO_DIRECT_SELECT	0xA0B214E6+1
#define	DO_START_SELECT		0xA0B2113C+1
#define	DO_EBACK		0xA0B20FF8+1
#define	DO_NOTHING		0xA0B211FA+1
#define	WGET_KBS_KSTATE		0xA0A49F4E+1 //1:ON, 0:OFF
#define	UNK_RAM_adr		0xA8EBCA10 //�������ж��Ƿ��ڱ༭״̬
#define	WSET_KBS_KSTATE		0xA0A49CB0+1
#define	DO_SELECT_EBACK		0xA0B21678+1
#define	KDB_KPOP_FUNC1_RAM	0xA8F2BED0
#define	KDB_KPOP_EBACK		0xA06EF290+1
#define	KDB_KPOP_EBNE_adr	0xA06EF328+1

/* ���²��ֺ�ƴ�����뷨�޸� v1.x �е�һ�� */
#define GBS_SendMessage_adr	0xA0091EAB
#define	JAVA_EDIT_KOP		0xA8EB0A30
#define	USE_RAM			0xA8D805C0   //�հ�RAM,4�ֽ�,��ƴ�����뷨�޸�v1.x��һ��
#define	GET_INPUT_STATE		0xA06EF026+1 //��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA06EDDC6+1 //0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA06EF1DC+1 //0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA06EF1EC+1 //0����ת�򳣹�����

#endif

#ifdef ELC1sw41
#define	DO_DIRECT_SELECT	0xA0B28D6E+1
#define	DO_START_SELECT		0xA0B289C4+1
#define	DO_EBACK		0xA0B28880+1
#define	DO_NOTHING		0xA0B27BA2+1
#define	WGET_KBS_KSTATE		0xA0A50736+1 //1:ON, 0:OFF
#define	UNK_RAM_adr		0xA8EBC98C //�������ж��Ƿ��ڱ༭״̬
#define	WSET_KBS_KSTATE		0xA0A50498+1
#define	DO_SELECT_EBACK		0xA0B28F00+1
#define	KDB_KPOP_FUNC1_RAM	0xA8F2B658
#define	KDB_KPOP_EBACK		0xA06F6BBC+1
#define	KDB_KPOP_EBNE_adr	0xA06F6C54+1

/* ���²��ֺ�ƴ�����뷨�޸� v1.x �е�һ�� */
#define GBS_SendMessage_adr	0xA0091EAB
#define	JAVA_EDIT_KOP		0xA8EB0730   //��JAVA��,�����ַ����
#define	USE_RAM			0xA8D805C0   //4�ֽ�,���ڴ洢JAVA�����뷨ѡ��˵�״̬
#define	GET_INPUT_STATE		0xA06F6952+1 //��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA06F56F2+1 //0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA06F6B08+1 //0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA06F6B18+1 //0����ת�򳣹�����

#endif

#ifdef C81Csw50
#define	DO_DIRECT_SELECT	0xA0AD852A+1
#define	DO_START_SELECT		0xA0AD8180+1
#define	DO_EBACK		0xA0AD803C+1
#define	DO_NOTHING		0xA0AD823E+1
#define	WGET_KBS_KSTATE		0xA0A32D56+1 //1:ON, 0:OFF
#define	UNK_RAM_adr		0xA8EBCA10 //�������ж��Ƿ��ڱ༭״̬ //δ��.ԭʼE71CV41
#define	WSET_KBS_KSTATE		0xA0A32AB8+1
#define	DO_SELECT_EBACK		0xA0AD86BC+1
#define	KDB_KPOP_FUNC1_RAM	0xA8EE2BF0  // //
#define	KDB_KPOP_EBACK		0xA05CBC9C+1
#define	KDB_KPOP_EBNE_adr	0xA05CBD34+1

/* ���²��ֺ�ƴ�����뷨�޸� v1.x �е�һ�� */
#define GBS_SendMessage_adr	0xA0092A94  // //
#define	JAVA_EDIT_KOP		0xA8E636A4  //*(CB040000??????A000000000CC090000FFFF000036E400000021201C-10)+4
#define	USE_RAM			0xA8ED0720   //�հ�RAM,4�ֽ�,��ƴ�����뷨�޸�v1.x��һ�� //δ��.ԭʼE71CV41
#define	GET_INPUT_STATE		0xA05CBA32+1 //��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA05CA7D2+1 //0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA05CBBE8+1 //0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA05CBBF8+1 //0����ת�򳣹�����

#endif

#ifdef	S7Csw47
#define	DO_DIRECT_SELECT	0xA0AD03AF
//#define	DO_START_SELECT		0xA0AD0005
#define	DO_EBACK		0xA0ACFEC1
#define	DO_NOTHING		0xA0AD00C3
//#define	WGET_KBS_KSTATE		0xA0A30E2F
//#define	UNK_RAM_adr		0xA8DF0908
//#define	WSET_KBS_KSTATE		0xA0A30B91
//#define	DO_SELECT_EBACK		0xA0ACFEC1

#define	KDB_KPOP_FUNC1_RAM	0xA8E63F88

#define GBS_SendMessage_adr	0xA0092A94

#define	JAVA_EDIT_KOP		0xA8DE4900	//��JAVA��,�����ַ����
#define	USE_RAM			0xA8A7F100	//4�ֽ�,���ڴ洢JAVA�����뷨ѡ��˵�״̬
#define	GET_INPUT_STATE		0xA05B41BF	//��ȡ����״̬,1Ϊ�ȴ�����,0Ϊƴ��ѡ���ѡ��״̬
#define	KEY0_FUNC1		0xA05B2F5F	//0����תλ�õ�һ������,����ʱҪ��ִ���������
#define	KEY0_BACK		0xA05B4375	//0����ת���ص�ַ
#define	KEY0_GOTO_IME		0xA05B4385	//0����ת�򳣹�����
#endif
