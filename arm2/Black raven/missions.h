int miss1=0,miss2=0,miss3=7;
//TextBox("�������� ����","�� ������ �������� ��������"," 1. ����� 1  �������",miss1," 2. ��������� ����",miss2,"",miss3); - ������ ���� ������
void mission1()
{
  
  sprintf(zag,"�������� ����");
  sprintf(all,"�� ������ �������� ��������");
  sprintf(cel1," 1. ����� 1  �������");
  sprintf(cel2," 2. ��������� ����");
  sprintf(cel3,"");//�����
  miss1=0;
  miss2=0;
  miss3=-1;//���� �� 1 � �� 0 �� �����
  if(strcmp(GetTerrainNames[npic (cursorX,cursorY)], "����")==0)
  {
    miss2=1;
  }
}
