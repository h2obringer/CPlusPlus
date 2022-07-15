/* passiveTCP.c - passiveTCP */

#include "libnet.h"

/*------------------------------------------------------------------------
 * passiveTCP - create a passive socket for use in a TCP server
 *------------------------------------------------------------------------
 */
int
passiveTCP(
    char    *service,       /* service associated with the desired port     */
    int     qlen)           /* maximum server request queue length          */
{
    return passivesock(service, "tcp", qlen);
}

