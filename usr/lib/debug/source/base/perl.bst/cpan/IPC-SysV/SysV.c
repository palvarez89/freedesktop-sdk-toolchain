/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.39 from the
 * contents of SysV.xs. Do not edit this file, edit SysV.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "SysV.xs"
/*******************************************************************************
*
*  Version 2.x, Copyright (C) 2007-2013, Marcus Holland-Moritz <mhx@cpan.org>.
*  Version 1.x, Copyright (C) 1999, Graham Barr <gbarr@pobox.com>.
*
*  This program is free software; you can redistribute it and/or
*  modify it under the same terms as Perl itself.
*
*******************************************************************************/

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#define NEED_sv_2pv_flags
#define NEED_sv_pvn_force_flags
#include "ppport.h"

#include <sys/types.h>

#if defined(HAS_MSG) || defined(HAS_SEM) || defined(HAS_SHM)
#  ifndef HAS_SEM
#    include <sys/ipc.h>
#  endif
#  ifdef HAS_MSG
#    include <sys/msg.h>
#  endif
#  ifdef HAS_SHM
#    if defined(PERL_SCO) || defined(PERL_ISC)
#      include <sys/sysmacros.h>	/* SHMLBA */
#    endif
#    include <sys/shm.h>
#    ifndef HAS_SHMAT_PROTOTYPE
       extern Shmat_t shmat(int, char *, int);
#    endif
#    if defined(HAS_SYSCONF) && defined(_SC_PAGESIZE)
#      undef  SHMLBA /* not static: determined at boot time */
#      define SHMLBA sysconf(_SC_PAGESIZE)
#    elif defined(HAS_GETPAGESIZE)
#      undef  SHMLBA /* not static: determined at boot time */
#      define SHMLBA getpagesize()
#    endif
#  endif
#endif

/* Required to get 'struct pte' for SHMLBA on ULTRIX. */
#if defined(__ultrix) || defined(__ultrix__) || defined(ultrix)
#include <machine/pte.h>
#endif

/* Required in BSDI to get PAGE_SIZE definition for SHMLBA.
 * Ugly.  More beautiful solutions welcome.
 * Shouting at BSDI sounds quite beautiful. */
#ifdef __bsdi__
#  include <vm/vm_param.h>	/* move upwards under HAS_SHM? */
#endif

#ifndef S_IRWXU
#  ifdef S_IRUSR
#    define S_IRWXU (S_IRUSR|S_IWUSR|S_IXUSR)
#    define S_IRWXG (S_IRGRP|S_IWGRP|S_IXGRP)
#    define S_IRWXO (S_IROTH|S_IWOTH|S_IXOTH)
#  else
#    define S_IRWXU 0700
#    define S_IRWXG 0070
#    define S_IRWXO 0007
#  endif
#endif

#define AV_FETCH_IV(ident, av, index)                         \
        STMT_START {                                          \
          SV **svp;                                           \
          if ((svp = av_fetch((av), (index), FALSE)) != NULL) \
            ident = SvIV(*svp);                               \
        } STMT_END

#define AV_STORE_IV(ident, av, index)                         \
          av_store((av), (index), newSViv(ident))

static const char *s_fmt_not_isa = "Method %s not called a %s object";
static const char *s_bad_length = "Bad arg length for %s, length is %d, should be %d";
static const char *s_sysv_unimpl PERL_UNUSED_DECL
                                 = "System V %sxxx is not implemented on this machine";

static const char *s_pkg_msg = "IPC::Msg::stat";
static const char *s_pkg_sem = "IPC::Semaphore::stat";
static const char *s_pkg_shm = "IPC::SharedMem::stat";

static void *sv2addr(SV *sv)
{
  if (SvPOK(sv) && SvCUR(sv) == sizeof(void *))
  {
    return *((void **) SvPVX(sv));
  }

  croak("invalid address value");

  return 0;
}

static void assert_sv_isa(SV *sv, const char *name, const char *method)
{
  if (!sv_isa(sv, name))
  {
    croak(s_fmt_not_isa, method, name);
  }
}

static void assert_data_length(const char *name, int got, int expected)
{
  if (got != expected)
  {
    croak(s_bad_length, name, got, expected);
  }
}

#include "const-c.inc"


#line 130 "SysV.c"
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
	    Perl_croak_nocontext("Usage: %s::%s(%s)", hvname, gvname, params);
        else
	    Perl_croak_nocontext("Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
	Perl_croak_nocontext("Usage: CODE(0x%" UVxf ")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#define croak_xs_usage        S_croak_xs_usage

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#if PERL_VERSION_LE(5, 21, 5)
#  define newXS_deffile(a,b) Perl_newXS(aTHX_ a,b,file)
#else
#  define newXS_deffile(a,b) Perl_newXS_deffile(aTHX_ a,b)
#endif

#line 274 "SysV.c"

XS_EUPXS(XS_IPC__Msg__stat_pack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__Msg__stat_pack)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "obj");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
#line 128 "SysV.xs"
  {
#ifdef HAS_MSG
    AV *list = (AV*) SvRV(obj);
    struct msqid_ds ds;
    assert_sv_isa(obj, s_pkg_msg, "pack");
    AV_FETCH_IV(ds.msg_perm.uid , list,  0);
    AV_FETCH_IV(ds.msg_perm.gid , list,  1);
    AV_FETCH_IV(ds.msg_perm.cuid, list,  2);
    AV_FETCH_IV(ds.msg_perm.cgid, list,  3);
    AV_FETCH_IV(ds.msg_perm.mode, list,  4);
    AV_FETCH_IV(ds.msg_qnum     , list,  5);
    AV_FETCH_IV(ds.msg_qbytes   , list,  6);
    AV_FETCH_IV(ds.msg_lspid    , list,  7);
    AV_FETCH_IV(ds.msg_lrpid    , list,  8);
    AV_FETCH_IV(ds.msg_stime    , list,  9);
    AV_FETCH_IV(ds.msg_rtime    , list, 10);
    AV_FETCH_IV(ds.msg_ctime    , list, 11);
    ST(0) = sv_2mortal(newSVpvn((char *) &ds, sizeof(ds)));
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "msg");
#endif
  }
#line 311 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__Msg__stat_unpack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__Msg__stat_unpack)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "obj, ds");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
	SV *	ds = ST(1)
;
#line 157 "SysV.xs"
  {
#ifdef HAS_MSG
    AV *list = (AV*) SvRV(obj);
    STRLEN len;
    const struct msqid_ds *data = (struct msqid_ds *) SvPV_const(ds, len);
    assert_sv_isa(obj, s_pkg_msg, "unpack");
    assert_data_length(s_pkg_msg, len, sizeof(*data));
    AV_STORE_IV(data->msg_perm.uid , list,  0);
    AV_STORE_IV(data->msg_perm.gid , list,  1);
    AV_STORE_IV(data->msg_perm.cuid, list,  2);
    AV_STORE_IV(data->msg_perm.cgid, list,  3);
    AV_STORE_IV(data->msg_perm.mode, list,  4);
    AV_STORE_IV(data->msg_qnum     , list,  5);
    AV_STORE_IV(data->msg_qbytes   , list,  6);
    AV_STORE_IV(data->msg_lspid    , list,  7);
    AV_STORE_IV(data->msg_lrpid    , list,  8);
    AV_STORE_IV(data->msg_stime    , list,  9);
    AV_STORE_IV(data->msg_rtime    , list, 10);
    AV_STORE_IV(data->msg_ctime    , list, 11);
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "msg");
#endif
  }
#line 356 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__Semaphore__stat_pack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__Semaphore__stat_pack)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "obj");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
#line 191 "SysV.xs"
  {
#ifdef HAS_SEM
    AV *list = (AV*) SvRV(obj);
    struct semid_ds ds;
    assert_sv_isa(obj, s_pkg_sem, "pack");
    AV_FETCH_IV(ds.sem_perm.uid , list, 0);
    AV_FETCH_IV(ds.sem_perm.gid , list, 1);
    AV_FETCH_IV(ds.sem_perm.cuid, list, 2);
    AV_FETCH_IV(ds.sem_perm.cgid, list, 3);
    AV_FETCH_IV(ds.sem_perm.mode, list, 4);
    AV_FETCH_IV(ds.sem_ctime    , list, 5);
    AV_FETCH_IV(ds.sem_otime    , list, 6);
    AV_FETCH_IV(ds.sem_nsems    , list, 7);
    ST(0) = sv_2mortal(newSVpvn((char *) &ds, sizeof(ds)));
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "sem");
#endif
  }
#line 394 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__Semaphore__stat_unpack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__Semaphore__stat_unpack)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "obj, ds");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
	SV *	ds = ST(1)
;
#line 216 "SysV.xs"
  {
#ifdef HAS_SEM
    AV *list = (AV*) SvRV(obj);
    STRLEN len;
    const struct semid_ds *data = (struct semid_ds *) SvPV_const(ds, len);
    assert_sv_isa(obj, s_pkg_sem, "unpack");
    assert_data_length(s_pkg_sem, len, sizeof(*data));
    AV_STORE_IV(data->sem_perm.uid , list, 0);
    AV_STORE_IV(data->sem_perm.gid , list, 1);
    AV_STORE_IV(data->sem_perm.cuid, list, 2);
    AV_STORE_IV(data->sem_perm.cgid, list, 3);
    AV_STORE_IV(data->sem_perm.mode, list, 4);
    AV_STORE_IV(data->sem_ctime    , list, 5);
    AV_STORE_IV(data->sem_otime    , list, 6);
    AV_STORE_IV(data->sem_nsems    , list, 7);
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "sem");
#endif
  }
#line 435 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__SharedMem__stat_pack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SharedMem__stat_pack)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "obj");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
#line 246 "SysV.xs"
  {
#ifdef HAS_SHM
    AV *list = (AV*) SvRV(obj);
    struct shmid_ds ds;
    assert_sv_isa(obj, s_pkg_shm, "pack");
    AV_FETCH_IV(ds.shm_perm.uid , list,  0);
    AV_FETCH_IV(ds.shm_perm.gid , list,  1);
    AV_FETCH_IV(ds.shm_perm.cuid, list,  2);
    AV_FETCH_IV(ds.shm_perm.cgid, list,  3);
    AV_FETCH_IV(ds.shm_perm.mode, list,  4);
    AV_FETCH_IV(ds.shm_segsz    , list,  5);
    AV_FETCH_IV(ds.shm_lpid     , list,  6);
    AV_FETCH_IV(ds.shm_cpid     , list,  7);
    AV_FETCH_IV(ds.shm_nattch   , list,  8);
    AV_FETCH_IV(ds.shm_atime    , list,  9);
    AV_FETCH_IV(ds.shm_dtime    , list, 10);
    AV_FETCH_IV(ds.shm_ctime    , list, 11);
    ST(0) = sv_2mortal(newSVpvn((char *) &ds, sizeof(ds)));
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "shm");
#endif
  }
#line 477 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__SharedMem__stat_unpack); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SharedMem__stat_unpack)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "obj, ds");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	obj = ST(0)
;
	SV *	ds = ST(1)
;
#line 275 "SysV.xs"
  {
#ifdef HAS_SHM
    AV *list = (AV*) SvRV(obj);
    STRLEN len;
    const struct shmid_ds *data = (struct shmid_ds *) SvPV_const(ds, len);
    assert_sv_isa(obj, s_pkg_shm, "unpack");
    assert_data_length(s_pkg_shm, len, sizeof(*data));
    AV_STORE_IV(data->shm_perm.uid , list,  0);
    AV_STORE_IV(data->shm_perm.gid , list,  1);
    AV_STORE_IV(data->shm_perm.cuid, list,  2);
    AV_STORE_IV(data->shm_perm.cgid, list,  3);
    AV_STORE_IV(data->shm_perm.mode, list,  4);
    AV_STORE_IV(data->shm_segsz    , list,  5);
    AV_STORE_IV(data->shm_lpid     , list,  6);
    AV_STORE_IV(data->shm_cpid     , list,  7);
    AV_STORE_IV(data->shm_nattch   , list,  8);
    AV_STORE_IV(data->shm_atime    , list,  9);
    AV_STORE_IV(data->shm_dtime    , list, 10);
    AV_STORE_IV(data->shm_ctime    , list, 11);
    XSRETURN(1);
#else
    croak(s_sysv_unimpl, "shm");
#endif
  }
#line 522 "SysV.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_IPC__SysV_ftok); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV_ftok)
{
    dVAR; dXSARGS;
    if (items < 1 || items > 2)
       croak_xs_usage(cv,  "path, id = &PL_sv_undef");
    {
	const char *	path = (const char *)SvPV_nolen(ST(0))
;
	SV *	id;
#line 310 "SysV.xs"
    int proj_id = 1;
    key_t k;
#line 542 "SysV.c"

	if (items < 2)
	    id = &PL_sv_undef;
	else {
	    id = ST(1)
;
	}
#line 313 "SysV.xs"
#if defined(HAS_SEM) || defined(HAS_SHM)
    if (SvOK(id))
    {
      if (SvIOK(id))
      {
        proj_id = (int) SvIVX(id);
      }
      else if (SvPOK(id) && SvCUR(id) == sizeof(char))
      {
        proj_id = (int) *SvPVX(id);
      }
      else
      {
        croak("invalid project id");
      }
    }
/* Including <sys/types.h> before <sys/ipc.h> makes Tru64
 * to see the obsolete prototype of ftok() first, grumble. */
# ifdef __osf__
#  define Ftok_t char*
/* Configure TODO Ftok_t */
# endif 
# ifndef Ftok_t
#  define Ftok_t const char*
# endif
    k = ftok((Ftok_t)path, proj_id);
    ST(0) = k == (key_t) -1 ? &PL_sv_undef : sv_2mortal(newSViv(k));
    XSRETURN(1);
#else
    Perl_die(aTHX_ PL_no_func, "ftok"); return;
#endif
#line 582 "SysV.c"
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IPC__SysV_memread); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV_memread)
{
    dVAR; dXSARGS;
    if (items != 4)
       croak_xs_usage(cv,  "addr, sv, pos, size");
    {
	SV *	addr = ST(0)
;
	SV *	sv = ST(1)
;
	int	pos = (int)SvIV(ST(2))
;
	int	size = (int)SvIV(ST(3))
;
#line 352 "SysV.xs"
    char *caddr = (char *) sv2addr(addr);
    char *dst;
    if (!SvOK(sv))
    {
      sv_setpvn(sv, "", 0);
    }
    SvPV_force_nolen(sv);
    dst = SvGROW(sv, (STRLEN) size + 1);
    Copy(caddr + pos, dst, size, char);
    SvCUR_set(sv, size);
    *SvEND(sv) = '\0';
    SvSETMAGIC(sv);
#ifndef INCOMPLETE_TAINTS
    /* who knows who has been playing with this memory? */
    SvTAINTED_on(sv);
#endif
    XSRETURN_YES;
#line 621 "SysV.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_IPC__SysV_memwrite); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV_memwrite)
{
    dVAR; dXSARGS;
    if (items != 4)
       croak_xs_usage(cv,  "addr, sv, pos, size");
    {
	SV *	addr = ST(0)
;
	SV *	sv = ST(1)
;
	int	pos = (int)SvIV(ST(2))
;
	int	size = (int)SvIV(ST(3))
;
#line 377 "SysV.xs"
    char *caddr = (char *) sv2addr(addr);
    STRLEN len;
    const char *src = SvPV_const(sv, len);
    int n = ((int) len > size) ? size : (int) len;
    Copy(src, caddr + pos, n, char);
    if (n < size)
    {
      memzero(caddr + pos + n, size - n);
    }
    XSRETURN_YES;
#line 653 "SysV.c"
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_IPC__SysV_shmat); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV_shmat)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "id, addr, flag");
    {
	int	id = (int)SvIV(ST(0))
;
	SV *	addr = ST(1)
;
	int	flag = (int)SvIV(ST(2))
;
#line 394 "SysV.xs"
#ifdef HAS_SHM
    if (id >= 0) {
      void *caddr = SvOK(addr) ? sv2addr(addr) : NULL;
      void *shm = (void *) shmat(id, caddr, flag);
      ST(0) = shm == (void *) -1 ? &PL_sv_undef
                                 : sv_2mortal(newSVpvn((char *) &shm, sizeof(void *)));
    } else {
      SETERRNO(EINVAL,LIB_INVARG);
      ST(0) = &PL_sv_undef;
    }
    XSRETURN(1);
#else
    Perl_die(aTHX_ PL_no_func, "shmat"); return;
#endif
#line 687 "SysV.c"
    }
    XSRETURN(1);
}


XS_EUPXS(XS_IPC__SysV_shmdt); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV_shmdt)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "addr");
    {
	SV *	addr = ST(0)
;
#line 413 "SysV.xs"
#ifdef HAS_SHM
    void *caddr = sv2addr(addr);
    int rv = shmdt((Shmat_t)caddr);
    ST(0) = rv == -1 ? &PL_sv_undef : sv_2mortal(newSViv(rv));
    XSRETURN(1);
#else
    Perl_die(aTHX_ PL_no_func, "shmdt"); return;
#endif
#line 711 "SysV.c"
    }
    XSRETURN(1);
}


/* INCLUDE:  Including 'const-xs.inc' from 'SysV.xs' */


XS_EUPXS(XS_IPC__SysV__constant); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_IPC__SysV__constant)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "sv");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 4 "./const-xs.inc"
#ifdef dXSTARG
	dXSTARG; /* Faster if we have it.  */
#else
	dTARGET;
#endif
	STRLEN		len;
        int		type;
	IV		iv = 0; /* avoid uninit var warning */
	/* NV		nv;	Uncomment this if you need to return NVs */
	/* const char	*pv;	Uncomment this if you need to return PVs */
#line 740 "SysV.c"
	SV *	sv = ST(0)
;
	const char *	s = SvPV(sv, len);
#line 18 "./const-xs.inc"
        /* Change this to _constant(aTHX_ s, len, &iv, &nv);
           if you need to return both NVs and IVs */
	type = _constant(aTHX_ s, len, &iv);
      /* Return 1 or 2 items. First is error message, or undef if no error.
           Second, if present, is found value */
        switch (type) {
        case PERL_constant_NOTFOUND:
          sv =
	    sv_2mortal(newSVpvf("%s is not a valid IPC::SysV macro", s));
          PUSHs(sv);
          break;
        case PERL_constant_NOTDEF:
          sv = sv_2mortal(newSVpvf(
	    "Your vendor has not defined IPC::SysV macro %s, used",
				   s));
          PUSHs(sv);
          break;
        case PERL_constant_ISIV:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHi(iv);
          break;
	/* Uncomment this if you need to return NOs
        case PERL_constant_ISNO:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_no);
          break; */
	/* Uncomment this if you need to return NVs
        case PERL_constant_ISNV:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHn(nv);
          break; */
	/* Uncomment this if you need to return PVs
        case PERL_constant_ISPV:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, strlen(pv));
          break; */
	/* Uncomment this if you need to return PVNs
        case PERL_constant_ISPVN:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, iv);
          break; */
	/* Uncomment this if you need to return SVs
        case PERL_constant_ISSV:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHs(sv);
          break; */
	/* Uncomment this if you need to return UNDEFs
        case PERL_constant_ISUNDEF:
          break; */
	/* Uncomment this if you need to return UVs
        case PERL_constant_ISUV:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHu((UV)iv);
          break; */
	/* Uncomment this if you need to return YESs
        case PERL_constant_ISYES:
          EXTEND(SP, 2);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_yes);
          break; */
        default:
          sv = sv_2mortal(newSVpvf(
	    "Unexpected return type %d while processing IPC::SysV macro %s, used",
               type, s));
          PUSHs(sv);
        }
#line 818 "SysV.c"
	PUTBACK;
	return;
    }
}


/* INCLUDE: Returning to 'SysV.xs' from 'const-xs.inc' */

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_IPC__SysV); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_IPC__SysV)
{
#if PERL_VERSION_LE(5, 21, 5)
    dVAR; dXSARGS;
#else
    dVAR; dXSBOOTARGSXSAPIVERCHK;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(file);

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#if PERL_VERSION_LE(5, 21, 5)
    XS_VERSION_BOOTCHECK;
#  ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#  endif
#endif

        (void)newXSproto_portable("IPC::Msg::stat::pack", XS_IPC__Msg__stat_pack, file, "$");
        (void)newXSproto_portable("IPC::Msg::stat::unpack", XS_IPC__Msg__stat_unpack, file, "$$");
        (void)newXSproto_portable("IPC::Semaphore::stat::pack", XS_IPC__Semaphore__stat_pack, file, "$");
        (void)newXSproto_portable("IPC::Semaphore::stat::unpack", XS_IPC__Semaphore__stat_unpack, file, "$$");
        (void)newXSproto_portable("IPC::SharedMem::stat::pack", XS_IPC__SharedMem__stat_pack, file, "$");
        (void)newXSproto_portable("IPC::SharedMem::stat::unpack", XS_IPC__SharedMem__stat_unpack, file, "$$");
        (void)newXSproto_portable("IPC::SysV::ftok", XS_IPC__SysV_ftok, file, "$;$");
        (void)newXSproto_portable("IPC::SysV::memread", XS_IPC__SysV_memread, file, "$$$$");
        (void)newXSproto_portable("IPC::SysV::memwrite", XS_IPC__SysV_memwrite, file, "$$$$");
        (void)newXSproto_portable("IPC::SysV::shmat", XS_IPC__SysV_shmat, file, "$$$");
        (void)newXSproto_portable("IPC::SysV::shmdt", XS_IPC__SysV_shmdt, file, "$");
        (void)newXSproto_portable("IPC::SysV::_constant", XS_IPC__SysV__constant, file, "$");
#if PERL_VERSION_LE(5, 21, 5)
#  if PERL_VERSION_GE(5, 9, 0)
    if (PL_unitcheckav)
        call_list(PL_scopestack_ix, PL_unitcheckav);
#  endif
    XSRETURN_YES;
#else
    Perl_xs_boot_epilog(aTHX_ ax);
#endif
}

