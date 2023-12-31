PORTNAME=	libtommath
DISTVERSION=	1.2.1
CATEGORIES=	math
MASTER_SITES=	https://github.com/libtom/libtommath/releases/download/v${DISTVERSION}/
DISTNAME=	ltm-${DISTVERSION}

MAINTAINER=	gahr@FreeBSD.org
COMMENT=	Comprehensive, modular, and portable mathematical routines
WWW=		https://libtom.net/

LICENSE=	UNLICENSE
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake libtool:build pathfix tar:xz

WRKSRC=		${WRKDIR}/${PORTNAME}-${DISTVERSION}
USE_LDCONFIG=	yes

MAKEFILE=	makefile.shared
MAKE_ENV+=	IGNORE_SPEED=yes
ALL_TARGET=	default
CFLAGS+=	-fPIC
PORTDOCS=	*

PLIST_FILES=	include/tommath.h \
		lib/libtommath.a \
		lib/libtommath.so \
		lib/libtommath.so.${DISTVERSION:R:R} \
		lib/libtommath.so.${DISTVERSION} \
		libdata/pkgconfig/libtommath.pc

OPTIONS_DEFINE=	DOCS

post-patch:
	@${REINPLACE_CMD} -e 's|$$(LIBPATH)/pkgconfig|${PREFIX}/libdata/pkgconfig|' \
		${WRKSRC}/${MAKEFILE}

post-install:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/bn.pdf ${STAGEDIR}${DOCSDIR}
	@${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libtommath.so.${DISTVERSION}

do-test:
	(cd ${WRKSRC}; \
	 ${SETENV} ${MAKE_ENV} ${MAKE_CMD} -f makefile mtest/mtest test; \
	 ./mtest/mtest | ./test)

.include <bsd.port.mk>
