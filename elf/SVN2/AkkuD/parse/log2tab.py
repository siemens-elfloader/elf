# -*- coding: cp1251 -*-
import re
import os
from datetime import datetime,timedelta

print "log2tab working.....\n"
f=open('akkud_log.txt','r')
l=f.readlines()
f.close()

pat=re.compile('^(\d+):(\d+)\s+(\d+)/(\d+)/(\d+)\s+CAP=(\d+)')

g=open('akku_day.txt','w')
gh=open('akku_hour.txt','w')
start=None
for q in l:
	#print "{%s}\n"%(q)
	da=pat.match(q)
	if da!=None:
		(h,m,dd,mm,yy,capacity)=da.groups()
		curr=datetime(int(yy),int(mm),int(dd),int(h),int(m))
		if start==None:
			start=curr
		delta=curr-start
		dayz=1.0*delta.seconds/(60*60*24)+delta.days
		hourz=1.0*delta.seconds/(60*60)+delta.days*24.0
		g.write("%1.4f\t%3d\n"%(dayz,int(capacity)))
		gh.write("%3.4f\t%3d\n"%(hourz,int(capacity)))
	#else:
	#	g.write(";wrong format!\n")
	#	gh.write(";wrong format!\n")
g.close()
gh.close()

f=open('_tmp.plt','w')
f.write('plot "akku_day.txt" with lines'+"\n"+'pause -1'+"\n")
f.close()
os.system("C:\\gnuplot\\bin\\wgnuplot.exe _tmp.plt");