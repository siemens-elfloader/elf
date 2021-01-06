/******************************************
 *
 * BM字符串匹配算法介绍
 *
 * BM算法的基本思想是从右向左进行比较。
 * 开始时仍是P(Pattern)的最左边与S(String)的最左边对齐，但首先进行Pm与Tm的比较。
 * 当某趟比较中出现不匹配时，BM算法采用两条启发性规则计算模式串右移的距离，即坏字符规则和好后缀规则。
 * 1) 坏字符规则（Bad Character）
 *    P中的某个字符与T中的某个字符不相同时使用坏字符规则右移模式串P，
 *    P右移的距离可以通过delta1函数计算出来。delta1函数的定义如下:
 *    delta1(x) = - m; x<>P[j] (1 <= j <= m)，即x在P中未出现
 *                |
 *                - m - max{k|P[k] = x, 1 <= k <= m}; 其它情况
 *
 * 2) 好后缀规则(Good Suffix)
 *    该规则将KMP算法和BM算法的思想结合起来，在不丢失真解的前提下确定一个新的移动距离delta2，
 *    该函数与样本P有关。
 *    P中的某一子串P[j-s+1..m-s]与已比较部分P[j+1..m]相同，可让P右移s位。
 *    delta2的定义如下：
 *    delta2（j）= {s|P[j+1..m]=P[j-s+1..m-s])&&(P[j]≠P[j-s])(j>s)}
 *
 * 在匹配过程中，取delta1和delta2中的大者。
 * BM算法的最坏时间复杂度为O(m*n)，
 * 但实际比较次数只有文本串长度的20%～30%。
 *
 ******************************************/

/******************************************
 *
 * BM字符串匹配算法
 *
 * 从snort2.2的mstring.c中整理而来
 *
 ******************************************/
#include <stdio.h>
#include <string.h>
/******************************************
 *
 * 生成skip数组，即delta1数组
 *
 ******************************************/
int *make_skip(char *ptrn, int plen) {
	int *skip = (int *)malloc(256 * sizeof(int));
	int *sptr = skip + 256;

	if (!skip) ShowMSG(1, (int)"malloc failed!");

	while (sptr-- != skip)
		*sptr = plen + 1;

	while (plen != 0)
		skip[(unsigned char)*ptrn++] = plen--;

	return skip;
}

/******************************************
 *
 * 生成shift数组，即delta2数组
 *
 ******************************************/
int *make_shift(char *ptrn, int plen) {
	int *shift = (int *)malloc(plen * sizeof(int));
	int *sptr = shift + plen - 1;
	char *pptr = ptrn + plen - 1;
	char c;

	if (!shift) ShowMSG(1, (int)"malloc failed!");

	c = ptrn[plen - 1];
	*sptr = 1;

	while (sptr -- != shift) {
		char *p1 = ptrn + plen - 2, *p2, *p3;

		do {
			while (p1 >= ptrn && *p1-- != c)
				;

			p2 = ptrn + plen - 2;
			p3 = p1;

			while (p3 >= ptrn && *p3-- == *p2-- && p2 >=pptr)
				;
		} while (p3 >= ptrn && p2 >= pptr);

		*sptr = shift + plen - sptr + p2 - p3;

		pptr--;
	}

	return shift;
}
/******************************************
 *
 * 搜索函数
 *
 ******************************************/
int mSearch(char *buf, int blen, char *ptrn, int plen, int *skip, int *shift) {
	int b_idx = plen;

	if (plen == 0)
		return 1;

	while (b_idx <= blen) {
		int p_idx = plen, skip_stride, shift_stride;

		while (buf[--b_idx] == ptrn[--p_idx]) {
			if (b_idx < 0)
				return 0;

			if (p_idx == 0) {
				return 1;
			}
		}

		skip_stride = skip[(unsigned char)buf[b_idx]];
		shift_stride = shift[p_idx];

		b_idx += (skip_stride > shift_stride) ? skip_stride : shift_stride;
	}

	return 0;
}
int main() {
	char str[100] = "faecabcxxdefeabcxxxabcdwaw";
	char pattern[10] = "abcxxxabc";
	int *skip, *shift, i;

	skip = make_skip(pattern, strlen(pattern));
	shift = make_shift(pattern, strlen(pattern));

	if (!mSearch(str, strlen(str), pattern, strlen(pattern), skip, shift))
		printf("The string \"%s\" doesn't contain string \"%s\"\n", str,
				pattern);
	else
		printf("The string \"%s\" does contain string \"%s\"\n", str, pattern);

	return 0;
}