#include "CommonAPI.h"

///********************************链表*****************************************/

#define Box struct box
#define NEW (Box*)malloc(sizeof(Box))
extern Box
{
	char *name;
	short value;
	Box *next;
} *obList;

//创建
void creatList()
{
	//创建链表
	obList = NEW;
	obList->name = "listHead";
	obList->value = 0;
	obList->next = NEW;
	obList->next->name = NULL;
}

//挂箱（参数szSrcName为NULL表示不创建实例）
void addBox(const char *szSrcName, const char *szMyName, short value)
{
	//如果提供了模板
	if (szSrcName) dCloneSprite(szSrcName, szMyName);

	Box *p, *q;
	p = obList;
	while(p->name)
	{
		q = p->next;
		p = q;
	}
	p->name = new char[1 + strlen(szMyName)];
	strcpy(p->name, szMyName);
	p->value = value;
	p->next = NEW;
	p->next->name = NULL;
}

//取箱
short *pickBox(const char *name)
{
	if (!strcmp(obList->name, name)) return &obList->value;
	Box *p, *q;
	p = obList;
	q = p->next;
	while(q->name&&strcmp(q->name, name))
	{
		p = q;
		q = p->next;
	}
	if (!q->name) return NULL;
	return &q->value;
}

//弃箱
void cutBox(const char *name)
{
	if (!strcmp(obList->name, name)) free(obList);
	Box *p, *q;
	p = obList;
	q = p->next;
	while(q->name&&strcmp(q->name, name))
	{
		p = q;
		q = p->next;
	}
	//查无
	if (!q->name) return;
	p->next = q->next;
	dDeleteSprite( name );
	free(q);
}

//销毁
void destroyList()
{
	Box *p = obList;
	Box *q = p->next;
	while (p->name)
	{
		dDeleteSprite( p->name );
		free(p);
		p = q;
		q = p->next;
	}
	free(p);
}
