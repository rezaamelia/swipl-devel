/*  $Id$

    Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@uva.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 1985-2008, University of Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef PL_INLINE_H_INCLUDED
#define PL_INLINE_H_INCLUDED
#undef LD
#define LD LOCAL_LD

static inline code
fetchop(Code PC)
{ code op = decode(*PC);

  if ( op == D_BREAK )
    op = decode(replacedBreak(PC));

  return op;
}


static inline Code
stepPC(Code PC)
{ code op = fetchop(PC++);

  if ( codeTable[op].arguments == VM_DYNARGC )
    return stepDynPC(PC, &codeTable[op]);
  else
    return PC + codeTable[op].arguments;
}


static inline void
Trail__LD(Word p, word v ARG_LD)
{ assert(tTop+1 <= tMax);

  if ( p >= (Word)lBase || p < LD->mark_bar )
    (tTop++)->address = p;
  *p = v;
}


static inline void
bindConst__LD(Word p, word c ARG_LD)
{ assert(hasGlobalSpace(0));

#ifdef O_ATTVAR
  if ( isVar(*p) )
  { *p = (c);
    if ( p >= (Word)lBase || p < LD->mark_bar )
      (tTop++)->address = p;
  } else
  { assignAttVar(p, &(c) PASS_LD);
  }
#else
  *p = (c);
  if ( p >= (Word)lBase || p < LD->mark_bar )
    (tTop++)->address = p;
#endif
}

#endif /*PL_INLINE_H_INCLUDED*/
