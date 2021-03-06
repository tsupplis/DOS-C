
/****************************************************************/
/*								*/
/*			      fat.h				*/
/*								*/
/*	 FAT File System data structures & declarations		*/
/*								*/
/*			November 26, 1991			*/
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


/* $Logfile:   C:/dos-c/hdr/fat.h_v  $ */
#ifdef MAIN
# ifdef VERSION_STRINGS
static BYTE *fat_hRcsId = "$Header:   C:/dos-c/hdr/fat.h_v   1.5   04 Jan 1998 23:14:18   patv  $";
# endif
#endif

/* $Log:   C:/dos-c/hdr/fat.h_v  $
 *	
 *	   Rev 1.5   04 Jan 1998 23:14:18   patv
 *	Changed Log for strip utility
 *	
 *	   Rev 1.4   29 May 1996 21:25:14   patv
 *	bug fixes for v0.91a
 *	
 *	   Rev 1.3   19 Feb 1996  3:15:30   patv
 *	Added NLS, int2f and config.sys processing
 *	
 *	   Rev 1.2   01 Sep 1995 17:35:42   patv
 *	First GPL release.
 *	
 *	   Rev 1.1   30 Jul 1995 20:43:48   patv
 *	Eliminated version strings in ipl
 *	
 *	   Rev 1.0   02 Jul 1995 10:39:40   patv
 *	Initial revision.
 */
/* $EndLog$ */

/* FAT file system attribute bits					*/
#define	D_NORMAL	0		/* normal			*/
#define	D_RDONLY	0x01		/* read-only file		*/
#define	D_HIDDEN	0x02		/* hidden			*/
#define	D_SYSTEM	0x04		/* system			*/
#define	D_VOLID		0x08		/* volume id			*/
#define	D_DIR		0x10		/* subdir			*/
#define	D_ARCHIVE	0x20		/* archive bit			*/

/* FAT file name constants						*/
#define	FNAME_SIZE		8
#define	FEXT_SIZE		3

/* FAT deleted flag							*/
#define	DELETED		0xe5		/* if first char, delete file	*/

/* FAT cluster to physical conversion macros				*/
#define clus_add(cl_no)		((LONG) (((LONG) cl_no - 2L) \
					* (LONG) cluster_size \
					+ (LONG) data_start))

#define clus2phys(cl_no,cl_size,d_st)	((LONG) (((LONG) cl_no - 2L) \
					* (LONG) cl_size \
					+ (LONG) d_st))

/* Test for 16 bit or 12 bit FAT					*/
#define SIZEOF_CLST16	2
#define FAT_MAGIC	4086

#define ISFAT16(dpbp)	(((dpbp)->dpb_size)>FAT_MAGIC)
#define ISFAT12(dpbp)	(((dpbp)->dpb_size)<=FAT_MAGIC)

/* FAT file system directory entry					*/
struct dirent
{
	UBYTE				/* Filename			*/
		dir_name[FNAME_SIZE];
	UBYTE				/* Filename extension		*/
		dir_ext[FEXT_SIZE];
	UBYTE				/* File Attribute		*/
		dir_attrib;
	BYTE	dir_reserved[10];	/* reserved			*/
	time	dir_time;		/* Time file created/updated	*/
	date	dir_date;		/*  Date file created/updated	*/
	UWORD	dir_start;		/* Starting cluster		*/
					/* 1st available = 2		*/
	ULONG	dir_size;		/* File size in bytes		*/
};

/*									*/
/* filesystem sizeof(dirent) - may be different from core		*/
/*									*/

#define DIR_NAME	0
#define	DIR_EXT		FNAME_SIZE
#define DIR_ATTRIB	FNAME_SIZE+FEXT_SIZE
#define DIR_RESERVED	FNAME_SIZE+FEXT_SIZE+1
#define DIR_TIME	FNAME_SIZE+FEXT_SIZE+11
#define DIR_DATE	FNAME_SIZE+FEXT_SIZE+13
#define DIR_START	FNAME_SIZE+FEXT_SIZE+15
#define DIR_SIZE	FNAME_SIZE+FEXT_SIZE+17

#define DIRENT_SIZE	32
