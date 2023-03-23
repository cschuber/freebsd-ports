# Make sure that your configuration DOES NOT set ANY gcc-related
# variables.  ksh93 will not compile if you set even the seemingly
# most unrelated variable related to gcc configuration.  This means
# especially any flag which attempts to set the cputype.  Setting the
# cputype does absolutely nothing except cause systems to fail in
# horrible ways.  For any modern processor, setting the cputype only
# serves to expose gcc bugs and does nothing to speed up any known
# program.  If you are really unconvinced, go ahead but do not
# complain to me about it.

DISTVERSIONPREFIX=	v
PORTNAME=	ksh
PORTVERSION=	1.0.4
PORTREVISION=	1
CATEGORIES=	shells

MAINTAINER=	cy@FreeBSD.org
COMMENT=	Development branch of AT&T KornShell 93
WWW=		http://www.kornshell.com/

LICENSE=	EPL

BROKEN_aarch64=		Fails to link: missing sbrk
BROKEN_riscv64=		Fails to link: missing sbrk

USES=		compiler:c11

USE_GITHUB=	yes
GH_ACCOUNT=	ksh93
GH_PROJECT=	ksh

OPTIONS_DEFAULT=	EXAMPLES
OPTIONS_DEFINE=		EXAMPLES STATIC

CFLAGS+=	-DMAP_TYPE
LDFLAGS+=	-lm
MAKE_ENV=	CCFLAGS="-Wno-unused-value -Wno-parentheses -Wno-logical-op-parentheses" CFLAGS="${CFLAGS}"

STATIC_MAKE_ENV=	LDFLAGS+=-static

FLAVORS=	ksh ksh93 ksh93n
FLAVOR=		ksh93


.include <bsd.port.pre.mk>

.if ${FLAVOR} == ksh93
# Install to ${PREFIX}/bin/ksh93
# IMPORTANT:	Disabling conflicts, i.e. -DDISABLE_CONFLICTS will result in
#		arcane build failures due to already installed ksh/ksh93 in
#		$PATH.
CONFLICTS=	ksh93 ast-ksh ksh-devel
PSUFFIX=	93
PLIST_SUB=	93="93"
.elif ${FLAVOR} == ksh93n
# Install to ${PREFIX}/bin/ksh93n (new)
PSUFFIX=	93n
PLIST_SUB=	93="93n"
.else
# Install to ${PREFIX}/bin/ksh
CONFLICTS=	pdksh
PSUFFIX=
PLIST_SUB=	93=""
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|SF_FLAGS|SFIO_FLAGS|g' ${WRKSRC}/src/lib/libast/include/sfio*.h ${WRKSRC}/src/lib/libast/sfio/*.c

do-build:
	@cd ${WRKSRC}/ && ${SETENV} -i ${MAKE_ENV} ${SH} bin/package flat make

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/bin/ksh ${STAGEDIR}${PREFIX}/bin/ksh${PSUFFIX}
	${INSTALL_MAN} ${WRKSRC}/man/man1/sh.1 ${STAGEDIR}${MAN1PREFIX}/man/man1/ksh${PSUFFIX}.1
	${MKDIR} ${STAGEDIR}${EXAMPLESDIR}${PSUFFIX}/
	cd ${WRKSRC}/fun/ && ${INSTALL_SCRIPT} dirs popd pushd ${STAGEDIR}${EXAMPLESDIR}${PSUFFIX}/

do-test:
	cd ${WRKSRC}/src/cmd/ksh93/tests/ && ${SETENV} SHELL=${WRKSRC}/bin/ksh ${WRKSRC}/bin/ksh shtests

.include <bsd.port.mk>
