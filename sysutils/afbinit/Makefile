PORTNAME=		afbinit
PORTVERSION=		1.0
PORTREVISION=		4
CATEGORIES=		sysutils graphics
MASTER_SITES=		DEBIAN/pool/contrib/a/afbinit/:afbinit,patch \
			http://dlc.sun.com/osol/sparc-gfx/downloads/:microcode
DISTFILES=		${PORTNAME}_${PORTVERSION}.orig.tar.gz:afbinit \
			afb-ucode.tar.bz2:microcode
DIST_SUBDIR=		${PORTNAME}

PATCH_SITES=		${MASTER_SITES}
PATCHFILES=		${PORTNAME}_${PORTVERSION}-4.diff.gz:patch
PATCH_DIST_STRIP=	-p1

MAINTAINER=		ports@FreeBSD.org
COMMENT=		Sun AFB aka Sun Elite 3D microcode firmware loader

DEPRECATED=		sparc64 architecture is deprecated in FreeBSD
EXPIRATION_DATE=	2023-12-31

OPTIONS_DEFINE=		DOCS

ONLY_FOR_ARCHS=		sparc64
USE_RC_SUBR=		afbinit
WRKSRC=			${WRKDIR}/${PORTNAME}-${PORTVERSION}.orig
PKGMESSAGE=		${WRKDIR}/pkg-message

post-patch:
.for i in afbinit.c debian/afbinit.8
	@${REINPLACE_CMD} -E -e 's|\/usr\/lib|${DATADIR}|g; \
		s|(\/dev\/fb\[)[0-3]+(\])|\10-7\2|g; \
		s|\/etc\/init.d\/afbinit|${PREFIX}/etc/rc.d/afbinit\{,.sh\}|g' \
		${WRKSRC}/${i}
.endfor
	@${SED} 's|%%DATADIR%%|${DATADIR}|g' ${PKGDIR}/pkg-message > \
		${WRKDIR}/pkg-message

do-build:
	@cd ${WRKSRC} && ${CC} ${CFLAGS} -o afbinit afbinit.c

do-install:
	@${INSTALL_PROGRAM} ${WRKSRC}/afbinit ${STAGEDIR}${PREFIX}/sbin
	@${INSTALL_MAN} ${WRKSRC}/debian/afbinit.8 ${STAGEDIR}${PREFIX}/man/man8
	@${INSTALL} -d ${STAGEDIR}${DATADIR}
	@${INSTALL_DATA} ${WRKDIR}/afb-ucode/afb.ucode ${STAGEDIR}${DATADIR}
	@${INSTALL} -d ${STAGEDIR}${DOCSDIR}
	@${INSTALL_DATA} ${WRKDIR}/afb-ucode/README ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
