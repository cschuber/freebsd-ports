PORTNAME=	ukncbtl
DISTVERSION=	g20221102
CATEGORIES=	emulators

MAINTAINER=	makc@FreeBSD.org
COMMENT=	UKNC (Elektronika MS-0511) emulator
WWW=		https://github.com/nzeemin/ukncbtl-doc/wiki

LICENSE=	LGPL3
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		compiler:c++11-lang gl qmake qt:5

USE_GL=		gl
USE_QT=		core gui multimedia network script testlib widgets \
		buildtools:build qmake:build

USE_GITHUB=	yes
GH_ACCOUNT=	nzeemin
GH_PROJECT=	ukncbtl-qt
GH_TAGNAME=	a368c750

DESKTOP_ENTRIES=	"UkncBtl" \
			"" \
			"${PREFIX}/share/pixmaps/ukncbtl.png" \
			"${PORTNAME}" \
			"" \
			true

PLIST_FILES=	bin/${PORTNAME} \
		share/pixmaps/ukncbtl.png

post-patch:
	${REINPLACE_CMD} '/^#include/s,malloc.h,stdlib.h,' ${WRKSRC}/stdafx.h
	${REINPLACE_CMD} '/^TARGET/s,QtUkncBtl,${PORTNAME},' ${WRKSRC}/QtUkncBtl.pro

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/images/ukncbtl.png ${STAGEDIR}${PREFIX}/share/pixmaps

.include <bsd.port.mk>
