/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.39 from the
 * contents of Glob.xs. Do not edit this file, edit Glob.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

#line 1 "Glob.xs"
#define PERL_NO_GET_CONTEXT

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "bsd_glob.h"

#define MY_CXT_KEY "File::Glob::_guts" XS_VERSION

typedef struct {
#ifdef USE_ITHREADS
    tTHX interp;
#endif
    int		x_GLOB_ERROR;
    HV *	x_GLOB_ENTRIES;
    Perl_ophook_t	x_GLOB_OLD_OPHOOK;
} my_cxt_t;

START_MY_CXT

#define GLOB_ERROR	(MY_CXT.x_GLOB_ERROR)

#include "const-c.inc"

#ifdef WIN32
#define errfunc		NULL
#else
static int
errfunc(const char *foo, int bar) {
  PERL_UNUSED_ARG(foo);
  return !(bar == EACCES || bar == ENOENT || bar == ENOTDIR);
}
#endif

static void
doglob(pTHX_ const char *pattern, int flags)
{
    dSP;
    glob_t pglob;
    int i;
    int retval;
    SV *tmp;
    {
	dMY_CXT;

	/* call glob */
	memset(&pglob, 0, sizeof(glob_t));
	retval = bsd_glob(pattern, flags, errfunc, &pglob);
	GLOB_ERROR = retval;

	/* return any matches found */
	EXTEND(sp, pglob.gl_pathc);
	for (i = 0; i < pglob.gl_pathc; i++) {
	    /* printf("# bsd_glob: %s\n", pglob.gl_pathv[i]); */
	    tmp = newSVpvn_flags(pglob.gl_pathv[i], strlen(pglob.gl_pathv[i]),
				 SVs_TEMP);
	    TAINT;
	    SvTAINT(tmp);
	    PUSHs(tmp);
	}
	PUTBACK;

	bsd_globfree(&pglob);
    }
}

static void
iterate(pTHX_ bool(*globber)(pTHX_ AV *entries, const char *pat, STRLEN len, bool is_utf8))
{
    dSP;
    dMY_CXT;

    const char * const cxixpv = (char *)&PL_op;
    STRLEN const cxixlen = sizeof(OP *);
    AV *entries;
    U32 const gimme = GIMME_V;
    SV *patsv = POPs;
    bool on_stack = FALSE;

    if (!MY_CXT.x_GLOB_ENTRIES) MY_CXT.x_GLOB_ENTRIES = newHV();
    entries = (AV *)*(hv_fetch(MY_CXT.x_GLOB_ENTRIES, cxixpv, cxixlen, 1));

    /* if we're just beginning, do it all first */
    if (SvTYPE(entries) != SVt_PVAV) {
        const char *pat;
        STRLEN len;
        bool is_utf8;

        /* glob without args defaults to $_ */
        SvGETMAGIC(patsv);
        if (
            !SvOK(patsv)
              && (patsv = DEFSV, SvGETMAGIC(patsv), !SvOK(patsv))
            ) {
            pat = "";
            len = 0;
            is_utf8 = 0;
        }
        else {
            pat = SvPV_nomg(patsv,len);
            is_utf8 = !!SvUTF8(patsv);
            /* the lower-level code expects a null-terminated string */
            if (!SvPOK(patsv) || pat != SvPVX(patsv) || pat[len] != '\0') {
                SV *newpatsv = newSVpvn_flags(pat, len, SVs_TEMP);
                pat = SvPV_nomg(newpatsv,len);
            }
        }

        if (!IS_SAFE_SYSCALL(pat, len, "pattern", "glob")) {
            if (gimme != G_ARRAY)
                PUSHs(&PL_sv_undef);
            PUTBACK;
            return;
        }

	PUTBACK;
	on_stack = globber(aTHX_ entries, pat, len, is_utf8);
	SPAGAIN;
    }

    /* chuck it all out, quick or slow */
    if (gimme == G_ARRAY) {
	if (!on_stack && AvFILLp(entries) + 1) {
	    EXTEND(SP, AvFILLp(entries)+1);
	    Copy(AvARRAY(entries), SP+1, AvFILLp(entries)+1, SV *);
	    SP += AvFILLp(entries)+1;
	}
	/* No G_DISCARD here!  It will free the stack items. */
	(void)hv_delete(MY_CXT.x_GLOB_ENTRIES, cxixpv, cxixlen, 0);
    }
    else {
	if (AvFILLp(entries) + 1) {
	    mPUSHs(av_shift(entries));
	}
	else {
	    /* return undef for EOL */
	    (void)hv_delete(MY_CXT.x_GLOB_ENTRIES, cxixpv, cxixlen, G_DISCARD);
	    PUSHs(&PL_sv_undef);
	}
    }
    PUTBACK;
}

/* returns true if the items are on the stack already, but only in
   list context */
static bool
csh_glob(pTHX_ AV *entries, const char *pat, STRLEN len, bool is_utf8)
{
	dSP;
	AV *patav = NULL;
	const char *patend;
	const char *s = NULL;
	const char *piece = NULL;
	SV *word = NULL;
	SV *flags_sv = get_sv("File::Glob::DEFAULT_FLAGS", GV_ADD);
	int const flags = (int)SvIV(flags_sv);
	U32 const gimme = GIMME_V;

	patend = pat + len;

	assert(SvTYPE(entries) != SVt_PVAV);
	sv_upgrade((SV *)entries, SVt_PVAV);

	/* extract patterns */
	s = pat-1;
	while (++s < patend) {
	    switch (*s) {
	    case '\'':
	    case '"' :
	      {
		bool found = FALSE;
		const char quote = *s;
		if (!word) {
		    word = newSVpvs("");
		    if (is_utf8) SvUTF8_on(word);
		}
		if (piece) sv_catpvn(word, piece, s-piece);
		piece = s+1;
		while (++s < patend)
		    if (*s == '\\') {
			s++;
			/* If the backslash is here to escape a quote,
			   obliterate it. */
			if (s < patend && *s == quote)
			    sv_catpvn(word, piece, s-piece-1), piece = s;
		    }
		    else if (*s == quote) {
			sv_catpvn(word, piece, s-piece);
			piece = NULL;
			found = TRUE;
			break;
		    }
		if (!found) { /* unmatched quote */
		    /* Give up on tokenisation and treat the whole string
		       as a single token, but with whitespace stripped. */
		    piece = pat;
		    while (isSPACE(*pat)) pat++;
		    while (isSPACE(*(patend-1))) patend--;
		    /* bsd_glob expects a trailing null, but we cannot mod-
		       ify the original */
		    if (patend < pat + len) {
			if (word) sv_setpvn(word, pat, patend-pat);
			else
			    word = newSVpvn_flags(
				pat, patend-pat, SVf_UTF8*is_utf8
			    );
			piece = NULL;
		    }
		    else {
			if (word) SvREFCNT_dec(word), word=NULL;
			piece = pat;
			s = patend;
		    }
		    goto end_of_parsing;
		}
		break;
	      }
	    case '\\':
		if (!piece) piece = s;
		s++;
		/* If the backslash is here to escape a quote,
		   obliterate it. */
		if (s < patend && (*s == '"' || *s == '\'')) {
		    if (!word) {
			word = newSVpvn(piece,s-piece-1);
			if (is_utf8) SvUTF8_on(word);
		    }
		    else sv_catpvn(word, piece, s-piece-1);
		    piece = s;
		}
		break;
	    default:
		if (isSPACE(*s)) {
		    if (piece) {
			if (!word) {
			    word = newSVpvn(piece,s-piece);
			    if (is_utf8) SvUTF8_on(word);
			}
			else sv_catpvn(word, piece, s-piece);
		    }
		    if (!word) break;
		    if (!patav) patav = (AV *)sv_2mortal((SV *)newAV());
		    av_push(patav, word);
		    word = NULL;
		    piece = NULL;
		}
		else if (!piece) piece = s;
		break;
	    }
	}
      end_of_parsing:

	if (patav) {
	    I32 items = AvFILLp(patav) + 1;
	    SV **svp = AvARRAY(patav);
	    while (items--) {
		PUSHMARK(SP);
		PUTBACK;
		doglob(aTHX_ SvPVXx(*svp++), flags);
		SPAGAIN;
		{
		    dMARK;
		    dORIGMARK;
		    while (++MARK <= SP)
			av_push(entries, SvREFCNT_inc_simple_NN(*MARK));
		    SP = ORIGMARK;
		}
	    }
	}
	/* piece is set at this point if there is no trailing whitespace.
	   It is the beginning of the last token or quote-delimited
	   piece thereof.  word is set at this point if the last token has
	   multiple quoted pieces. */
	if (piece || word) {
	    if (word) {
		if (piece) sv_catpvn(word, piece, s-piece);
		piece = SvPVX(word);
	    }
	    PUSHMARK(SP);
	    PUTBACK;
	    doglob(aTHX_ piece, flags);
	    if (word) SvREFCNT_dec(word);
	    SPAGAIN;
	    {
		dMARK;
		dORIGMARK;
		/* short-circuit here for a fairly common case */
		if (!patav && gimme == G_ARRAY) { PUTBACK; return TRUE; }
		while (++MARK <= SP)
		    av_push(entries, SvREFCNT_inc_simple_NN(*MARK));

		SP = ORIGMARK;
	    }
	}
	PUTBACK;
	return FALSE;
}

static void
csh_glob_iter(pTHX)
{
    iterate(aTHX_ csh_glob);
}

/* wrapper around doglob that can be passed to the iterator */
static bool
doglob_iter_wrapper(pTHX_ AV *entries, const char *pattern, STRLEN len, bool is_utf8)
{
    dSP;
    SV * flags_sv = get_sv("File::Glob::DEFAULT_FLAGS", GV_ADD);
    int const flags = (int)SvIV(flags_sv);

    PERL_UNUSED_VAR(len); /* we use \0 termination instead */
    /* XXX we currently just use the underlying bytes of the passed SV.
     * Some day someone needs to make glob utf8 aware */
    PERL_UNUSED_VAR(is_utf8);

    PUSHMARK(SP);
    PUTBACK;
    doglob(aTHX_ pattern, flags);
    SPAGAIN;
    {
	dMARK;
	dORIGMARK;
	if (GIMME_V == G_ARRAY) { PUTBACK; return TRUE; }
	sv_upgrade((SV *)entries, SVt_PVAV);
	while (++MARK <= SP)
	    av_push(entries, SvREFCNT_inc_simple_NN(*MARK));
	SP = ORIGMARK;
    }
    return FALSE;
}

static void
glob_ophook(pTHX_ OP *o)
{
  if (PL_dirty) return;
  {
    dMY_CXT;
    if (MY_CXT.x_GLOB_ENTRIES
     && (o->op_type == OP_GLOB || o->op_type == OP_ENTERSUB))
	(void)hv_delete(MY_CXT.x_GLOB_ENTRIES, (char *)&o, sizeof(OP *),
		  G_DISCARD);
    if (MY_CXT.x_GLOB_OLD_OPHOOK) MY_CXT.x_GLOB_OLD_OPHOOK(aTHX_ o);
  }
}

#line 359 "Glob.c"
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

#line 503 "Glob.c"

XS_EUPXS(XS_File__Glob_GLOB_ERROR); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_GLOB_ERROR)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
#line 354 "Glob.xs"
	dMY_CXT;
#line 514 "Glob.c"
	int	RETVAL;
	dXSTARG;
#line 356 "Glob.xs"
	RETVAL = GLOB_ERROR;
#line 519 "Glob.c"
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_File__Glob_bsd_glob); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_bsd_glob)
{
    dVAR; dXSARGS;
    if (items < 1)
       croak_xs_usage(cv,  "pattern_sv, ...");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
	SV *	pattern_sv = ST(0)
;
#line 364 "Glob.xs"
    int flags = 0;
    char *pattern;
    STRLEN len;
#line 541 "Glob.c"
#line 368 "Glob.xs"
    {
        pattern = SvPV(pattern_sv, len);
        if (!IS_SAFE_SYSCALL(pattern, len, "pattern", "bsd_glob"))
            XSRETURN(0);
	/* allow for optional flags argument */
	if (items > 1) {
	    flags = (int) SvIV(ST(1));
	    /* remove unsupported flags */
	    flags &= ~(GLOB_APPEND | GLOB_DOOFFS | GLOB_ALTDIRFUNC | GLOB_MAGCHAR);
	} else {
	    SV * flags_sv = get_sv("File::Glob::DEFAULT_FLAGS", GV_ADD);
	    flags = (int)SvIV(flags_sv);
	}

	PUTBACK;
	doglob(aTHX_ pattern, flags);
	SPAGAIN;
    }
#line 561 "Glob.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_File__Glob_csh_glob); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_csh_glob)
{
    dVAR; dXSARGS;
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 391 "Glob.xs"
    /* For backward-compatibility with the original Perl function, we sim-
     * ply take the first argument, regardless of how many there are.
     */
    if (items) SP ++;
    else {
	XPUSHs(&PL_sv_undef);
    }
    PUTBACK;
    csh_glob_iter(aTHX);
    SPAGAIN;
#line 588 "Glob.c"
	PUTBACK;
	return;
    }
}


XS_EUPXS(XS_File__Glob_bsd_glob_override); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_bsd_glob_override)
{
    dVAR; dXSARGS;
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 405 "Glob.xs"
    if (items) SP ++;
    else {
	XPUSHs(&PL_sv_undef);
    }
    PUTBACK;
    iterate(aTHX_ doglob_iter_wrapper);
    SPAGAIN;
#line 612 "Glob.c"
	PUTBACK;
	return;
    }
}

#ifdef USE_ITHREADS
#define XSubPPtmpAAAA 1


XS_EUPXS(XS_File__Glob_CLONE); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_CLONE)
{
    dVAR; dXSARGS;
    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
    {
#line 418 "Glob.xs"
    HV *glob_entries_clone = NULL;
#line 631 "Glob.c"
#line 420 "Glob.xs"
    PERL_UNUSED_ARG(items);
    {
        dMY_CXT;
        if ( MY_CXT.x_GLOB_ENTRIES ) {
            CLONE_PARAMS param;
            param.stashes    = NULL;
            param.flags      = 0;
            param.proto_perl = MY_CXT.interp;

            glob_entries_clone = MUTABLE_HV(sv_dup_inc((SV*)MY_CXT.x_GLOB_ENTRIES, &param));
        }
    }
    {
        MY_CXT_CLONE;
        MY_CXT.x_GLOB_ENTRIES = glob_entries_clone;
        MY_CXT.interp = aTHX;
    }
#line 650 "Glob.c"
    }
    XSRETURN_EMPTY;
}

#endif

/* INCLUDE:  Including 'const-xs.inc' from 'Glob.xs' */


XS_EUPXS(XS_File__Glob_AUTOLOAD); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_File__Glob_AUTOLOAD)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    PERL_UNUSED_VAR(ax); /* -Wall */
    SP -= items;
    {
#line 120 "./const-xs.inc"
	SV *sv = newSVpvn_flags(SvPVX(cv), SvCUR(cv), SVs_TEMP | SvUTF8(cv));
	const COP *cop = PL_curcop;
#line 672 "Glob.c"
#line 123 "./const-xs.inc"
#ifndef SYMBIAN
	/* It's not obvious how to calculate this at C pre-processor time.
	   However, any compiler optimiser worth its salt should be able to
	   remove the dead code, and hopefully the now-obviously-unused static
	   function too.  */
	HV *constant_missing = (C_ARRAY_LENGTH(values_for_notfound) > 1)
	    ? get_missing_hash(aTHX) : NULL;
	if ((C_ARRAY_LENGTH(values_for_notfound) > 1)
	    ? hv_exists_ent(constant_missing, sv, 0) : 0) {
	    sv = newSVpvf("Your vendor has not defined File::Glob macro %" SVf
			  ", used at %" COP_FILE_F " line %" UVuf "\n", 
			  sv, COP_FILE(cop), (UV)CopLINE(cop));
	} else
#endif
	{
	    sv = newSVpvf("%" SVf
                          " is not a valid File::Glob macro at %"
			  COP_FILE_F " line %" UVuf "\n",
			  sv, COP_FILE(cop), (UV)CopLINE(cop));
	}
	croak_sv(sv_2mortal(sv));
#line 695 "Glob.c"
	PUTBACK;
	return;
    }
}


/* INCLUDE: Returning to 'Glob.xs' from 'const-xs.inc' */

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_File__Glob); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_File__Glob)
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

        newXS_deffile("File::Glob::GLOB_ERROR", XS_File__Glob_GLOB_ERROR);
        newXS_deffile("File::Glob::bsd_glob", XS_File__Glob_bsd_glob);
        newXS_deffile("File::Glob::csh_glob", XS_File__Glob_csh_glob);
        newXS_deffile("File::Glob::bsd_glob_override", XS_File__Glob_bsd_glob_override);
#if XSubPPtmpAAAA
        newXS_deffile("File::Glob::CLONE", XS_File__Glob_CLONE);
#endif
        newXS_deffile("File::Glob::AUTOLOAD", XS_File__Glob_AUTOLOAD);

    /* Initialisation Section */

#if XSubPPtmpAAAA
#endif
#line 441 "Glob.xs"
{
#ifndef PERL_EXTERNAL_GLOB
    /* Don't do this at home! The globhook interface is highly volatile. */
    PL_globhook = csh_glob_iter;
#endif
}

#line 449 "Glob.xs"
{
    MY_CXT_INIT;
    {
	dMY_CXT;
	MY_CXT.x_GLOB_ENTRIES = NULL;
	MY_CXT.x_GLOB_OLD_OPHOOK = PL_opfreehook;
#ifdef USE_ITHREADS
        MY_CXT.interp = aTHX;
#endif
	PL_opfreehook = glob_ophook;
    }  
}

#line 2 "./const-xs.inc"
  {
#if defined(dTHX) && !defined(PERL_NO_GET_CONTEXT)
    dTHX;
#endif
    HV *symbol_table = get_hv("File::Glob::", GV_ADD);

    static const struct iv_s values_for_iv[] =
      {
#ifdef GLOB_ABEND
        { "GLOB_ABEND", 10, GLOB_ABEND },
#endif
#ifdef GLOB_ALPHASORT
        { "GLOB_ALPHASORT", 14, GLOB_ALPHASORT },
#endif
#ifdef GLOB_ALTDIRFUNC
        { "GLOB_ALTDIRFUNC", 15, GLOB_ALTDIRFUNC },
#endif
#ifdef GLOB_BRACE
        { "GLOB_BRACE", 10, GLOB_BRACE },
#endif
#ifdef GLOB_ERR
        { "GLOB_ERR", 8, GLOB_ERR },
#endif
#ifdef GLOB_LIMIT
        { "GLOB_LIMIT", 10, GLOB_LIMIT },
#endif
#ifdef GLOB_MARK
        { "GLOB_MARK", 9, GLOB_MARK },
#endif
#ifdef GLOB_NOCASE
        { "GLOB_NOCASE", 11, GLOB_NOCASE },
#endif
#ifdef GLOB_NOCHECK
        { "GLOB_NOCHECK", 12, GLOB_NOCHECK },
#endif
#ifdef GLOB_NOMAGIC
        { "GLOB_NOMAGIC", 12, GLOB_NOMAGIC },
#endif
#ifdef GLOB_NOSORT
        { "GLOB_NOSORT", 11, GLOB_NOSORT },
#endif
#ifdef GLOB_NOSPACE
        { "GLOB_NOSPACE", 12, GLOB_NOSPACE },
#endif
#ifdef GLOB_QUOTE
        { "GLOB_QUOTE", 10, GLOB_QUOTE },
#endif
#ifdef GLOB_TILDE
        { "GLOB_TILDE", 10, GLOB_TILDE },
#endif
        { "GLOB_CSH", 8, GLOB_BRACE|GLOB_NOMAGIC|GLOB_QUOTE|GLOB_TILDE|GLOB_ALPHASORT },
        { NULL, 0, 0 } };
	const struct iv_s *value_for_iv = values_for_iv;
        while (value_for_iv->name) {
	    constant_add_symbol(aTHX_  symbol_table, value_for_iv->name,
				value_for_iv->namelen, newSViv(value_for_iv->value));
            ++value_for_iv;
	}
	if (C_ARRAY_LENGTH(values_for_notfound) > 1) {
#ifndef SYMBIAN
	    HV *const constant_missing = get_missing_hash(aTHX);
#endif
	    const struct notfound_s *value_for_notfound = values_for_notfound;
	    do {

		/* Need to add prototypes, else parsing will vary by platform.  */
		HE *he = (HE*) hv_common_key_len(symbol_table,
						 value_for_notfound->name,
						 value_for_notfound->namelen,
						 HV_FETCH_LVALUE, NULL, 0);
		SV *sv;
#ifndef SYMBIAN
		HEK *hek;
#endif
		if (!he) {
		    croak("Couldn't add key '%s' to %%File::Glob::",
			  value_for_notfound->name);
		}
		sv = HeVAL(he);
		if (!SvOK(sv) && SvTYPE(sv) != SVt_PVGV) {
		    /* Nothing was here before, so mark a prototype of ""  */
		    sv_setpvn(sv, "", 0);
		} else if (SvPOK(sv) && SvCUR(sv) == 0) {
		    /* There is already a prototype of "" - do nothing  */
		} else {
		    /* Someone has been here before us - have to make a real
		       typeglob.  */
		    /* It turns out to be incredibly hard to deal with all the
		       corner cases of sub foo (); and reporting errors correctly,
		       so lets cheat a bit.  Start with a constant subroutine  */
		    CV *cv = newCONSTSUB(symbol_table,
					 value_for_notfound->name,
					 &PL_sv_yes);
		    /* and then turn it into a non constant declaration only.  */
		    SvREFCNT_dec(CvXSUBANY(cv).any_ptr);
		    CvCONST_off(cv);
		    CvXSUB(cv) = NULL;
		    CvXSUBANY(cv).any_ptr = NULL;
		}
#ifndef SYMBIAN
		hek = HeKEY_hek(he);
		if (!hv_common(constant_missing, NULL, HEK_KEY(hek),
 			       HEK_LEN(hek), HEK_FLAGS(hek), HV_FETCH_ISSTORE,
			       &PL_sv_yes, HEK_HASH(hek)))
		    croak("Couldn't add key '%s' to missing_hash",
			  value_for_notfound->name);
#endif
	    } while ((++value_for_notfound)->name);
	}
    /* As we've been creating subroutines, we better invalidate any cached
       methods  */
    mro_method_changed_in(symbol_table);
  }

#line 882 "Glob.c"

    /* End of Initialisation Section */

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

