PORTNAME=	mbpurple
PORTVERSION=	0.3.0
PORTREVISION=	6
CATEGORIES=	net-im
MASTER_SITES=	https://BSDforge.com/projects/source/net-im/mbpurple/

MAINTAINER=	portmaster@bsdforge.com
COMMENT=	Integrate Twitter with Pidgin (AKA microblog-purple)
WWW=		https://BSDforge.com/projects/net-im/mbpurple/

BUILD_DEPENDS=	${LOCALBASE}/bin/pidgin:net-im/pidgin
RUN_DEPENDS=	${LOCALBASE}/bin/pidgin:net-im/pidgin

LICENSE=	GPLv3+
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		dos2unix gmake pkgconfig
DOS2UNIX_GLOB=	*.c
MAKE_ARGS=	PREFIX="${PREFIX}" LIBDIR="${PREFIX}/lib" \
		PURPLE_DATAROOT_DIR="${PREFIX}/share"

post-patch:
	@${REINPLACE_CMD} 's/make -C/$$(MAKE) -C/' ${WRKSRC}/Makefile

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/purple-2/*.so

.include <bsd.port.mk>
