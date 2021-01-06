#ifndef _EDIT_SETTINGS_H_
  #define _EDIT_SETTINGS_H_

typedef enum {
  DEGREES=0,
  RADIANS,
  GRADS
}DRG;
  
typedef struct {
  double x;
  double y;
  char fmt[16];
  char drg;
  char auto_recalc;
} CALC_SETTINGS;

void ReadCalcSettings(void);
void WriteCalcSettings(void);
int CreateSettingsEdit(void);

#endif
