
typedef struct {
  void *address;
  char  old_data;
  char  new_data;
}PATCH_ITEM;

#define PP_RMODE  0
#define PP_MMODE  1
#define PP_RESET  2

#define APPLY_VP  0
#define UNDO_VP   1
#define UNDO_RP   2



//������������� ����� ��� PrePatch
void SetPrePatchMode(int m);
//������� ������� ����� � �������� ������ ����� 
int PrePatch(void *addr, char old_data, char new_data);
//������ ������� � ������
int PatchFunction(int type);

