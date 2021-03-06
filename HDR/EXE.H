
/****************************************************************/
/*								*/
/*			      exe.h				*/
/*								*/
/*		   DOS EXE Header Data Structure		*/
/*								*/
/*			 December 1, 1991			*/
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


/* $Logfile:   C:/dos-c/hdr/exe.h_v  $ */
#ifdef MAIN
# ifdef VERSION_STRINGS
static BYTE *exe_hRcsId = "$Header:   C:/dos-c/hdr/exe.h_v   1.5   04 Jan 1998 23:14:16   patv  $";
# endif
#endif

/* $Log:   C:/dos-c/hdr/exe.h_v  $
 *	
 *	   Rev 1.5   04 Jan 1998 23:14:16   patv
 *	Changed Log for strip utility
 *	
 *	   Rev 1.4   29 May 1996 21:25:18   patv
 *	bug fixes for v0.91a
 *	
 *	   Rev 1.3   19 Feb 1996  3:15:34   patv
 *	Added NLS, int2f and config.sys processing
 *	
 *	   Rev 1.2   01 Sep 1995 17:35:38   patv
 *	First GPL release.
 *	
 *	   Rev 1.1   30 Jul 1995 20:41:56   patv
 *	Fixed ipl
 *	
 *	   Rev 1.0   02 Jul 1995 10:39:38   patv
 *	Initial revision.
 */
/* $EndLog$ */

typedef struct
{
	UWORD exSignature;
	UWORD exExtraBytes;
	UWORD exPages;
	UWORD exRelocItems;
	UWORD exHeaderSize;
	UWORD exMinAlloc;
	UWORD exMaxAlloc;
	UWORD exInitSS;
	UWORD exInitSP;
	UWORD exCheckSum;
	UWORD exInitIP;
	UWORD exInitCS;
	UWORD exRelocTable;
	UWORD exOverlay;
} exe_header;

#define MAGIC 0x5a4d

