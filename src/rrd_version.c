/*****************************************************************************
 * RRDtool 1.3rc6  Copyright by Tobi Oetiker, 1997-2008
 *****************************************************************************
 * rrd_version Return
 *****************************************************************************
 * Initial version by Burton Strauss, ntopSupport.com - 5/2005
 *****************************************************************************/

#include "rrd_tool.h"

double rrd_version(
    void)
{
    return NUMVERS;
}

char     *rrd_strversion(
    void)
{
    return PACKAGE_VERSION;
}
