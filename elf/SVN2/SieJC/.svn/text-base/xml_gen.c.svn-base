#include "platform.h"
#ifdef SIEMENS
  #include "../inc/swilib.h"
#else
  #include <string.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <stdio.h>

  #include "siemens_compat.h"
#endif

#include "string_util.h"
#include "xml_common.h"
#include "xml_gen.h"

XMLNode *
XML_CreateNode(char *name, char *value)
{
	XMLNode *node;
	
	if (name==NULL)
		return NULL;
	
	node = malloc(sizeof(XMLNode));
	bzero(node, sizeof(XMLNode));
	node->name = malloc(strlen(name) + 1);
	strcpy(node->name, name);
	if (value) {
		node->value = malloc(strlen(value) + 1);
		strcpy(node->value, value);
	}

	return (node);
}

int
XML_Set_Attr_Value(XMLNode *node, char *attr_name, char *attr_value)
{
	XMLAttr *p, **tail;
	u_int32_t len;

	if (!node || !attr_name)
		return (-1);
	tail = NULL;
	if (node->attr) {
		p = node->attr;
		while (p) {
			if (!strcmp(p->name, attr_name)) {
				len = strlen(attr_value);
				p->param = realloc(p->param, len + 1);
				strcpy(p->param, attr_value);
				break;
			}
			p = p->next;
		}

		if (!p) {/* No attr with such name */
			p = node->attr;
			while (p->next) {
				p = p->next;
			}
			tail = (XMLAttr**)&(p->next);
			
		}
	} else tail = &(node->attr);

	if (tail) {
		p = malloc(sizeof(XMLAttr));
		bzero(p, sizeof(XMLAttr));
		p->name = malloc(strlen(attr_name)+1);
		p->param= malloc(strlen(attr_value)+1);
		strcpy(p->name, attr_name);
		strcpy(p->param, attr_value);
		*tail = p;
	}
	return (0);
}

inline char *
chk_realloc_buf(char *buf, u_int32_t * buf_len, u_int32_t remain, u_int32_t growsize)
{
	u_int32_t l_buf_len;
	l_buf_len = *buf_len;

	if (growsize > remain - 100) {
		buf = realloc(buf, l_buf_len+=growsize+1024);
		*buf_len = l_buf_len;
	}

	return (buf);
} 

char *
XML_Get_Node_As_Text(XMLNode *node)
{
	XMLAttr *attr;
	char *buf, *sub_buf, *conv_param;
	u_int32_t buf_len, occ_len, l;
	XMLNode *sn;

#define CHK(b, l) b = chk_realloc_buf(b, &buf_len, buf_len - occ_len, l);

	if (!node || !node->name) /* Check sanity */
		return (NULL);

	occ_len = 0;
	buf = malloc(buf_len = 1024);
	bzero(buf, buf_len);
	buf[occ_len++]='<';
	strncpy(buf + occ_len, node->name, buf_len - occ_len);
	l = strlen(node->name);
	occ_len+=l;
	
	/* Copy attributes */
	attr = node->attr;
	while (attr && attr->name && attr->param) {
		buf[occ_len++]=' ';
		l = strlen(attr->name);
		CHK(buf, l);
		strncpy(buf + occ_len, attr->name, buf_len - occ_len);
		occ_len+=l;
		buf[occ_len++]='=';
		buf[occ_len++]='"';
		conv_param = Mask_Special_Syms(attr->param);
		l = strlen(conv_param);
		CHK(buf, l);
		strncpy(buf + occ_len, conv_param, buf_len - occ_len);
		mfree(conv_param);
		occ_len+=l;
		buf[occ_len++]='"';
		attr = attr->next;
	}
	
	if (node->subnode) {
		CHK(buf, 1);
		buf[occ_len++] = '>';
		
		sn = node->subnode;
		while (sn) {
			sub_buf = XML_Get_Node_As_Text(sn);
			if (sub_buf) {
				l = strlen(sub_buf);
				CHK(buf, l);
				strncpy(buf + occ_len, sub_buf, buf_len - occ_len);
				occ_len+=l;
				mfree(sub_buf);
			}
			sn = sn->next;
		}
		/* Closing tag */
		l = strlen(node->name);
		CHK(buf, l+3);
		buf[occ_len++] = '<';
		buf[occ_len++] = '/';
		strncpy(buf + occ_len, node->name, buf_len - occ_len);
		occ_len+=l;
		buf[occ_len++] = '>';
	} else {
		if (node->value) {
			CHK(buf, 1);
			buf[occ_len++] = '>';
			conv_param = Mask_Special_Syms(node->value);
			l = strlen(conv_param);
			CHK(buf, l);
//			occ_len++;
			strncpy(buf + occ_len, conv_param, buf_len - occ_len);
			occ_len+=l;
			mfree(conv_param);
                        /* Closing tag */
			l = strlen(node->name);
			CHK(buf, l+3);
			buf[occ_len++] = '<';
			buf[occ_len++] = '/';
			strncpy(buf + occ_len, node->name, buf_len - occ_len);
			occ_len+=l;			
			buf[occ_len++] = '>';
		} else {
			CHK(buf, 2);
			buf[occ_len++] = '/';
			buf[occ_len] = '>';
		}
	}
//	printf("XML node name %s has dump\n%s\n", node->name, buf);
	return (buf);
}
/*
 * Local Variables: *
 * c-file-style: "bsd" *
 * End: *
 */
