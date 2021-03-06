
/****************************************************************/
/*								*/
/*			     portab.h				*/
/*								*/
/*		   DOS-C portability typedefs, etc.		*/
/*								*/
/*			   May 1, 1995				*/
/*								*/
/*			Copyright (c) 1995			*/
/*			Pasquale J. Villani			*/
/*			All Rights Reserved			*/
/*								*/
/* This file is part of DOS-C.					*/
/*								*/
/* DOS-C is free software; you can redistribute it and/or	*/
/* modify it under the terms of the GNU General Public License	*/
/* as published by the Free Software Foundation; either version	*/
/* 2, or (at your option) any later version.			*/
/*								*/
/* DOS-C is distributed in the hope that it will be useful, but	*/
/* WITHOUT ANY WARRANTY; without even the implied warranty of	*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See	*/
/* the GNU General Public License for more details.		*/
/*								*/
/* You should have received a copy of the GNU General Public	*/
/* License along with DOS-C; see the file COPYING.  If not,	*/
/* write to the Free Software Foundation, 675 Mass Ave,		*/
/* Cambridge, MA 02139, USA.					*/
/****************************************************************/


/* $Logfile:   C:/dos-c/hdr/portab.h_v  $ */
#ifdef MAIN
# ifdef VERSION_STRINGS
static char *portab_hRcsId = "$Header:   C:/dos-c/hdr/portab.h_v   1.5   04 Jan 1998 23:14:16   patv  $";
# endif
#endif

/* $Log:   C:/dos-c/hdr/portab.h_v  $
 *	
 *	   Rev 1.5   04 Jan 1998 23:14:16   patv
 *	Changed Log for strip utility
 *	
 *	   Rev 1.4   29 May 1996 21:25:16   patv
 *	bug fixes for v0.91a
 *	
 *	   Rev 1.3   19 Feb 1996  3:15:32   patv
 *	Added NLS, int2f and config.sys processing
 *	
 *	   Rev 1.2   01 Sep 1995 17:35:44   patv
 *	First GPL release.
 *	
 *	   Rev 1.1   30 Jul 1995 20:43:50   patv
 *	Eliminated version strings in ipl
 *	
 *	   Rev 1.0   02 Jul 1995 10:39:50   patv
 *	Initial revision.
 */
/* $EndLog$ */


/****************************************************************/
/*								*/
/* Machine dependant portable types. Note that this section is	*/
/* used primarily for segmented architectures. Common types and	*/
/* types used relating to segmented operations are found here.	*/
/*								*/
/* Be aware that segmented architectures impose on linear	*/
/* architectures because they require special types to be used	*/
/* throught the code that must be reduced to empty preprocessor	*/
/* replacements in the linear machine.				*/
/*								*/
/* #ifdef <segmeted machine>					*/
/* # define FAR far						*/
/* # define NEAR near						*/
/* #endif							*/
/*								*/
/* #ifdef <linear machine>					*/
/* # define FAR							*/
/* # define NEAR						*/
/* #endif							*/
/*								*/
/****************************************************************/

#ifdef MC68K

# define far				/* No far type		*/
# define interrupt			/* No interrupt type	*/

# define VOID		void
# define FAR				/* linear architecture	*/
# define NEAR				/*    "        "	*/
# define INRPT		interrupt

# define CONST
# define REG		register

# define API		int		/* linear architecture	*/
# define NONNATIVE

# define PARASIZE	4096		/* "paragraph" size	*/
#endif

#ifdef I86

# define VOID		void
# define FAR		far		/* segment architecture	*/
# define NEAR		near		/*    "          "	*/
# define INRPT		interrupt

# define CONST		const
# define REG		register

# define API		int far pascal	/* segment architecture	*/
# define NATIVE

# define PARASIZE	16		/* "paragraph" size	*/
#endif

/*								*/
/* Boolean type & definitions of TRUE and FALSE boolean values	*/
/*								*/
typedef int		BOOL;
#define FALSE		(1==0)
#define TRUE		(1==1)

/*								*/
/* Common pointer types 					*/
/*								*/
#ifndef NULL
#define NULL		0
#endif


/*								*/
/* Convienence defines						*/
/*								*/
#define FOREVER		while(TRUE)
#ifndef max
# define max(a,b)	(((a) > (b)) ? (a) : (b))
#endif
#ifndef min
# define min(a,b)	(((a) < (b)) ? (a) : (b))
#endif


/*								*/
/* Common byte, 16 bit and 32 bit types				*/
/*								*/
typedef char		BYTE;
typedef short		WORD;
typedef long		DWORD;

typedef unsigned char	UBYTE;
typedef unsigned short	UWORD;

typedef short		SHORT;

typedef unsigned int	BITS;		/* for use in bit fields(!)	*/

typedef int		COUNT;
typedef unsigned int	UCOUNT;
typedef unsigned long	ULONG;

#ifdef UNIX
typedef char FAR	*ADDRESS;
#else
typedef void FAR	*ADDRESS;
#endif

#ifdef STRICT
typedef signed long	LONG;
#else
#define LONG long
#endif

/* General far pointer macros						*/
#ifdef I86
# ifdef __TURBOC__
#  define MK_FP(seg,ofs)	((VOID _seg *)(seg) + (VOID near *)(ofs))
#  define FP_SEG(fp)		((UWORD)(VOID _seg *)(VOID FAR *)(fp))
#  define FP_OFF(fp)		((UWORD)(fp))
# else
#  define MK_FP(seg,ofs)	((VOID _far *)(((LONG)(seg)<<16)|(UWORD)(ofs)))
#  define FP_SEG(fp)		(*((UWORD _far *)&(fp)+1))
#  define FP_OFF(fp)		(*((UWORD _far *)&(fp)))
# endif
#endif

#ifdef MC68K
# define MK_FP(seg,ofs)		((VOID *)(&(((BYTE *)(seg))[(ofs)])))
# define FP_SEG(fp)		(0)
# define FP_OFF(fp)		(fp)
#endif

