/*****************************************************************************
 * RRDtool 1.2.26  Copyright by Tobi Oetiker, 1997-2007
 *****************************************************************************
 * rrd_format.c  RRD Database Format helper functions
 *****************************************************************************
 * $Id: rrd_format.c 1235 2007-11-20 00:15:07Z oetiker $
 * $Log$
 * Revision 1.5  2004/05/18 18:53:03  oetiker
 * big spell checking patch -- slif@bellsouth.net
 *
 * Revision 1.4  2003/02/13 07:05:27  oetiker
 * Find attached the patch I promised to send to you. Please note that there
 * are three new source files (src/rrd_is_thread_safe.h, src/rrd_thread_safe.c
 * and src/rrd_not_thread_safe.c) and the introduction of librrd_th. This
 * library is identical to librrd, but it contains support code for per-thread
 * global variables currently used for error information only. This is similar
 * to how errno per-thread variables are implemented.  librrd_th must be linked
 * alongside of libpthred
 *
 * There is also a new file "THREADS", holding some documentation.
 *
 * -- Peter Stamfest <peter@stamfest.at>
 *
 * Revision 1.3  2002/02/01 20:34:49  oetiker
 * fixed version number and date/time
 *
 * Revision 1.2  2001/03/10 23:54:39  oetiker
 * Support for COMPUTE data sources (CDEF data sources). Removes the RPN
 * parser and calculator from rrd_graph and puts then in a new file,
 * rrd_rpncalc.c. Changes to core files rrd_create and rrd_update. Some
 * clean-up of aberrant behavior stuff, including a bug fix.
 * Documentation update (rrdcreate.pod, rrdupdate.pod). Change xml format.
 * -- Jake Brutlag <jakeb@corp.webtv.net>
 *
 * Revision 1.1.1.1  2001/02/25 22:25:05  oetiker
 * checkin
 *
 * Revision 1.3  1998/03/08 12:35:11  oetiker
 * checkpointing things because the current setup seems to work
 * according to the things said in the manpages
 *
 * Revision 1.2  1998/02/26 22:58:22  oetiker
 * fixed define
 *
 * Revision 1.1  1998/02/21 16:14:41  oetiker
 * Initial revision
 *
 *
 *****************************************************************************/
#include "rrd_tool.h"

#define converter(VV,VVV) \
   if (strcmp(#VV, string) == 0) return VVV;

/* conversion functions to allow symbolic entry of enumerations */
enum dst_en dst_conv(char *string)
{
    converter(COUNTER,DST_COUNTER)
    converter(ABSOLUTE,DST_ABSOLUTE)
    converter(GAUGE,DST_GAUGE)
    converter(DERIVE,DST_DERIVE)
    converter(COMPUTE,DST_CDEF)
    rrd_set_error("unknown data acquisition function '%s'",string);
    return(-1);
}


enum cf_en cf_conv(const char *string)
{

    converter(AVERAGE,CF_AVERAGE)
    converter(MIN,CF_MINIMUM)
    converter(MAX,CF_MAXIMUM)
    converter(LAST,CF_LAST)
    converter(HWPREDICT,CF_HWPREDICT)
    converter(DEVPREDICT,CF_DEVPREDICT)
    converter(SEASONAL,CF_SEASONAL)
    converter(DEVSEASONAL,CF_DEVSEASONAL)
    converter(FAILURES,CF_FAILURES)
    rrd_set_error("unknown consolidation function '%s'",string);
    return(-1);
}

#undef converter	

long
ds_match(rrd_t *rrd,char *ds_nam){
    unsigned long i;
    for(i=0;i<rrd->stat_head->ds_cnt;i++)
	if ((strcmp(ds_nam,rrd->ds_def[i].ds_nam))==0)
	    return i;
    rrd_set_error("unknown data source name '%s'",ds_nam);
    return -1;
}
