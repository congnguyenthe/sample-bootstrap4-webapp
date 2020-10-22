/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "data_processing_all_features.h"


#ifdef DSIMULATOR
int main(void);

int main(void)
{
	data_processing(" ");
    return 0;
}
#else
int main(int argc, char *argv[] );

int main ( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        printf( "usage: %s filename error \n", argv[0] );
    }
    else
    {
	    data_processing(argv[1]);
    }

    return 0;
}
#endif

