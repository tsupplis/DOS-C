; File:
;                         apisupt.asm
; Description:
;     Assembly support routines for stack manipulation, etc.
;
;                    Copyright (c) 1995, 1998
;                       Pasquale J. Villani
;                       All Rights Reserved
;
; This file is part of DOS-C.
;
; DOS-C is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version
; 2, or (at your option) any later version.
;
; DOS-C is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
; the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public
; License along with DOS-C; see the file COPYING.  If not,
; write to the Free Software Foundation, 675 Mass Ave,
; Cambridge, MA 02139, USA.
;
; $Logfile:   C:/usr/patv/dos-c/src/kernel/apisupt.asv  $
;
; $Header:   C:/usr/patv/dos-c/src/kernel/apisupt.asv   1.4   06 Dec 1998  8:47:02   patv  $
;
; $Log:   C:/usr/patv/dos-c/src/kernel/apisupt.asv  $
;
;   Rev 1.4   06 Dec 1998  8:47:02   patv
;Expanded due to new I/O subsystem.
;
;   Rev 1.3   16 Jan 1997 12:46:44   patv
;pre-Release 0.92 feature additions
;
;   Rev 1.2   29 May 1996 21:03:38   patv
;bug fixes for v0.91a
;
;   Rev 1.1   01 Sep 1995 17:54:26   patv
;First GPL release.
;
;   Rev 1.0   02 Jul 1995  9:04:50   patv
;Initial revision.
; $EndLog$
;

		page    60,132
		title   Assembly support routines for stack manipulation, etc.

IFDEF ??version
_TEXT           segment byte public 'CODE'
DGROUP          group   _DATA,_BSS,_BSSEND              ; small model
		assume  cs:_TEXT,ds:DGROUP,ss:DGROUP
_TEXT           ends

_DATA           segment word public 'DATA'
_DATA           ends

_BSS            segment word public 'BSS'
_BSS            ends

_BSSEND         segment byte public 'STACK'
_BSSEND         ends

ELSE
_TEXT           segment byte public 'CODE'
_TEXT           ends

_DATA           segment word public 'DATA'
_DATA           ends

CONST           segment word public 'CONST'
CONST           ends

_BSS            segment word public 'BSS'
_BSS            ends

_BSSEND         segment byte public 'STACK'
_BSSEND         ends

DGROUP          group   CONST,_DATA,_BSS,_BSSEND        ; small/tiny model
		assume  ds:DGROUP, ss:DGROUP
ENDIF

		extrn   _api_sp:word            ; api stacks - for context
		extrn   _api_ss:word            ; switching
		extrn   _usr_sp:word            ; user stacks
		extrn   _usr_ss:word

_TEXT           segment
		assume  cs: _TEXT
		public  _set_stack
;
; void far set_stack(void) - 
;       save current stack and setup our local stack
;
_set_stack      proc    far

		; save foreground stack

		; we need to get the return values from the stack 
		; since the current stack will change
		pop     ax                      ;get return offset
		pop     bx                      ;get return segment

		; Save the flags so that we can restore correct interrupt
		; state later. We need to disable interrupts so that we
		; don't trash memory with new sp-old ss combination
		pushf
		pop     dx
		cli
		
		; save bp
		push    bp

		mov     cx, sp
		neg     cx

		; save away foreground process' stack
		push    word ptr DGROUP:_usr_ss
		push    word ptr DGROUP:_usr_sp

		mov     word ptr DGROUP:_usr_ss,ss
		mov     word ptr DGROUP:_usr_sp,sp

		; setup our local stack
		mov     ss,word ptr DGROUP:_api_ss
		mov     sp,word ptr DGROUP:_api_sp

		add     cx, sp
		add     bp, cx

		; setup for ret
		push    bx  
		push    ax

		; now restore interrupt state
		push    dx
		popf

		ret

_set_stack      endp

;
; void far restore_stack(void) - 
;       restore foreground stack, throw ours away 
;
		public  _restore_stack
_restore_stack  proc    far

	; we need to get the return values from the stack 
	; since the current stack will change
		pop     cx                      ;get return offset
		pop     bx                      ;get return segment

		; Save the flags so that we can restore correct interrupt
		; state later. We need to disable interrupts so that we
		; don't trash memory with new sp-old ss combination
		pushf
		pop     dx
		cli

		; save background stack
		mov     word ptr DGROUP:_api_ss,ss
		mov     word ptr DGROUP:_api_sp,sp

		; restore foreground stack here
		mov     ss,word ptr DGROUP:_usr_ss
		mov     sp,word ptr DGROUP:_usr_sp
		
		pop     word ptr DGROUP:_usr_sp
		pop     word ptr DGROUP:_usr_ss

		; make bp relative to our stack frame
		pop     bp
		;mov     bp,sp   

		; setup for ret
		push    bx 
		push    cx
	    
		; now restore interrupt state
		push    dx
		popf

		ret
_restore_stack  endp

_TEXT           ends

		end

