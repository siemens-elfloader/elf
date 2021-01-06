#ifndef _MACROS_H_
#define _MACROS_H_

// Макросы ;)

#define _safe_delete(x) { if (x) delete(x); (x) = NULL; }
#define _tmr_second(x)  (1300 * x / 6)

#endif
